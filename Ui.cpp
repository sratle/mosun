#include "Ui.h"
extern keyhouse keys;

Ui::Ui(int width, int height)
	:width(width), height(height), current_index(0), plane(nullptr),music_id(0),bgm_id(0)
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
	loadimage(page_3, L"assets/attack01.png");//战斗.第一关
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
		{
			//按键控制模块
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
				else if (msg.vkcode == 88 || msg.vkcode == 90)//X,Z键
				{
					keys.key_card = msg.vkcode;
				}
			}
			else if (msg.x > 5 && keys.condition == 2 && plane != nullptr)
			{
				keys.move[0] = msg.x;
				keys.move[1] = msg.y;
			}
		}
		while (peekmessage(&msg)) {}//msg会有堆积，影响按键判断

		draw_control();//调用渲染控制函数
		FlushBatchDraw();
		end = clock();
		double diff = 1000.0 / FPS - end + start;
		if (diff <= 0)
			diff = 0;
		Sleep(DWORD(diff));//控制帧率
		keys.timer++;
		if (keys.timer > FPS * 30000)
		{
			keys.timer = 0;
			close();
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
		note(0, 100, 720, 150, 140, 0, color, WHITE, L"Moon Sun");
		note(0, 800, 720, 70, 60, 0, color, WHITE, L"按任意键进入");
		note(100, 10, 120, 50, 30, 0, color, WHITE, L"按0:退出");
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
		note(10, 10, 120, 50, 30, 1, LIGHTGRAY, WHITE, L"按0:退出");
		note(10, 200, 300, 70, 50, 1, BLACK, WHITE, L"按1:踏上旅程");
		note(10, 320, 300, 70, 50, 1, BLACK, WHITE, L"按2:无尽征途");
		note(10, 440, 300, 70, 50, 1, BLACK, WHITE, L"按3:进入机库");
		note(10, 560, 300, 70, 50, 1, BLACK, WHITE, L"按4:进入牌库");
		note(10, 680, 300, 70, 50, 1, BLACK, WHITE, L"按5:打开设置");
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
			plane->set_stage(0);
			//随机数种子更新
			srand((unsigned)time(NULL));
			bgm_id = 2;
			//init end
		}
		//按下2，进入无尽
		if (keys.condition == 1 && (!keys.key_num.empty()) && keys.key_num.back() == 50)
		{

		}
		//按下3，进入机库
		if (keys.condition == 1 && (!keys.key_num.empty()) && keys.key_num.back() == 51)
		{

		}
		//按下4，进入牌库
		if (keys.condition == 1 && (!keys.key_num.empty()) && keys.key_num.back() == 52)
		{

		}
		//按下5，进入设置
		if (keys.condition == 1 && (!keys.key_num.empty()) && keys.key_num.back() == 53)
		{

		}
	}
	else if (current_index == 2 || current_index == 3 || current_index == 4)
	{
		note(10, 10, 120, 50, 30, 0, LIGHTGRAY, WHITE, L"按0:退出");
		//返回菜单
		if (keys.condition == 2 && (!keys.key_num.empty()) && keys.key_num.back() == 48)
		{
			keys.key_num.clear();
			music_id = 1;
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
			if (!enemys.empty())
			{
				for (auto enemy : enemys)
					delete enemy;
				enemys.clear();
			}
			if (!drops.empty())
			{
				for (auto drop : drops)
					delete drop;
				drops.clear();
			}
			if (!card_select.empty())
			{
				for (auto card : card_select)
					delete card;
				card_select.clear();
			}
			card_now.clear();
			bgm_id = 0;
			return;
		}
		//死亡
		if (keys.hp <= 0) {
			note(180, 300, 400, 120, 80, 1, RED, WHITE, L"YOU DIED");
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
		for (auto drop : drops) {
			drop->draw();
		}
		judge();//判定
	}
}

