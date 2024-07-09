#include "Ui.h"
extern keyhouse keys;
extern Ui ui;

Ui::Ui(int width, int height)
	:width(width), height(height), current_index(0)
{
}

void Ui::init()
{
	initgraph(width, height);

	planes_data.push_back(new ur);
	planes_data.push_back(new nanna);
	planes_data.push_back(new ea);
	planes_data.push_back(new enlil);

	set_current_index(0);
	IMAGE* page_1 = new IMAGE(width, height);
	loadimage(page_1, L"assets/main_test.png");
	add_page(page_1);

	IMAGE* page_2 = new IMAGE(width, height);
	loadimage(page_2, L"assets/mune.jpg");
	add_page(page_2);

	IMAGE* page_3 = new IMAGE(width, height);
	loadimage(page_3, L"assets/attack01.png");
	add_page(page_3);
}

void Ui::run()
{
	ExMessage msg;
	BeginBatchDraw();
	draw_control();
	FlushBatchDraw();
	double start = 0;
	double end = 0;

	while (true)
	{
		start = clock();
		if (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN && keys.condition == 0)
			{
				keys.key_any.push_back(msg.vkcode);
			}
			else if (msg.message == WM_KEYDOWN && keys.condition == 1)
			{
				if (msg.vkcode >= 48 && msg.vkcode <= 57)
				{
					keys.key_num.push_back(msg.vkcode);
				}
			}
			else if (msg.message == WM_KEYDOWN && keys.condition == 2)
			{
				if (msg.vkcode >= 48 && msg.vkcode <= 57)
				{
					keys.key_num.push_back(msg.vkcode);
				}
				else if (msg.vkcode == 65 || msg.vkcode == 68 || msg.vkcode == 83 || msg.vkcode == 87)//ADSW
				{
					keys.key_move = msg.vkcode;
				}
				else if (msg.vkcode == 20 || msg.vkcode == 74 || msg.vkcode == 75)//CapsLock,J,K
				{
					keys.key_card = msg.vkcode;
				}
			}
		}
		while (peekmessage(&msg)) {}//msg会有堆积，影响判断，清除

		draw_control();
		FlushBatchDraw();
		end = clock();
		Sleep(DWORD(1000.0 / FPS - start + end));//控制帧率
		keys.timer++;
		if (keys.timer > FPS * 30000)
		{
			keys.timer = 0;
		}
	}
	EndBatchDraw();
}

void Ui::close()
{
	closegraph();
	exit(0);
}

void Ui::draw_control()
{
	if (current_index >= 0 && current_index < pages.size())
	{
		putimage(0, 0, pages[current_index]);
		if (current_index == 0)
		{
			double cps = keys.timer / 10.0;
			COLORREF color = RGB(200 * abs(sin(cps)), 200 * abs(sin(cps)), 80);
			settextcolor(color);
			setbkmode(TRANSPARENT);
			settextstyle(140, 0, _T("华文行楷"));
			outtextxy(100, 100, L"Moon Sun");
			settextstyle(60, 0, _T("仿宋"));
			outtextxy(200, 800, L"按任意键进入");
			note(100, 10, 100, 50, 30, 0, L"0:退出");
			if (keys.condition == 0 && (!keys.key_any.empty()) && keys.key_any.back() == 48)
			{
				close();
			}
			else if (keys.condition == 0 && (!keys.key_any.empty()))
			{
				keys.key_any.clear();
				set_current_index(1);
				keys.condition = 1;
			}
		}
		else if (current_index == 1)
		{
			note(10, 10, 100, 50, 30, 1, L"0:退出");
			note(10, 200, 300, 70, 50, 1, L"1:踏上旅程");

			put_bk_image(350 + int(300 * sin(keys.timer / 30.0)), 800, keys.sakuya[keys.timer / 10 % 3]);
			if (keys.condition == 1 && (!keys.key_num.empty()) && keys.key_num.back() == 48)
			{
				keys.key_num.clear();
				PlaySound(L"assets/exit.wav", NULL, SND_ASYNC | SND_NOSTOP);
				set_current_index(0);
				keys.condition = 0;
			}
			if (keys.condition == 1 && (!keys.key_num.empty()) && keys.key_num.back() == 49)
			{
				keys.key_num.clear();
				set_current_index(2);
				keys.condition = 2;
				keys.plane_self.push_back(300);
				keys.plane_self.push_back(900);
				keys.plane_self.push_back(332);
				keys.plane_self.push_back(964);
			}
		}
		else if (current_index == 2)
		{
			if (keys.shot_time == 0) {
				keys.shot_time = keys.timer;
			}
			note(10, 10, 100, 50, 30, 1, L"0:退出");

			//渲染机体
			put_bk_image(keys.plane_self[0], keys.plane_self[1], keys.plane_image[keys.plane_id]);
			setfillcolor(WHITE);
			fillcircle(keys.plane_self[2], keys.plane_self[3], 5);
			//子弹渲染
			planes_data[keys.plane_id]->draw();

			if (keys.condition == 2 && (!keys.key_num.empty()) && keys.key_num.back() == 48)
			{
				keys.key_num.clear();
				PlaySound(L"assets/exit.wav", NULL, SND_ASYNC | SND_NOSTOP);
				set_current_index(1);
				keys.condition = 1;
			}
			if (keys.condition == 2 && keys.key_move == 65)
			{
				keys.plane_self[0] -= 3 + 5 * keys.move_flag;
				keys.key_move = 0;
			}
			else if (keys.condition == 2 && keys.key_move == 68)
			{
				keys.plane_self[0] += 3 + 5 * keys.move_flag;
				keys.key_move = 0;
			}
			else if (keys.condition == 2 && keys.key_move == 83)
			{
				keys.plane_self[1] += 3 + 5 * keys.move_flag;
				keys.key_move = 0;
			}
			else if (keys.condition == 2 && keys.key_move == 87)
			{
				keys.plane_self[1] -= 3 + 5 * keys.move_flag;
				keys.key_move = 0;
			}
			else if (keys.condition == 2 && keys.key_card == 20)
			{
				keys.move_flag = 1 - keys.move_flag;
				keys.key_card = 0;
			}
			keys.plane_self[2] = keys.plane_self[0] + 32;
			keys.plane_self[3] = keys.plane_self[1] + 64;
		}
	}
}

//x坐标，y坐标，宽度，高度，字体大小，是否含背景，内容
void Ui::note(int x, int y, int width, int height, int font, int bg, const wstring& text)
{
	if (bg == 1)
	{
		fillrectangle(x, y, x + width, y + height);
	}
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(font, 0, _T("仿宋"));
	int textX = x + (width - textwidth(text.c_str())) / 2;
	int textY = y + (height - textheight(_T("仿宋"))) / 2;
	outtextxy(textX, textY, text.c_str());
}

void Ui::set_current_index(int index)
{
	if (index >= 0 && index < pages.size())
	{
		current_index = index;
	}
}

void Ui::add_page(IMAGE* page)
{
	pages.push_back(page);
}

void Ui::put_bk_image(int x, int y, IMAGE img)
{
	IMAGE img1;
	DWORD* d1;
	img1 = img;
	d1 = GetImageBuffer(&img1);
	float h, s, l;
	for (int i = 0; i < img1.getheight() * img1.getwidth(); i++) {
		RGBtoHSL(BGR(d1[i]), &h, &s, &l);
		if (l < 0.03)
		{
			d1[i] = BGR(WHITE);
		}
		if (d1[i] != BGR(WHITE))
		{
			d1[i] = 0;
		}
	}
	putimage(x, y, &img1, SRCAND);
	putimage(x, y, &img, SRCPAINT);
}

