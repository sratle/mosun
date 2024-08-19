#include "Ui.h"
extern keyhouse keys;

Ui::Ui(int width, int height)
	:width(width), height(height), current_index(0), plane(nullptr), music_id(0), bgm_id(0), mouse_ban(0)
{
}

void Ui::init()
{
	initgraph(width, height);
	keys.load();

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

	IMAGE* page_4 = new IMAGE(width, height);
	loadimage(page_4, L"assets/attack01.png");//战斗.第二关
	add_page(page_4);

	IMAGE* page_5 = new IMAGE(width, height);
	loadimage(page_5, L"assets/attack01.png");//战斗.第三关
	add_page(page_5);

	IMAGE* page_6 = new IMAGE(width, height);
	loadimage(page_6, L"assets/attack01.png");//战斗.无尽
	add_page(page_6);

	IMAGE* page_7 = new IMAGE(width, height);
	loadimage(page_7, L"assets/planehouse.png");//机库
	add_page(page_7);

	IMAGE* page_8 = new IMAGE(width, height);
	loadimage(page_8, L"assets/planehouse.png");//牌库
	add_page(page_8);

	IMAGE* page_9 = new IMAGE(width, height);
	loadimage(page_9, L"assets/planehouse.png");//设置
	add_page(page_9);
}

