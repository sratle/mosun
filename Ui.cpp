#include "Ui.h"
extern keyhouse keys;

Ui::Ui(int width, int height)
	:width(width), height(height), current_index(0), plane(nullptr)
{
}

void Ui::init()
{
	initgraph(width, height);

	//加载页面
	IMAGE* page_1 = new IMAGE(width, height);
	loadimage(page_1, L"assets/main_test.png");//开始界面
	add_page(page_1);

	IMAGE* page_2 = new IMAGE(width, height);
	loadimage(page_2, L"assets/mune.jpg");//菜单界面
	add_page(page_2);

	IMAGE* page_3 = new IMAGE(width, height);
	loadimage(page_3, L"assets/attack01.png");//战斗第一界面
	add_page(page_3);
}

void Ui::run()
{
	ExMessage msg;
	BeginBatchDraw();
	draw_control();
	FlushBatchDraw();
	//记录每一帧使用的时间
	double start = 0;
	double end = 0;

	while (true)
	{
		start = clock();
		if (peekmessage(&msg))//如果有信息
		{//按键控制模块
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
		while (peekmessage(&msg)) {}//msg会有堆积，影响按键判断

		draw_control();//调用渲染控制函数
		FlushBatchDraw();
		end = clock();
		Sleep(DWORD(1000.0 / FPS + start - end));//控制帧率
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

//控制与页面渲染都在这个函数里控制
void Ui::draw_control()
{
	if (current_index < 0 || current_index > pages.size())//确认正常
		return;
	//渲染背景图
	putimage(0, 0, pages[current_index]);
	if (current_index == 0)
	{
		//给标题做的渐变效果，属于试验性质
		double cps = keys.timer / 10.0;
		COLORREF color = RGB(200 * abs(sin(cps)), 200 * abs(sin(cps)), 80);
		settextcolor(color);
		setbkmode(TRANSPARENT);
		settextstyle(140, 0, _T("华文行楷"));
		outtextxy(100, 100, L"Moon Sun");
		settextstyle(60, 0, _T("仿宋"));
		outtextxy(200, 800, L"按任意键进入");

		note(100, 10, 100, 50, 30, 0, L"0:退出");
		//确认捕获按键0则执行退出
		if (keys.condition == 0 && (!keys.key_any.empty()) && keys.key_any.back() == 48)
		{
			close();
		}//如果是其他任意按键就进入
		else if (keys.condition == 0 && (!keys.key_any.empty()))
		{
			keys.key_any.clear();
			set_current_index(1);
			keys.condition = 1;//让按键输入的模式转换到1模式：菜单模式
		}
	}
	else if (current_index == 1)
	{
		note(10, 10, 100, 50, 30, 1, L"0:退出");
		note(10, 200, 300, 70, 50, 1, L"1:踏上旅程");
		//菜单界面下方的sakuya
		put_bk_image(350 + int(300 * sin(keys.timer / 30.0)), 800, keys.sakuya[keys.timer / 10 % 3]);
		//按下0，返回开始界面
		if (keys.condition == 1 && (!keys.key_num.empty()) && keys.key_num.back() == 48)
		{
			keys.key_num.clear();
			PlaySound(L"assets/exit.wav", NULL, SND_ASYNC | SND_NOSTOP);
			set_current_index(0);
			keys.condition = 0;
		}
		//按下1，进入战斗界面
		if (keys.condition == 1 && (!keys.key_num.empty()) && keys.key_num.back() == 49)
		{
			keys.key_num.clear();
			set_current_index(2);
			keys.condition = 2;
			//初始进入战斗进行战机的初始化
			switch (keys.plane_id)
			{
			case 0:
				plane = new ur;
				break;
			case 1:
				plane = new nanna;
				break;
			case 2:
				plane = new ea;
				break;
			case 3:
				plane = new enlil;
				break;
			}
			plane->upgrade();//加载数据到keys中
			plane->set_stage(1);
			//init end
		}
		//按下2，进入无尽
		//按下3，进入机库
		//按下4，进入牌库
		//按下5，进入设置
	}
	else if (current_index == 2)
	{
		note(10, 10, 100, 50, 30, 1, L"0:退出");
		//返回菜单
		if (keys.condition == 2 && (!keys.key_num.empty()) && keys.key_num.back() == 48)
		{
			keys.key_num.clear();
			PlaySound(L"assets/exit.wav", NULL, SND_ASYNC | SND_NOSTOP);
			set_current_index(1);
			keys.condition = 1;
			//重置flags，用于关卡的flags
			for (int i = 0; i < keys.get_flag_size(); i++)
				keys.set_flag(i, 0);
			delete plane;
			plane = nullptr;
			//重置defeat目标数据
			defeat_target.clear();
			//内存管理
			if (enemys.empty())
				return;
			for (auto enemy : enemys)
				delete enemy;
			enemys.clear();
			return;
		}
		//死亡
		if (keys.hp <= 0) {
			note(180, 300, 360, 120, 80, 1, L"YOU DIED");
			return;
		}
		//机体相关的渲染,大部分渲染逻辑封装进plane中
		plane->draw();
		switch (keys.level)
		{
		case 0:
			level_1();
			break;
		}
		for (auto ene : enemys) {
			ene->draw();
		}
		judge();//判定
	}
}

void Ui::level_1()
{
	//使用flag和defeat目标进行对照，编写关卡下一个阶段的时候需要将target_num值手动加一
	static int target_num = 4;

	static int target = 0;
	if (defeat_target.empty())
		for (int i = 0; i <= target_num; i++)
			defeat_target.push_back(0);
	int i = 0;
	//模块start
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		//添加enemy,需修改
		enemys.push_back(new simple_enemy(240, 150, 1));//分别是x，y坐标和group参数，group就是关卡id
		enemys.push_back(new simple_enemy(480, 150, 1));
		//下面三句话不用改
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	//end
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		//添加enemy
		enemys.push_back(new simple_enemy(220, 150, 1));
		enemys.push_back(new lock_simple(360, 250, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_enemy(500, 150, 1));
		//下面三句话不用改
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		enemys.push_back(new lock_simple(160, 300, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_three(360, 150, 1));
		enemys.push_back(new lock_simple(560, 300, 1, &(plane->position[2]), &(plane->position[3])));
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		enemys.push_back(new simple_three(260, 150, 1));
		enemys.push_back(new lock_simple(120, 300, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new lock_simple(600, 300, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_three(460, 150, 1));
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
}

void Ui::judge()//判定函数
{
	//判定己方子弹对敌机的伤害
	for (auto shot : plane->shots)
	{
		for (auto enemy : enemys)
		{
			if (enemy->state)
				continue;//敌机已经寄了就不用做判断
			//若击中
			if (shot->flag == 0 && sqrt(pow(abs(shot->get_x() + 16 - enemy->position[2]), 2) + pow(abs(shot->get_y() + 16 - enemy->position[3]), 2)) < 24)
			{
				enemy->hp -= keys.attack * (1 + (rand() < keys.strike));
				shot->flag = 1;
			}
		}
	}
	//判定敌机子弹对己方的伤害
	for (auto enemy : enemys)
	{
		if (enemy->state)
			continue;//敌机已经寄了就不用做判断
		for (auto shot : enemy->shots)
		{
			if (shot->flag == 0 && sqrt(pow(abs(shot->get_x() + 16 - plane->position[2]), 2) + pow(abs(shot->get_y() + 16 - plane->position[3]), 2)) < 8)
			{
				keys.hp -= enemy->attack;
				shot->flag = 1;
			}
		}
	}
}

//重置enemys库,内存管理
void Ui::enemys_reset()
{
	if (enemys.empty())
		return;
	for (auto enemy : enemys)
		delete enemy;
	enemys.clear();
}

//在指定位置渲染一个提示框，参数为：x坐标，y坐标，宽度，高度，字体大小，是否含背景，内容
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

//设定当前页面的id
void Ui::set_current_index(int index)
{
	if (index >= 0 && index < pages.size())
	{
		current_index = index;
	}
}

//增加一个页面
void Ui::add_page(IMAGE* page)
{
	pages.push_back(page);
}

//该函数用来在指定位置渲染图片，注意渲染坐标是图片左上角
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

