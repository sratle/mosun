#include "Ui.h"
extern keyhouse key_house;
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
	//控制fps
	double start = 0;
	double end = 0;

	while (true)
	{
		start = clock();
		if (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN && key_house.condition == 0)
			{
				key_house.key_any.push_back(msg.vkcode);
			}
			else if (msg.message == WM_KEYDOWN && key_house.condition == 1)
			{
				if (msg.vkcode >= 48 && msg.vkcode <= 57)
				{
					key_house.key_num.push_back(msg.vkcode);
				}
			}
			else if (msg.message == WM_KEYDOWN && key_house.condition == 2)
			{
				if (msg.vkcode >= 48 && msg.vkcode <= 57)
				{
					key_house.key_num.push_back(msg.vkcode);
				}
				else if (msg.vkcode == 65 || msg.vkcode == 68 || msg.vkcode == 83 || msg.vkcode == 87)//ADSW
				{
					key_house.key_move = msg.vkcode;
				}
				else if (msg.vkcode == 20 || msg.vkcode == 74 || msg.vkcode == 75)//CapsLock,J,K
				{
					key_house.key_card = msg.vkcode;
				}
			}
		}
		while (peekmessage(&msg)) {}//msg会有堆积，影响判断，清除

		draw_control();
		FlushBatchDraw();
		end = clock();
		Sleep(DWORD(1000.0 / FPS - start + end));
		key_house.timer++;
		if (key_house.timer > FPS * 30000)
		{
			key_house.timer = 0;
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
			double cps = key_house.timer / 10.0;
			COLORREF color = RGB(200 * abs(sin(cps)), 200 * abs(sin(cps)), 80);
			settextcolor(color);
			setbkmode(TRANSPARENT);
			settextstyle(140, 0, _T("华文行楷"));
			outtextxy(100, 100, L"Moon Sun");
			settextstyle(60, 0, _T("仿宋"));
			outtextxy(200, 800, L"按任意键进入");
			note(100, 10, 100, 50, 30, 0, L"0:退出");
			if (key_house.condition == 0 && (!key_house.key_any.empty()) && key_house.key_any.back() == 48)
			{
				close();
			}
			else if (key_house.condition == 0 && (!key_house.key_any.empty()))
			{
				key_house.key_any.clear();
				set_current_index(1);
				key_house.condition = 1;
			}
		}
		else if (current_index == 1)
		{
			note(10, 10, 100, 50, 30, 1, L"0:退出");
			note(10, 200, 300, 70, 50, 1, L"1:踏上旅程");

			put_bk_image(350 + int(300 * sin(key_house.timer / 30.0)), 800, key_house.sakuya[key_house.timer / 10 % 3]);
			if (key_house.condition == 1 && (!key_house.key_num.empty()) && key_house.key_num.back() == 48)
			{
				key_house.key_num.clear();
				PlaySound(L"assets/exit.wav", NULL, SND_ASYNC | SND_NOSTOP);
				set_current_index(0);
				key_house.condition = 0;
			}
			if (key_house.condition == 1 && (!key_house.key_num.empty()) && key_house.key_num.back() == 49)
			{
				key_house.key_num.clear();
				set_current_index(2);
				key_house.condition = 2;
				key_house.plane_self.push_back(300);
				key_house.plane_self.push_back(900);
				key_house.plane_self.push_back(332);
				key_house.plane_self.push_back(964);
			}
		}
		else if (current_index == 2)
		{
			note(10, 10, 100, 50, 30, 1, L"0:退出");

			put_bk_image(key_house.plane_self[0], key_house.plane_self[1], key_house.plane_image[key_house.plane_id]);
			setfillcolor(WHITE);
			fillcircle(key_house.plane_self[2], key_house.plane_self[3], 5);

			if (key_house.condition == 2 && (!key_house.key_num.empty()) && key_house.key_num.back() == 48)
			{
				key_house.key_num.clear();
				PlaySound(L"assets/exit.wav", NULL, SND_ASYNC | SND_NOSTOP);
				set_current_index(1);
				key_house.condition = 1;
			}
			if (key_house.condition == 2 && key_house.key_move == 65)
			{
				key_house.plane_self[0] -= 3 + 5 * key_house.move_flag;
				key_house.key_move = 0;
			}
			else if (key_house.condition == 2 && key_house.key_move == 68)
			{
				key_house.plane_self[0] += 3 + 5 * key_house.move_flag;
				key_house.key_move = 0;
			}
			else if (key_house.condition == 2 && key_house.key_move == 83)
			{
				key_house.plane_self[1] += 3 + 5 * key_house.move_flag;
				key_house.key_move = 0;
			}
			else if (key_house.condition == 2 && key_house.key_move == 87)
			{
				key_house.plane_self[1] -= 3 + 5 * key_house.move_flag;
				key_house.key_move = 0;
			}
			else if (key_house.condition == 2 && key_house.key_card == 20)
			{
				key_house.move_flag = 1 - key_house.move_flag;
				key_house.key_card = 0;
			}
			key_house.plane_self[2] = key_house.plane_self[0] + 32;
			key_house.plane_self[3] = key_house.plane_self[1] + 64;
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