void Ui::run()
{
	BeginBatchDraw();
	draw_control();
	FlushBatchDraw();
	//记录每一帧使用的时间
	double start = 0;
	double end = 0;

	while (true)
	{
		start = clock();
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
		if (keys.condition == 0 && keys.key_any == 48)
		{
			keys.save();
			close();
		}//如果是其他任意按键就进入
		else if (keys.condition == 0 && keys.key_any)
		{
			music_id = 8;
			keys.key_any = 0;
			set_current_index(1);
			keys.condition = 1;//让按键输入的模式转换到1模式：菜单模式
		}
	}
	else if (current_index == 1)
	{
		COLORREF color = RGB(102, 204, 255);
		note(10, 10, 120, 50, 30, 1, LIGHTGRAY, WHITE, L"按0:退出");
		note(10, 200, 300, 70, 50, 1, BLACK, color, L"按1:踏上旅程");
		note(10, 320, 300, 70, 50, 1, BLACK, color, L"按2:无尽征途");
		note(10, 440, 300, 70, 50, 1, BLACK, color, L"按3:进入机库");
		note(10, 560, 300, 70, 50, 1, BLACK, color, L"按4:进入牌库");
		note(10, 680, 300, 70, 50, 1, BLACK, color, L"按5:打开设置");
		//菜单界面下方的sakuya
		put_bk_image(350 + int(300 * sin(keys.timer / 30.0)), 800, keys.sakuya[keys.timer / 10 % 3]);
		//按下0，返回开始界面
		if (keys.condition == 1 && keys.key_num == 48)
		{
			keys.key_num = 0;
			music_id = 1;
			set_current_index(0);
			keys.condition = 0;
		}
		//按下1，进入战斗界面
		if (keys.condition == 1 && keys.key_num == 49)
		{
			music_id = 8;
			keys.key_num = 0;
			set_current_index(2);
			keys.condition = 2;
			card_load();
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
			//血条部件
			tools.push_back(new hpmp_bar(plane->get_maxhp(), plane->get_maxmp(), &keys.hp, &keys.mp));
			//随机数种子更新
			srand((unsigned)time(NULL));
			bgm_id = 2;
			//init end
		}
		//按下2，进入无尽
		if (keys.condition == 1 && keys.key_num == 50)
		{
			music_id = 8;
			keys.key_num = 0;
			set_current_index(5);
			keys.condition = 2;
			card_load();
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
			//血条部件
			tools.push_back(new hpmp_bar(plane->get_maxhp(), plane->get_maxmp(), &keys.hp, &keys.mp));
			//随机数种子更新
			srand((unsigned)time(NULL));
			bgm_id = 5;
			//init end
		}
		//按下3，进入机库
		if (keys.condition == 1 && keys.key_num == 51)
		{
			music_id = 8;
			bgm_id = 1;
			keys.key_num = 0;
			set_current_index(6);
		}
		//按下4，进入牌库
		if (keys.condition == 1 && keys.key_num == 52)
		{
			music_id = 8;
			bgm_id = 1;
			keys.key_num = 0;
			set_current_index(7);
		}
		//按下5，进入设置
		if (keys.condition == 1 && keys.key_num == 53)
		{
			music_id = 8;
			bgm_id = 1;
			keys.key_num = 0;
			set_current_index(8);
		}
	}
	else if (current_index == 2 || current_index == 3 || current_index == 4)
	{
		COLORREF color = RGB(102, 204, 255);
		note(10, 10, 120, 50, 30, 0, LIGHTGRAY, WHITE, L"按0:退出");
		string text2 = "Stage:" + std::to_string(keys.stage + 1);
		wstring out2(text2.begin(), text2.end());
		note(200, 10, 100, 50, 30, 0, color, WHITE, out2.c_str());
		string text3 = "Level:" + std::to_string(keys.plane_level[keys.plane_id] + 1);
		wstring out3(text3.begin(), text3.end());
		note(420, 10, 100, 50, 30, 0, color, WHITE, out3.c_str());
		if (mouse_ban == 0) {
			note(570, 10, 120, 50, 30, 0, LIGHTGRAY, WHITE, L"F1禁用鼠标");
		}
		else if (mouse_ban == 1) {
			note(570, 10, 120, 50, 30, 0, LIGHTGRAY, WHITE, L"F1启用鼠标");
		}

		//返回菜单
		if (keys.condition == 2 && keys.key_num == 48)
		{
			keys.save();
			keys.score = 0;
			keys.key_num = 0;
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
			if (!tools.empty())
			{
				for (auto tool : tools)
					delete tool;
				tools.clear();
			}
			if (!card_select.empty())
			{
				for (auto card : card_select)
					delete card;
				card_select.clear();
			}
			card_now.clear();
			bgm_id = 0;
			keys.stage = 0;
			keys.move[0] = 360;
			keys.move[1] = 932;
			return;
		}
		//死亡
		if (keys.hp <= 0) {
			note(180, 300, 400, 120, 80, 1, RED, WHITE, L"YOU DIED");
			return;
		}
		//机体相关的渲染,大部分渲染逻辑封装进plane中
		plane->draw();
		switch (keys.stage)
		{
		case 0:
			stage_1();
			break;
		case 1:
			stage_2();
			break;
		case 2:
			stage_3();
			break;
		}
		card_control();
		for (auto ene : enemys) {
			ene->draw();
		}
		for (auto drop : drops) {
			drop->draw();
		}
		for (auto tool : tools) {
			tool->draw();
		}
		judge();//判定
	}
	else if (current_index == 5)
	{
		COLORREF color = RGB(102, 204, 255);
		note(10, 10, 120, 50, 30, 0, LIGHTGRAY, WHITE, L"按0:退出");
		string text2 = "score:" + std::to_string(keys.score);
		wstring out2(text2.begin(), text2.end());
		note(200, 10, 100, 50, 30, 0, color, WHITE, out2.c_str());
		string text3 = "Level:" + std::to_string(keys.plane_level[keys.plane_id] + 1);
		wstring out3(text3.begin(), text3.end());
		note(420, 10, 100, 50, 30, 0, color, WHITE, out3.c_str());
		if (mouse_ban == 0) {
			note(570, 10, 120, 50, 30, 0, LIGHTGRAY, WHITE, L"F1禁用鼠标");
		}
		else if (mouse_ban == 1) {
			note(570, 10, 120, 50, 30, 0, LIGHTGRAY, WHITE, L"F1启用鼠标");
		}

		//返回菜单
		if (keys.condition == 2 && keys.key_num == 48)
		{
			if (keys.score > keys.max_score) {
				keys.max_score = keys.score;
				keys.score_plane_id = keys.plane_id;
				keys.score_level = keys.plane_level[keys.plane_id];
			}
			keys.save();
			keys.score = 0;
			keys.key_num = 0;
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
			if (!tools.empty())
			{
				for (auto tool : tools)
					delete tool;
				tools.clear();
			}
			if (!card_select.empty())
			{
				for (auto card : card_select)
					delete card;
				card_select.clear();
			}
			card_now.clear();
			bgm_id = 0;
			keys.stage = 0;
			keys.move[0] = 360;
			keys.move[1] = 932;
			return;
		}
		//死亡
		if (keys.hp <= 0) {
			note(180, 300, 400, 120, 80, 1, RED, WHITE, L"YOU DIED");
			return;
		}
		//机体相关的渲染,大部分渲染逻辑封装进plane中
		plane->draw();
		//无尽关卡
		infinity();
		card_control();
		for (auto ene : enemys) {
			ene->draw();
		}
		for (auto drop : drops) {
			drop->draw();
		}
		for (auto tool : tools) {
			tool->draw();
		}
		judge();//判定
	}
	else if (current_index == 6)
	{
		plane_house();
	}
	else if (current_index == 7)
	{
		card_house();
	}
	else if (current_index == 8)
	{
		static int display_status = 0;
		static int rand_num = 0;
		COLORREF color = RGB(102, 204, 255);
		note(10, 10, 120, 50, 30, 1, LIGHTGRAY, WHITE, L"按0:退出");
		string text2 = "Max Score:" + std::to_string(keys.max_score);
		wstring out2(text2.begin(), text2.end());
		note(0, 70, 720, 50, 40, 0, color, WHITE, out2.c_str());
		switch (keys.score_plane_id)
		{
		case 0:
			note(0, 130, 720, 50, 40, 0, color, WHITE, L"Plane:Chirono");
			break;
		case 1:
			note(0, 130, 720, 50, 40, 0, color, WHITE, L"Plane:Patchouli");
			break;
		case 2:
			note(0, 130, 720, 50, 40, 0, color, WHITE, L"Plane:Sanae");
			break;
		case 3:
			note(0, 130, 720, 50, 40, 0, color, WHITE, L"Plane:Meirin");
			break;
		}
		string text3 = "Level:" + std::to_string(keys.score_level + 1);
		wstring out3(text3.begin(), text3.end());
		note(0, 190, 720, 50, 40, 0, color, WHITE, out3.c_str());
		note(0, 10, 720, 55, 50, 0, color, WHITE, L"按9重置存档");
		note(0, 250, 720, 55, 50, 0, color, WHITE, L"按1进行星辰抽卡（star-10）");
		note(0, 310, 720, 55, 50, 0, color, WHITE, L"按2进行月光抽卡（moon-3）");
		note(0, 370, 720, 55, 50, 0, color, WHITE, L"按3进行烈日抽卡（sun-1）");
		note(0, 430, 720, 55, 50, 0, color, WHITE, L"卡池是一样的！");

		if (keys.condition == 1 && keys.key_num == 49) 
		{
			keys.key_num = 0;
			if (keys.star_value >= 10) {
				keys.star_value -= 10;
				display_status = 2;
			}
			else {
				display_status = 1;
			}
		}
		if (keys.condition == 1 && keys.key_num == 50)
		{
			keys.key_num = 0;
			if (keys.moon >= 3) {
				keys.moon -= 3;
				display_status = 2;
			}
			else {
				display_status = 1;
			}
		}
		if (keys.condition == 1 && keys.key_num == 51)
		{
			keys.key_num = 0;
			if (keys.sun >= 1) {
				keys.sun -= 1;
				display_status = 2;
			}
			else {
				display_status = 1;
			}
		}
		if (display_status == 2) {
			srand((unsigned)time(NULL));
			rand_num = rand() % 10 + 6;
			if (keys.cards_unlock[rand_num] == 0) {
				keys.cards_unlock[rand_num] = 1;
				display_status = 3;
			}
			else {
				display_status = 4;
			}
			keys.save();
		}
		if (display_status == 1) {
			note(0, 500, 720, 55, 50, 0, color, WHITE, L"资源不足！");
		}
		if (display_status == 3) {
			switch (rand_num)
			{
			case 6:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"解锁了[帕秋莉·诺蕾姬]");
				break;
			case 7:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"解锁了[博丽灵梦]");
				break;
			case 8:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"解锁了[东风谷早苗]");
				break;
			case 9:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"解锁了[尔子田里乃]");
				break;
			case 10:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"解锁了[古明地觉]");
				break;
			case 11:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"解锁了[伊吹萃香]");
				break;
			case 12:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"解锁了[洩矢诹访子]");
				break;
			case 13:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"解锁了[比那名居天子]");
				break;
			case 14:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"解锁了[灵乌路空]");
				break;
			case 15:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"解锁了[八云紫]");
				break;
			}
		}
		if (display_status == 4) {
			switch (rand_num % 8) {
			case 0:
				keys.star_value += 3;
				break;
			case 1:
				keys.moon += 2;
				break;
			case 2:
				keys.sun += 1;
				break;
			case 3:
				keys.star_value += 6;
				break;
			case 4:
				keys.star_value += 10;
				break;
			case 5:
				keys.moon += 4;
				break;
			case 6:
				keys.sun += 2;
				break;
			case 7:
				keys.star_value += 18;
				break;
			}
			display_status = 5;
		}
		if (display_status == 5) {
			switch (rand_num % 8) {
			case 0:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"获得star*3");
				break;
			case 1:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"获得moon*2");
				break;
			case 2:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"获得sun*1");
				break;
			case 3:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"获得star*6");
				break;
			case 4:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"获得star*10");
				break;
			case 5:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"获得moon*4");
				break;
			case 6:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"获得sun*2");
				break;
			case 7:
				note(0, 500, 720, 55, 50, 0, color, WHITE, L"获得star*18");
				break;
			}
			display_status = 5;
		}
		if (keys.condition == 1 && keys.key_num == 57)
		{
			keys.reset_save();
			keys.save();
			keys.load();
		}
		if (keys.condition == 1 && keys.key_num == 48)
		{
			keys.key_num = 0;
			music_id = 1;
			bgm_id = 0;
			set_current_index(1);
			return;
		}
	}
}