void Ui::level_1()
{
	//使用flag和defeat目标进行对照，编写关卡下一个阶段的时候需要将target_num值手动加一
	static int target_num = 8;
	static int target = 0;
	if (defeat_target.empty()) {
		for (int i = 0; i <= target_num; i++) {
			defeat_target.push_back(0);
			target = 0;
		}
	}
	int i = 0;
	//模块start
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		//添加enemy,需修改
		enemys.push_back(new simple_enemy(260, 150, 1));//分别是x，y坐标和group参数，group就是关卡id
		enemys.push_back(new simple_enemy(460, 150, 1));
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
		enemys.push_back(new lock_super(120, 300, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new lock_simple(600, 300, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_three(460, 150, 1));
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		enemys.push_back(new simple_three(120, 360, 1));
		enemys.push_back(new lock_super(120, 140, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_three(360, 260, 1));
		enemys.push_back(new lock_super(600, 140, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_three(600, 360, 1));
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		enemys.push_back(new simple_three(120, 360, 1));
		enemys.push_back(new lock_super(120, 140, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new lock_super(360, 100, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_three(360, 260, 1));
		enemys.push_back(new lock_super(600, 140, 1, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_three(600, 360, 1));
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		enemys.push_back(new boss_1(360, 120, 1, &(plane->position[2]), &(plane->position[3])));
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		note(0, 500, 720, 70, 60, 0, LIGHTGREEN, WHITE, L"L1 COMPLETE!");
	}
}

void Ui::card_control()//卡牌相关的操控、使用
{
	//第一次进入这个函数
	if (card_now.empty())
	{
		int first = rand() % 6;
		int second = rand() % 6;
		card_now.push_back(card_select[first]->get_id());
		card_select[first]->set_pos(0);
		while (first == second)
			second = rand() % 6;
		card_now.push_back(card_select[second]->get_id());
		card_select[second]->set_pos(1);
	}
	for (int pos_id : card_now)
	{
		if (pos_id == -1)
		{
			//刷新
			if (keys.timer - keys.get_flag(0) > FPS * 5) {
				int rand_id = rand() % 6;
				if (card_now[0] == pos_id) {
					while (card_select[rand_id]->get_id() == card_now[1])
						rand_id = rand() % 6;
					card_now[0] = card_select[rand_id]->get_id();
					card_select[card_now[0]]->set_pos(0);
				}
				else {
					while (card_select[rand_id]->get_id() == card_now[0])
						rand_id = rand() % 6;
					card_now[1] = card_select[rand_id]->get_id();
					card_select[card_now[1]]->set_pos(1);
				}
			}
			continue;
		}
		card_select[pos_id]->draw();
		if (card_select[pos_id]->get_state() == 3)
		{
			//发动效果
			switch (card_select[pos_id]->get_id())
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			case 13:
				break;
			case 14:
				break;
			case 15:
				break;
			}
			//重置
			if (card_now[0] == pos_id)
				card_now[0] = -1;
			else
				card_now[1] = -1;
			card_select[pos_id]->set_state(0);
			keys.set_flag(0, keys.timer);
		}
	}
	//检测到了按键
	if (keys.key_card == 88)//对0位置操控
	{
		if (card_now[0] == -1) {
			keys.key_card = 0;
			return;
		}
		if (card_select[card_now[0]]->get_state() == 0 && card_select[card_now[1]]->get_state() == 1) {
			card_select[card_now[0]]->set_state(1);
			card_select[card_now[1]]->set_state(0);
		}
		else if (card_select[card_now[0]]->get_state() == 0) {
			card_select[card_now[0]]->set_state(1);
		}
		else if (card_select[card_now[0]]->get_state() == 1 && card_now[1] != -1 && keys.mp >= card_select[card_now[0]]->get_cost(card_now[0])) {
			keys.mp -= card_select[card_now[0]]->get_cost(card_now[0]);
			card_select[card_now[0]]->set_state(2);
		}
	}
	else if (keys.key_card == 90)//对1位置操控
	{
		if (card_now[1] == -1) {
			keys.key_card = 0;
			return;
		}
		if (card_select[card_now[1]]->get_state() == 0 && card_select[card_now[0]]->get_state() == 1) {
			card_select[card_now[1]]->set_state(1);
			card_select[card_now[0]]->set_state(0);
		}
		else if (card_select[card_now[1]]->get_state() == 0) {
			card_select[card_now[1]]->set_state(1);
		}
		else if (card_select[card_now[1]]->get_state() == 1 && card_now[0] != -1 && keys.mp > card_select[card_now[1]]->get_cost(card_now[1])) {
			keys.mp -= card_select[card_now[1]]->get_cost(card_now[1]);
			card_select[card_now[1]]->set_state(2);
		}
	}
	keys.key_card = 0;
}

void Ui::music_control()
{
	while(1)
	{
		switch (music_id)
		{
		case 0:
			break;
		case 1:
			PlaySound(L"assets/exit.wav", NULL, SND_ASYNC | SND_NOSTOP);
			music_id = 0;
			break;
		case 2:
			break;
		}
		Sleep(DWORD(400.0 / FPS));
	}
}

void Ui::bgm_control()
{
	int last_bgm = -1;
	mciSendString(L"open assets/main01.mp3 alias main01", 0, 0, 0);
	mciSendString(L"open assets/main02.mp3 alias main02", 0, 0, 0);
	mciSendString(L"open assets/level01.mp3 alias level01", 0, 0, 0);
	mciSendString(L"open assets/level02.mp3 alias level02", 0, 0, 0);
	mciSendString(L"open assets/level03.mp3 alias level03", 0, 0, 0);
	mciSendString(L"open assets/infinity.mp3 alias infinity", 0, 0, 0);
	while (1)
	{
		if (last_bgm != bgm_id) {
			switch (last_bgm)
			{
			case 0:
				mciSendString(L"stop main01", 0, 0, 0);
				break;
			case 1:
				mciSendString(L"stop main02", 0, 0, 0);
				break;
			case 2:
				mciSendString(L"stop level01", 0, 0, 0);
				break;
			case 3:
				mciSendString(L"stop level02", 0, 0, 0);
				break;
			case 4:
				mciSendString(L"stop level03", 0, 0, 0);
				break;
			case 5:
				mciSendString(L"stop infinity", 0, 0, 0);
				break;
			}
			last_bgm = bgm_id;
			Sleep(DWORD(1000.0 / FPS));
			switch (last_bgm)
			{
			case 0:
				mciSendString(L"play main01 repeat", 0, 0, 0);
				break;
			case 1:
				mciSendString(L"play main02 repeat", 0, 0, 0);
				break;
			case 2:
				mciSendString(L"play level01 repeat", 0, 0, 0);
				break;
			case 3:
				mciSendString(L"play level02 repeat", 0, 0, 0);
				break;
			case 4:
				mciSendString(L"play level03 repeat", 0, 0, 0);
				break;
			case 5:
				mciSendString(L"play infinity repeat", 0, 0, 0);
				break;
			}
		}
		Sleep(DWORD(1000.0 / FPS));
	}
}

void Ui::judge()//判定函数
{
	//判定己方子弹对敌机的伤害
	for (auto shot : plane->shots)
	{
		for (auto enemy : enemys)
		{
			if (enemy->state == 2)
				continue;//敌机已经寄了就不用做判断
			else if (enemy->state == 1)
			{
				if (enemy->get_id() == 4) {
					drops.push_back(new Drop(enemy->position[2], enemy->position[3], 4));//isthar
					enemy->state = 2;
					continue;
				}
				//随机释放掉落物
				int randi = rand() % 100;
				if (randi < 20)
					drops.push_back(new Drop(enemy->position[2], enemy->position[3], 0));//升级道具
				else if (randi < 40)
					drops.push_back(new Drop(enemy->position[2], enemy->position[3], 1));//血量
				else if (randi < 60)
					drops.push_back(new Drop(enemy->position[2], enemy->position[3], 2));//能量
				else if (randi < 75)
					drops.push_back(new Drop(enemy->position[2], enemy->position[3], 3));//star
				enemy->state = 2;
			}//若击中
			else if (shot->flag == 0 && sqrt(pow(abs(shot->get_x() + 16 - enemy->position[2]), 2) + pow(abs(shot->get_y() + 16 - enemy->position[3]), 2)) < 20)
			{
				enemy->hp -= keys.attack * (1 + ((rand() % 100) < keys.strike));
				shot->flag = 1;
				put_bk_image((int)shot->get_x(), (int)shot->get_y(), keys.boom_image[0]);
			}
		}
	}
	//判定敌机子弹对己方的伤害
	for (auto enemy : enemys)
	{
		if (enemy->state != 0)
			continue;//敌机已经寄了就不用做判断
		for (auto shot : enemy->shots)
		{
			if (shot->flag == 0 && sqrt(pow(abs(shot->get_x() + 16 - plane->position[2]), 2) + pow(abs(shot->get_y() + 16 - plane->position[3]), 2)) < 10)
			{
				keys.hp -= enemy->attack + keys.shield;
				plane->set_stage(plane->get_stage() - 1);
				shot->flag = 1;
				put_bk_image((int)shot->get_x(), (int)shot->get_y(), keys.boom_image[3]);
			}
		}
	}
	//判定掉落物
	for (auto drop : drops)
	{
		if (drop->state == 1)
			continue;
		//超大判定范围下，然后判断id，做出不同的功效
		if (sqrt(pow(abs(drop->get_x() - plane->position[2]), 2) + pow(abs(drop->get_y() - plane->position[3]), 2)) < 32)
		{
			drop->state = 1;
			switch (drop->get_id())
			{
			case 0:
				plane->set_stage(plane->get_stage() + 1);
				break;
			case 1:
				keys.hp += 150;
				if (keys.hp > plane->get_maxhp())
					keys.hp = plane->get_maxhp();
				break;
			case 2:
				keys.mp += 80;
				if (keys.mp > plane->get_maxmp())
					keys.mp = plane->get_maxmp();
				break;
			case 3:
				keys.star_value++;
				break;
			case 4:
				keys.isthar++;
				break;
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

//在指定位置渲染一个提示框，参数为：x坐标，y坐标，宽度，高度，字体大小，是否含背景，字体颜色，背景颜色，内容
void Ui::note(int x, int y, int width, int height, int font_size, int bg, COLORREF font_c, COLORREF bg_c, const wstring& text)
{
	if (bg == 1)
	{
		setfillcolor(bg_c);
		fillrectangle(x, y, x + width, y + height);
	}
	settextcolor(font_c);
	setbkmode(TRANSPARENT);
	settextstyle(font_size, 0, _T("华文新魏"));
	int textX = x + (width - textwidth(text.c_str())) / 2;
	int textY = y + (height - textheight(_T("华文新魏"))) / 2;
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