void Ui::stage_1()
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
		keys.save();
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
		keys.save();
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
		keys.save();
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
		keys.save();
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
		keys.save();
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
		keys.save();
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
		keys.save();
		enemys.push_back(new boss_1(360, 120, 1, &(plane->position[2]), &(plane->position[3])));
		keys.set_flag(1, keys.get_flag(1) + 1);
		target++;
		defeat_target[target] = keys.get_flag(1) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(1) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		note(0, 500, 720, 70, 60, 0, LIGHTGREEN, WHITE, L"STAGE01 COMPLETE!");
		static int count = 0;
		count++;
		if (count == FPS * 5) {
			keys.stage = 1;
			set_current_index(3);
			defeat_target.clear();
			bgm_id = 3;
			count = 0;
		}
	}
}

void Ui::stage_2()
{
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
	if (keys.get_flag(2) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		//添加enemy,需修改
		enemys.push_back(new lock_extend(560, 140, 2, &(plane->position[2]), &(plane->position[3])));//分别是x，y坐标和group参数，group就是关卡id
		enemys.push_back(new lock_extend(160, 140, 2, &(plane->position[2]), &(plane->position[3])));
		//下面三句话不用改
		keys.set_flag(2, keys.get_flag(2) + 1);
		target++;
		defeat_target[target] = keys.get_flag(2) + (int)enemys.size();
	}
	i++;
	//end
	if (keys.get_flag(2) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		//添加enemy,需修改
		enemys.push_back(new five_super(580, 200, 2, -6));//分别是x，y坐标和group参数，group就是关卡id
		enemys.push_back(new lock_extend(360, 180, 2, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new five_super(140, 200, 2, 6));
		//下面三句话不用改
		keys.set_flag(2, keys.get_flag(2) + 1);
		target++;
		defeat_target[target] = keys.get_flag(2) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(2) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		//添加enemy,需修改
		enemys.push_back(new five_super(580, 220, 2, -6));//分别是x，y坐标和group参数，group就是关卡id
		enemys.push_back(new five_super(440, 80, 2, 2));
		enemys.push_back(new five_super(280, 80, 2, -2));
		enemys.push_back(new five_super(140, 220, 2, 6));
		//下面三句话不用改
		keys.set_flag(2, keys.get_flag(2) + 1);
		target++;
		defeat_target[target] = keys.get_flag(2) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(2) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		//添加enemy,需修改
		enemys.push_back(new lock_extend(560, 200, 2, &(plane->position[2]), &(plane->position[3])));//分别是x，y坐标和group参数，group就是关卡id
		enemys.push_back(new lock_extend(160, 200, 2, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new three_move(360, 120, 2));
		//下面三句话不用改
		keys.set_flag(2, keys.get_flag(2) + 1);
		target++;
		defeat_target[target] = keys.get_flag(2) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(2) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		//添加enemy,需修改
		enemys.push_back(new five_super(580, 220, 2, -6));
		enemys.push_back(new five_super(140, 220, 2, 6));
		enemys.push_back(new three_move(460, 120, 2));
		enemys.push_back(new three_move(260, 120, 2));
		//下面三句话不用改
		keys.set_flag(2, keys.get_flag(2) + 1);
		target++;
		defeat_target[target] = keys.get_flag(2) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(2) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		enemys.push_back(new boss_2(360, 120, 2, &(plane->position[2]), &(plane->position[3])));
		keys.set_flag(2, keys.get_flag(2) + 1);
		target++;
		defeat_target[target] = keys.get_flag(2) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(2) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		note(0, 500, 720, 70, 60, 0, LIGHTGREEN, WHITE, L"STAGE02 COMPLETE!");
		static int count = 0;
		count++;
		if (count == FPS * 5) {
			keys.stage = 2;
			set_current_index(4);
			defeat_target.clear();
			bgm_id = 4;
			count = 0;
		}
	}
}

void Ui::stage_3()
{
	static int target_num = 8;
	static int target = 0;
	if (defeat_target.empty()) {
		for (int i = 0; i <= target_num; i++) {
			defeat_target.push_back(0);
			target = 0;
		}
	}
	int i = 0;
	if (keys.get_flag(3) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		//添加enemy,需修改
		enemys.push_back(new lock_super(620, 240, 3, &(plane->position[2]), &(plane->position[3])));//分别是x，y坐标和group参数，group就是关卡id
		enemys.push_back(new lock_extend(360, 140, 3, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new lock_super(100, 240, 3, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_enemy(240, 180, 3));
		enemys.push_back(new simple_enemy(480, 180, 3));
		//下面三句话不用改
		keys.set_flag(3, keys.get_flag(3) + 1);
		target++;
		defeat_target[target] = keys.get_flag(3) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(3) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		//添加enemy,需修改
		enemys.push_back(new lock_simple(620, 240, 3, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new simple_three(360, 140, 3));
		enemys.push_back(new lock_simple(100, 240, 3, &(plane->position[2]), &(plane->position[3])));
		enemys.push_back(new three_move(240, 180, 3));
		enemys.push_back(new three_move(480, 180, 3));
		//下面三句话不用改
		keys.set_flag(3, keys.get_flag(3) + 1);
		target++;
		defeat_target[target] = keys.get_flag(3) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(3) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		//添加enemy,需修改
		enemys.push_back(new five_super(160, 200, 3, -1));
		enemys.push_back(new six_super(360, 140, 3));
		enemys.push_back(new five_super(560, 200, 3, 1));
		//下面三句话不用改
		keys.set_flag(3, keys.get_flag(3) + 1);
		target++;
		defeat_target[target] = keys.get_flag(3) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(3) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		//添加enemy,需修改
		enemys.push_back(new five_trans(160, 200, 3));
		enemys.push_back(new three_move(360, 140, 3));
		enemys.push_back(new five_trans(560, 200, 3));
		//下面三句话不用改
		keys.set_flag(3, keys.get_flag(3) + 1);
		target++;
		defeat_target[target] = keys.get_flag(3) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(3) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		//添加enemy,需修改
		enemys.push_back(new six_super(160, 220, 3));
		enemys.push_back(new five_trans(360, 120, 3));
		enemys.push_back(new six_super(560, 220, 3));
		//下面三句话不用改
		keys.set_flag(3, keys.get_flag(3) + 1);
		target++;
		defeat_target[target] = keys.get_flag(3) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(3) == defeat_target[i]) {
		enemys_reset();
		keys.save();
		enemys.push_back(new boss_3(360, 120, 3, &(plane->position[2]), &(plane->position[3])));
		keys.set_flag(3, keys.get_flag(3) + 1);
		target++;
		defeat_target[target] = keys.get_flag(3) + (int)enemys.size();
	}
	i++;
	if (keys.get_flag(3) == defeat_target[i]) {
		keys.save();
		enemys_reset();
		note(0, 500, 720, 70, 60, 0, LIGHTGREEN, WHITE, L"ALL STAGE COMPLETE!");
	}
}

void Ui::infinity()
{
	//使用flag和defeat目标进行对照，编写关卡下一个阶段的时候需要将target_num值手动加一
	static int target_num = 1000;
	static int target = 0;
	static int enemy_id = 0;//0~11,9,10,11为boss1，boss2，boss3
	static int position_id = 0;//用于随机分配敌机位置0~14
	static vector<int> position_buffer;//防止重复
	static int position_flag = 0;
	static int score_stage = 0;//用于标识目前分数所在的难度等级
	if (defeat_target.empty()) {
		for (int i = 0; i <= target_num; i++) {
			defeat_target.push_back(0);
			target = 0;
		}
	}
	//15个可能出现的位置
	static vector<vector<int>> enemy_position{
		{160,120},{260,120},{360,120},{460,120},{560,120},
		{160,240},{260,240},{360,240},{460,240},{560,240},
		{160,360},{260,360},{360,360},{460,360},{560,360}
	};

	//模块start
	if (keys.get_flag(4) == defeat_target[target]) {
		enemys_reset();
		position_buffer.clear();
		keys.save();

		//添加enemy,需修改group
		srand((unsigned)time(NULL));
		if (keys.score != 0) {
			score_stage = int(log2(keys.score)) - 9;
			if (score_stage < 1) {
				score_stage = 1;
			}
		}
		else {
			score_stage = 1;
		}

		while (score_stage > 0) {
			enemy_id = rand() % 12;
			position_flag = 1;

			while (position_flag == 1) {
				position_id = rand() % 15;
				position_flag = 0;
				if (!position_buffer.empty()) {
					for (auto position : position_buffer) {
						if (position == position_id) {
							position_flag = 1;
							break;
						}
					}
				}
			}
			position_buffer.push_back(position_id);

			switch (enemy_id) 
			{
			case 0:
				enemys.push_back(new simple_enemy(enemy_position[position_id][0], enemy_position[position_id][1], 4));
				break;
			case 1:
				enemys.push_back(new lock_simple(enemy_position[position_id][0], enemy_position[position_id][1], 4, &(plane->position[2]), &(plane->position[3])));
				break;
			case 2:
				enemys.push_back(new simple_three(enemy_position[position_id][0], enemy_position[position_id][1], 4));
				break;
			case 3:
				enemys.push_back(new lock_super(enemy_position[position_id][0], enemy_position[position_id][1], 4, &(plane->position[2]), &(plane->position[3])));
				break;
			case 4:
				enemys.push_back(new lock_extend(enemy_position[position_id][0], enemy_position[position_id][1], 4, &(plane->position[2]), &(plane->position[3])));
				break;
			case 5:
				enemys.push_back(new five_super(enemy_position[position_id][0], enemy_position[position_id][1], 4, position_id % 2 * 2 - 1));
				break;
			case 6:
				enemys.push_back(new three_move(enemy_position[position_id][0], enemy_position[position_id][1], 4));
				break;
			case 7:
				enemys.push_back(new six_super(enemy_position[position_id][0], enemy_position[position_id][1], 4));
				break;
			case 8:
				enemys.push_back(new five_trans(enemy_position[position_id][0], enemy_position[position_id][1], 4));
				break;
			case 9:
				if (score_stage > 1) {
					enemys.push_back(new boss_1(enemy_position[position_id][0], enemy_position[position_id][1], 4, &(plane->position[2]), &(plane->position[3])));
					score_stage--;
				}
				else {
					enemys.push_back(new simple_three(enemy_position[position_id][0], enemy_position[position_id][1], 4));
				}
				break;
			case 10:
				if (score_stage > 2) {
					enemys.push_back(new boss_2(enemy_position[position_id][0], enemy_position[position_id][1], 4, &(plane->position[2]), &(plane->position[3])));
					score_stage -= 2;
				}
				else {
					enemys.push_back(new three_move(enemy_position[position_id][0], enemy_position[position_id][1], 4));
				}
				break;
			case 11:
				if (score_stage > 3) {
					enemys.push_back(new boss_3(enemy_position[position_id][0], enemy_position[position_id][1], 4, &(plane->position[2]), &(plane->position[3])));
					score_stage -= 3;
				}
				else {
					enemys.push_back(new six_super(enemy_position[position_id][0], enemy_position[position_id][1], 4));
				}
				break;
			}
			score_stage--;
		}

		//下面三句话不用改
		keys.set_flag(4, keys.get_flag(4) + 1);
		target++;
		defeat_target[target] = keys.get_flag(4) + (int)enemys.size();
	}
	//end
}

void Ui::plane_house()
{
	//数据
	static vector<vector<int>> up_cost{
		{1,2,4,1,2,3,1},
		{4,6,2,1},
		{4,6,2,4,2},
		{4,7,3,5,2}
	};//maxlevel:8,5,6,6
	static vector<vector<int>> up_kind{
		{0,0,0,1,1,1,2},
		{0,0,1,2},
		{0,0,1,1,2},
		{0,0,1,1,2}
	};//0:star,1:moon,2:sun
	static vector<vector<int>> hps{
		{ 300,350,400,460,520,580,640,700 },
		{ 300,370,440,520,600 },
		{ 400,450,500,550,620,700 },
		{ 200,250,300,350,400,450 }
	};
	static vector<vector<int>> mps{
		{ 200,230,260,300,350,400,450,500 },
		{ 300,350,400,450,500 },
		{ 200,230,260,300,350,400 },
		{ 220,250,280,320,360,400 }
	};
	static vector<vector<int>> attacks{
		{ 100,120,140,160,180,210,240,270 },
		{ 80,110,140,175,210 },
		{ 100,120,145,170,200,230 },
		{ 130,150,180,220,260,300 }
	};
	static vector<vector<int>> shields{
		{ 0,10,20,30,40,50,55,60 },
		{ 20,35,50,60,70 },
		{ 15,30,40,50,60,70 },
		{ 10,20,30,40,45,50 }
	};
	static vector<vector<int>> strikes{
		{ 0,2,4,7,10,13,15,18 },
		{ 2,4,7,10,12 },
		{ 2,5,8,11,14,16 },
		{ 10,13,17,21,25,30 }
	};
	COLORREF color = RGB(102, 204, 255);
	static int flag = 0;
	static int temp_id = 0;
	//选择机体
	note(10, 10, 120, 50, 30, 0, LIGHTGRAY, WHITE, L"按0:退出");
	note(0, 10, 720, 50, 30, 0, LIGHTGRAY, WHITE, L"按1~4选择机体");
	if (keys.condition == 1 && keys.key_num > 48 && keys.key_num <= 52) {
		temp_id = keys.key_num - 49;
		if (keys.key_num <= keys.plane_unlock + 49) {
			flag = 0;
		}
		else {
			flag = 1;
		}
		keys.key_num = 0;
	}
	//升级界面
	if (flag == 0) {
		string text = "level:" + std::to_string(keys.plane_level[temp_id] + 1);
		wstring out1(text.begin(), text.end());
		note(0, 400, 720, 80, 60, 0, color, WHITE, out1.c_str());
		if (keys.plane_level[temp_id] >= up_cost[temp_id].size()) {
			note(0, 500, 720, 80, 60, 0, color, WHITE, L"已经是最高等级!");
		}
		else {
			string text2 = "Next Level:" + std::to_string(up_cost[temp_id][keys.plane_level[temp_id]]);
			if (up_kind[temp_id][keys.plane_level[temp_id]] == 0) {
				text2 += " star";
			}
			else if (up_kind[temp_id][keys.plane_level[temp_id]] == 1) {
				text2 += " moon";
			}
			else if (up_kind[temp_id][keys.plane_level[temp_id]] == 2) {
				text2 += " sun";
			}
			wstring out2(text2.begin(), text2.end());
			note(0, 500, 720, 80, 60, 0, color, WHITE, out2.c_str());
			note(400, 600, 200, 60, 40, 0, color, WHITE, L"升级按9");
		}
	}
	//升级花费
	if (keys.condition == 1 && keys.key_num == 57 && flag == 0 && (keys.plane_level[temp_id] < up_cost[temp_id].size())) {
		keys.key_num = 0;
		int cost = up_cost[temp_id][keys.plane_level[temp_id]];
		if (up_kind[temp_id][keys.plane_level[temp_id]] == 0 && keys.star_value >= cost) {
			keys.plane_level[temp_id]++;
			keys.star_value -= cost;
			flag = 5;
			music_id = 12;
		}
		else if (up_kind[temp_id][keys.plane_level[temp_id]] == 1 && keys.moon >= cost) {
			keys.plane_level[temp_id]++;
			keys.moon -= cost;
			flag = 5;
			music_id = 12;
		}
		else if (up_kind[temp_id][keys.plane_level[temp_id]] == 2 && keys.sun >= cost) {
			keys.plane_level[temp_id]++;
			keys.sun -= cost;
			flag = 5;
			music_id = 12;
		}
		else {
			flag = 4;
		}
	}
	//升级判定
	if (flag == 4) {
		note(80, 400, 560, 100, 70, 1, color, WHITE, L"资源不足！");
		note(400, 600, 200, 60, 40, 0, color, WHITE, L"确认按9");
	}
	if (keys.condition == 1 && keys.key_num == 57 && flag == 4) {
		flag = 0;
		keys.key_num = 0;
	}
	if (flag == 5) {
		note(80, 400, 560, 100, 70, 1, color, WHITE, L"升级成功！");
		note(400, 600, 200, 60, 40, 0, color, WHITE, L"确认按9");
	}
	if (keys.condition == 1 && keys.key_num == 57 && flag == 5) {
		flag = 0;
		keys.key_num = 0;
	}
	//解锁界面
	if (flag == 1) {
		note(180, 400, 400, 100, 80, 1, color, WHITE, L"LOCKED!");
		if (temp_id == 1)
			note(0, 500, 720, 80, 60, 0, color, WHITE, L"使用1个moon解锁?");
		if (temp_id == 2)
			note(0, 500, 720, 80, 60, 0, color, WHITE, L"使用3个moon解锁?");
		if (temp_id == 3)
			note(0, 500, 720, 80, 60, 0, color, WHITE, L"使用1个sun解锁?");
		note(400, 600, 200, 60, 40, 0, color, WHITE, L"确认按9");
	}

	//机体和名字
	put_bk_image(328, 200, keys.plane_image[temp_id]);

	if (temp_id == 0) {
		note(0, 320, 720, 40, 30, 0, color, WHITE, L"Chirno");
		note(0, 890, 720, 50, 45, 0, color, WHITE, L"无特殊被动");
	}
	else if (temp_id == 1) {
		string text6 = std::to_string(keys.plane_level[temp_id] * 5 + 5);
		wstring out6(text6.begin(), text6.end());
		note(0, 320, 720, 40, 30, 0, color, WHITE, L"Patchouli");
		note(0, 890, 720, 50, 45, 0, color, WHITE, L"每12秒恢复HP");
		note(164, 890, 720, 50, 45, 0, color, WHITE, out6.c_str());
	}
	else if (temp_id == 2) {
		note(0, 320, 720, 40, 30, 0, color, WHITE, L"Sanae");
		note(0, 890, 720, 50, 45, 0, color, WHITE, L"有20%概率防御力翻倍");
	}
	else if (temp_id == 3) {
		note(0, 320, 720, 40, 30, 0, color, WHITE, L"Meirin");
		note(0, 890, 720, 50, 45, 0, color, WHITE, L"有20%概率暴击率翻倍");
	}
	//数值显示
	string text7 = "HP:" + std::to_string(hps[temp_id][keys.plane_level[temp_id]]);
	wstring hp(text7.begin(), text7.end());
	note(0, 690, 720, 30, 28, 0, color, WHITE, hp.c_str());
	text7 = "MP:" + std::to_string(mps[temp_id][keys.plane_level[temp_id]]);
	wstring mp(text7.begin(), text7.end());
	note(0, 725, 720, 30, 28, 0, color, WHITE, mp.c_str());
	text7 = "ATTACK:" + std::to_string(attacks[temp_id][keys.plane_level[temp_id]]);
	wstring attack(text7.begin(), text7.end());
	note(0, 760, 720, 30, 28, 0, color, WHITE, attack.c_str());
	text7 = "SHIELD:" + std::to_string(shields[temp_id][keys.plane_level[temp_id]]);
	wstring shield(text7.begin(), text7.end());
	note(0, 795, 720, 30, 28, 0, color, WHITE, shield.c_str());
	text7 = "STRIKE:" + std::to_string(strikes[temp_id][keys.plane_level[temp_id]]);
	wstring strike(text7.begin(), text7.end());
	note(0, 830, 720, 30, 28, 0, color, WHITE, strike.c_str());
	//资源数据
	string text3 = "star:" + std::to_string(keys.star_value);
	wstring out3(text3.begin(), text3.end());
	note(0, 940, 240, 40, 35, 0, color, WHITE, out3.c_str());
	string text4 = "moon:" + std::to_string(keys.moon);
	wstring out4(text4.begin(), text4.end());
	note(240, 940, 240, 40, 35, 0, color, WHITE, out4.c_str());
	string text5 = "sun:" + std::to_string(keys.sun);
	wstring out5(text5.begin(), text5.end());
	note(480, 940, 240, 40, 35, 0, color, WHITE, out5.c_str());

	//解锁机体
	if (keys.condition == 1 && keys.key_num == 57 && flag == 1) {
		keys.key_num = 0;
		if (temp_id == 1) {
			if (keys.moon >= 1) {
				flag = 0;
				keys.moon -= 1;
				keys.plane_unlock = 1;
			}
			else {
				flag = 3;
			}
		}
		if (temp_id == 2) {
			if (keys.plane_unlock < 1) {
				flag = 2;
			}
			if (keys.moon >= 3 && flag == 1) {
				flag = 0;
				keys.moon -= 3;
				keys.plane_unlock = 2;
			}
			else if (keys.moon < 3 && flag == 1) {
				flag = 3;
			}
		}
		if (temp_id == 3) {
			if (keys.plane_unlock < 2) {
				flag = 2;
			}
			if (keys.sun >= 1 && flag == 1) {
				flag = 0;
				keys.sun -= 1;
				keys.plane_unlock = 3;
			}
			else if (keys.sun < 1 && flag == 1) {
				flag = 3;
			}
		}
	}
	if (flag == 3) {
		note(80, 400, 560, 100, 70, 1, color, WHITE, L"所需要的资源不足");
		note(400, 600, 200, 60, 40, 0, color, WHITE, L"确认按9");
	}
	if (flag == 2) {
		note(80, 400, 560, 100, 70, 1, color, WHITE, L"需先解锁前一机体");
		note(400, 600, 200, 60, 40, 0, color, WHITE, L"确认按9");
	}
	if (keys.condition == 1 && keys.key_num == 57 && (flag == 2 || flag == 3)) {
		temp_id = 0;
		flag = 0;
		keys.key_num = 0;
	}
	//返回菜单
	if (keys.condition == 1 && keys.key_num == 48)
	{
		if (flag)
			keys.plane_id = 0;
		else
			keys.plane_id = temp_id;
		keys.key_num = 0;
		music_id = 1;
		bgm_id = 0;
		set_current_index(1);
		keys.save();
		return;
	}
}

void Ui::card_control()//卡牌相关的操控、使用
{
	//第一次进入这个函数
	static int total_hp = 0;
	static int card_skill_rand02 = 0;
	if (card_now.empty())
	{
		int first = rand() % 6;
		int second = rand() % 6;
		card_now.push_back(first);
		card_select[first]->set_pos(0);
		while (first == second) {
			srand((unsigned)time(NULL));
			second = rand() % 6;
		}
		card_now.push_back(second);
		card_select[second]->set_pos(1);
	}
	for (int pos_id : card_now)
	{
		if (pos_id == -1)
		{
			//刷新
			if (keys.timer - keys.get_flag(0) > FPS * 5) {
				if (card_skill_flag[1] == 1) {
					card_skill_flag[1] = 0;
				}
				int rand_id = rand() % 6;
				srand((unsigned)time(NULL));
				if (card_now[0] == pos_id) {
					while (rand_id == card_now[1]) {
						rand_id = rand() % 6;
						srand((unsigned)time(NULL));
					}
					card_now[0] = rand_id;
					card_select[card_now[0]]->set_pos(0);
				}
				else {
					while (rand_id == card_now[0]) {
						rand_id = rand() % 6;
						srand((unsigned)time(NULL));
					}
					card_now[1] = rand_id;
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
				//直接用 for enemy:enemys会卡死，原因未知
				for (int i = 0; i < enemys.size();i++) {
					enemys[i]->hp -= 500;
				}
				break;
			case 1:
				card_skill_flag[1] = 1;
				break;
			case 2:
				card_skill_rand02 = rand() % (enemys.size());
				enemys[card_skill_rand02]->hp -=2000;
				break;
			case 3:
				keys.mp = plane->get_maxmp();
				break;
			case 4:
				card_skill_flag[4] = 1;
				break;
			case 5:
				card_skill_flag[5] = 1;
				break;
			case 6:
				for (int i = 0; i < enemys.size(); i++) {
					enemys[i]->hp -= 300;
					enemys[i]->position[1] = enemys[i]->position[1] / 2;
					enemys[i]->position[3] = enemys[i]->position[1] + enemys[i]->height / 2;
				}
				break;
			case 7:
				card_skill_flag[7] = 1;
				break;
			case 8:
				keys.hp = plane->get_maxhp();
				break;
			case 9:
				card_skill_flag[9] = 1;
				break;
			case 10:
				card_skill_flag[10] = 1;
				break;
			case 11:
				for (int i = 0; i < enemys.size(); i++) {
					enemys[i]->hp = enemys[i]->hp / 2;
					enemys[i]->attack = enemys[i]->attack / 2;
				}
				break;
			case 12:
				card_skill_flag[12] = 1;
				break;
			case 13:
				for (int i = 0; i < enemys.size(); i++) {
					enemys[i]->hp = enemys[i]->hp - 2000;
				}
				keys.hp = keys.hp / 2;
				break;
			case 14:
				for (int i = 0; i < enemys.size(); i++) {
					enemys[i]->hp = enemys[i]->hp / 2;
					total_hp += enemys[i]->hp / 5;
				}
				keys.hp += total_hp;
				if (keys.hp > plane->get_maxhp()) {
					keys.hp = plane->get_maxhp();
				}
				total_hp = 0;
				break;
			case 15:
				plane->set_stage(plane->get_stage() + 1);
				card_skill_flag[15] = 1;
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
	if (keys.key_card == 90)//对0位置操控
	{
		if (card_now[0] == -1||card_now[1]==-1) {
			keys.key_card = 0;
			return;
		}
		if (card_select[card_now[0]]->get_state() == 0 && card_select[card_now[1]]->get_state() == 1) {
			card_select[card_now[0]]->set_state(1);
			card_select[card_now[1]]->set_state(0);
			music_id = 9;
		}
		else if (card_select[card_now[0]]->get_state() == 0) {
			card_select[card_now[0]]->set_state(1);
			music_id = 10;
		}
		else if (card_select[card_now[0]]->get_state() == 1 && card_now[1] != -1 && keys.mp >= card_select[card_now[0]]->get_cost(card_now[0])) {
			keys.mp -= card_select[card_now[0]]->get_cost(card_now[0]);
			card_select[card_now[0]]->set_state(2);
			music_id = 9;
		}
	}
	else if (keys.key_card == 88)//对1位置操控
	{
		if (card_now[0] == -1 || card_now[1] == -1) {
			keys.key_card = 0;
			return;
		}
		if (card_select[card_now[1]]->get_state() == 0 && card_select[card_now[0]]->get_state() == 1) {
			card_select[card_now[1]]->set_state(1);
			card_select[card_now[0]]->set_state(0);
			music_id = 9;
		}
		else if (card_select[card_now[1]]->get_state() == 0) {
			card_select[card_now[1]]->set_state(1);
			music_id = 10;
		}
		else if (card_select[card_now[1]]->get_state() == 1 && card_now[0] != -1 && keys.mp >= card_select[card_now[1]]->get_cost(card_now[1])) {
			keys.mp -= card_select[card_now[1]]->get_cost(card_now[1]);
			card_select[card_now[1]]->set_state(2);
			music_id = 9;
		}
	}
	keys.key_card = 0;
}

//在卡牌库界面**修改**卡牌的选择,设置界面抽卡，保存卡牌选择的id到keyhouse中,进入游戏的时候加载卡牌就行
void Ui::card_house()
{
	static int card_column = 0;
	static vector<vector<int>> card_position{
		{148,150},{268,150},{388,150},{508,150},
		{148,296},{268,296},{388,296},{508,296},
		{148,442},{268,442},{388,442},{508,442},
		{148,588},{268,588},{388,588},{508,588}
	};//id 0~15
	static vector<int> card_pos_status{
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	};
	COLORREF color = RGB(102, 204, 255);
	static vector<int> temp_select;
	if (temp_select.empty()) {
		for (auto card : keys.cards_select) {
			temp_select.push_back(card);
			card_pos_status[card] = 1;
		}
	}
	static int last_select = 0;
	//6张卡牌压入card_select中
	note(0, 10, 720, 50, 30, 0, color, WHITE, L"按9切换卡牌行，按1~4选择卡牌");
	note(0, 40, 720, 50, 30, 0, color, WHITE, L"需选择6张，少于六张保存失败");
	note(0, 940, 720, 50, 30, 0, color, WHITE, L"卡牌效果不叠加,战斗中按z,x选择卡牌,第二次选中即使用");

	if (keys.condition == 1 && keys.key_num == 57) {
		card_column++;
		if (card_column == 4) {
			card_column = 0;
		}
		keys.key_num = 0;
	}
	note(30, card_position[card_column * 4 + 1][1]+17, 64, 50, 30, 0, color, WHITE, L"THIS->");

	if (keys.condition == 1 && (keys.key_num == 49 || keys.key_num == 50 || keys.key_num == 51 || keys.key_num == 52)) {
		last_select = keys.key_num - 49 + card_column * 4;
		if (card_pos_status[last_select] != 0 || temp_select.size() < 6 && keys.cards_unlock[last_select]==1) {
			card_pos_status[last_select] = 1 - card_pos_status[last_select];
			if (card_pos_status[last_select] == 1) {
				temp_select.push_back(last_select);
			}
			else if (card_pos_status[last_select] == 0) {
				for (int i = 0; i < temp_select.size(); i++) {
					if (temp_select[i] == last_select) {
						temp_select.erase(temp_select.begin() + i);
						break;
					}
				}
			}
		}
		keys.key_num = 0;
	}
	if (keys.cards_unlock[last_select] == 0) {
		note(0, 890, 720, 50, 50, 0, color, WHITE, L"该卡牌未解锁！");
	}
	switch (last_select)
	{
	case 0:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"爱丽丝·玛格特洛依德");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"操纵魔法程度的能力/操纵人偶程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"敌方全体HP-500");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费120");
		break;
	case 1:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"琪露诺");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"操纵冷气程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"冻结自己血条五秒钟");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费150");
		break;
	case 2:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"西行寺幽幽子");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"操纵死亡程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"随机击杀一架敌机（对BOSS-2000血量）");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费100");
		break;
	case 3:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"雾雨魔理沙");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"操纵魔法程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"回满能量值");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费0");
		break;
	case 4:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"饭纲丸龙");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"操纵星空程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"下一次捡到Star时，多获得一颗star，并且武器等级+2");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费120");
		break;
	case 5:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"红美铃");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"使用气程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"接下来五次成功击中必定暴击");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费60");
		break;
	case 6:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"帕秋莉·诺蕾姬");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"使用魔法程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"击退所有的敌机，并造成300伤害");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费100");
		break;
	case 7:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"博丽灵梦");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"在空中飞翔程度的能力/操纵灵气程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"接下来三次补能道具获得的能量值翻倍");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费100");
		break;
	case 8:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"东风谷早苗");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"引发奇迹程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"将生命值回满");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费150");
		break;
	case 9:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"尔子田里乃");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"通过在背后起舞来诱导出精神力程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"下一个武器升级道具可以把武器升满");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费150");
		break;
	case 10:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"古明地觉");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"读心程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"防止武器降级三次");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费120");
		break;
	case 11:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"伊吹萃香");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"操纵密度程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"使得在场的敌机血量减半，攻击减半");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费150");
		break;
	case 12:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"洩矢诹访子");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"创造程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"接下来三次补血道具获得的能量值翻倍");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费120");
		break;
	case 13:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"比那名居天子");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"操纵大地程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"击杀全体敌方（对BOSS-2000血量），自己血量减少一半");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费180");
		break;
	case 14:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"灵乌路空");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"操控核聚变程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"使用敌方一半血量为自己回血");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费160");
		break;
	case 15:
		note(0, 750, 720, 30, 30, 0, color, WHITE, L"八云紫");
		note(0, 780, 720, 30, 30, 0, color, WHITE, L"使用境界程度的能力");
		note(0, 810, 720, 30, 30, 0, color, WHITE, L"提升自己的武器等级一级，并抵御三次伤害");
		note(0, 840, 720, 30, 30, 0, color, WHITE, L"能量花费220");
		break;
	}

	for (int i = 0; i < 16; i++) {
		put_bk_image(card_position[i][0], card_position[i][1], keys.card_image[i]);
		if (card_pos_status[i] == 1) {
			setlinecolor(color);
			rectangle(card_position[i][0], card_position[i][1], card_position[i][0] + 64, card_position[i][1] + 128);
			rectangle(card_position[i][0] - 1, card_position[i][1] - 1, card_position[i][0] + 65, card_position[i][1] + 129);
			rectangle(card_position[i][0] - 2, card_position[i][1] - 2, card_position[i][0] + 66, card_position[i][1] + 130);
			rectangle(card_position[i][0] - 3, card_position[i][1] - 3, card_position[i][0] + 67, card_position[i][1] + 131);
		}
	}

	note(10, 10, 120, 50, 30, 0, LIGHTGRAY, WHITE, L"按0:退出");
	if (keys.condition == 1 && keys.key_num == 48)
	{
		if (temp_select.size() == 6) {
			for (int i = 0; i < 6; i++) {
				keys.cards_select[i] = temp_select[i];
			}
		}
		keys.key_num = 0;
		music_id = 1;
		bgm_id = 0;
		set_current_index(1);
		keys.save();
		return;
	}

}

//加载卡牌,使用的是keyhouse中的数据
void Ui::card_load()
{
	card_select.clear();
	for (auto card : keys.cards_select) {
		card_select.push_back(new Card(card));
	}
}

void Ui::music_control()
{
	while (1)
	{
		switch (music_id)
		{
		case 0:
			break;
		case 1:
			PlaySound(L"assets/exit.wav", NULL, SND_ASYNC);
			music_id = 0;
			break;
		case 2:
			PlaySound(L"assets/damage01.wav", NULL, SND_ASYNC);
			music_id = 0;
			break;
		case 3:
			PlaySound(L"assets/damage02.wav", NULL, SND_ASYNC);
			music_id = 0;
			break;
		case 4:
			PlaySound(L"assets/damage03.wav", NULL, SND_ASYNC);
			music_id = 0;
			break;
		case 5:
			PlaySound(L"assets/damage04.wav", NULL, SND_ASYNC);
			music_id = 0;
			break;
		case 6:
			PlaySound(L"assets/damage05.wav", NULL, SND_ASYNC);
			music_id = 0;
			break;
		case 7:
			PlaySound(L"assets/damage06.wav", NULL, SND_ASYNC);
			music_id = 0;
			break;
		case 8:
			PlaySound(L"assets/enter.wav", NULL, SND_ASYNC);
			music_id = 0;
			break;
		case 9:
			PlaySound(L"assets/change.wav", NULL, SND_ASYNC);
			music_id = 0;
			break;
		case 10:
			PlaySound(L"assets/select.wav", NULL, SND_ASYNC);
			music_id = 0;
			break;
		case 11:
			PlaySound(L"assets/hit.wav", NULL, SND_ASYNC | SND_NOSTOP);
			music_id = 0;
			break;
		case 12:
			PlaySound(L"assets/upgrade.wav", NULL, SND_ASYNC);
			music_id = 0;
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
			Sleep(10);
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
			if (enemy->state == 2 || enemy->attack_flag == 0)
				continue;//敌机已经寄了就不用做判断
			else if (enemy->state == 1)
			{
				if (enemy->get_id() == 4 || enemy->get_id() == 8) {
					drops.push_back(new Drop(enemy->position[2], enemy->position[3], 4));//moon
					enemy->state = 2;
					continue;
				}
				if (enemy->get_id() == 8) {
					drops.push_back(new Drop(enemy->position[2], enemy->position[3], 5));//moon*2
					enemy->state = 2;
					continue;
				}
				if (enemy->get_id() == 11) {
					drops.push_back(new Drop(enemy->position[2], enemy->position[3], 6));//sun
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
				music_id = rand() % 6 + 2;
				srand((unsigned)time(NULL));
			}//若击中
			else if (shot->flag != 1 && sqrt(pow(abs(shot->get_x() + 16 - enemy->position[2]), 2) + pow(abs(shot->get_y() + 16 - enemy->position[3]), 2)) < 32)
			{
				if (card_skill_flag[5] == 0) {
					enemy->hp -= keys.attack * (1 + ((rand() % 100) < keys.strike));
				}
				else {
					enemy->hp -= keys.attack * 2;
					card_skill_flag[5]++;
					if (card_skill_flag[5] == 6) {
						card_skill_flag[5] = 0;
					}
				}
				shot->flag = 1;
				keys.score += keys.attack / 20;
				if (enemy->hp > 0)
					music_id = 11;
				put_bk_image((int)shot->get_x(), (int)shot->get_y(), keys.boom_image[0]);
			}
		}
	}
	//判定敌机子弹对己方的伤害
	for (auto enemy : enemys)
	{
		if (enemy->state != 0||card_skill_flag[1]==1)
			continue;//敌机已经寄了就不用做判断
		for (auto shot : enemy->shots)
		{
			if (shot->flag != 1 && sqrt(pow(abs(shot->get_x() + 16 - plane->position[2]), 2) + pow(abs(shot->get_y() + 16 - plane->position[3]), 2)) < 13)
			{
				if (card_skill_flag[15] != 0) {
					card_skill_flag[15]++;
					if (card_skill_flag[15] == 4) {
						card_skill_flag[15] = 0;
					}
					continue;
				}
				keys.hp -= (enemy->attack - keys.shield);
				if (card_skill_flag[10] == 0) {
					plane->set_stage(plane->get_stage() - 1);
				}
				else {
					card_skill_flag[10]++;
					if (card_skill_flag[10] == 4) {
						card_skill_flag[10] = 0;
					}
				}
				shot->flag = 1;
				music_id = 11;
				keys.score -= 100;
				put_bk_image((int)shot->get_x(), (int)shot->get_y(), keys.boom_image[3]);
			}
		}
		//判定碰撞
		if (sqrt(pow(abs(enemy->position[2] - plane->position[2]), 2) + pow(abs(enemy->position[3] - plane->position[3]), 2)) < 48) {
			keys.hp -= 5;
			enemy->hp -= 15;
			put_bk_image((int)plane->position[0], (int)plane->position[1] + 32, keys.boom_image[4]);
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
			keys.score += 30;
			drop->state = 1;
			switch (drop->get_id())
			{
			case 0:
				plane->set_stage(plane->get_stage() + 1);
				if (card_skill_flag[9] == 1) {
					plane->set_stage(3);
					card_skill_flag[9] = 0;
				}
				music_id = 12;
				break;
			case 1:
				if (card_skill_flag[12] != 0) {
					keys.hp += 150;
					card_skill_flag[12]++;
					if (card_skill_flag[12] == 4) {
						card_skill_flag[12] = 0;
					}
				}
				keys.hp += 150;
				if (keys.hp > plane->get_maxhp())
					keys.hp = plane->get_maxhp();
				music_id = 10;
				break;
			case 2:
				if (card_skill_flag[7] != 0) {
					keys.mp += 80;
					card_skill_flag[7]++;
					if (card_skill_flag[7] == 4) {
						card_skill_flag[7] = 0;
					}
				}
				keys.mp += 80;
				if (keys.mp > plane->get_maxmp())
					keys.mp = plane->get_maxmp();
				music_id = 10;
				break;
			case 3:
				keys.star_value++;
				if (card_skill_flag[4] == 1) {
					plane->set_stage(plane->get_stage() + 2);
					keys.star_value++;
					card_skill_flag[4] = 0;
				}
				music_id = 12;
				break;
			case 4:
				keys.moon += 2;
				music_id = 12;
				break;
			case 5:
				keys.moon += 2;
				keys.sun += 1;
				music_id = 12;
				break;
			case 6:
				keys.sun += 2;
				keys.moon += 3;
				music_id = 12;
				break;
			}
		}
	}
}

void Ui::input()
{
	static int key_shift = 0;
	ExMessage msg;
	while (true)
	{
		if (peekmessage(&msg))//如果有信息
		{
			//按键控制模块
			if (msg.message == WM_KEYDOWN && keys.condition == 0)
			{
				keys.key_any = msg.vkcode;
			}
			else if (msg.x > 5 && keys.condition == 2 && plane != nullptr && mouse_ban == 0)
			{
				keys.move[0] = msg.x;
				keys.move[1] = msg.y;
			}
		}
		if (keys.condition == 1 || keys.condition == 0) {
			for (int i = 48; i < 58; i++) {
				if (KEY_DOWN(i)){
					while (KEY_DOWN(i)) {}
					keys.key_num = i;
				}
			}
		}
		while (peekmessage(&msg)) {}//msg会有堆积，影响按键判断
		if (keys.condition == 2 && plane != nullptr)
		{
			if (KEY_DOWN(16)) {
				key_shift = 5;
			}
			else {
				key_shift = 0;
			}
			if (KEY_DOWN(48)) {
				while (KEY_DOWN(48)) {}
				keys.key_num = 48;
			}
			if (KEY_DOWN(88)) {
				while (KEY_DOWN(88)) {}
				keys.key_card = 88;
			}
			if (KEY_DOWN(90)) {
				while (KEY_DOWN(90)) {}
				keys.key_card = 90;
			}
			if (KEY_DOWN(37)) {
				keys.move[0] -= 8 - key_shift;
			}
			else if (KEY_DOWN(39)) {
				keys.move[0] += 8 - key_shift;
			}
			if (KEY_DOWN(38)) {
				keys.move[1] -= 8 - key_shift;
			}
			else if (KEY_DOWN(40)) {
				keys.move[1] += 8 - key_shift;
			}
			if (KEY_DOWN(112)) {
				while (KEY_DOWN(112)) {}
				mouse_ban = 1 - mouse_ban;
			}
		}
		Sleep(DWORD(600.0 / FPS));
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

