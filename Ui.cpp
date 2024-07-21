#include "Ui.h"
extern keyhouse keys;

Ui::Ui(int width, int height)
	:width(width), height(height), current_index(0), plane(nullptr), music_id(0), bgm_id(0)
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
		if (keys.condition == 1 && keys.key_num == 50)
		{

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

		}
		//按下5，进入设置
		if (keys.condition == 1 && keys.key_num == 53)
		{

		}
	}
	else if (current_index == 2 || current_index == 3 || current_index == 4)
	{
		COLORREF color = RGB(102, 204, 255);
		note(10, 10, 120, 50, 30, 0, LIGHTGRAY, WHITE, L"按0:退出");
		string text2 = "Stage:" + std::to_string(keys.level + 1);
		wstring out2(text2.begin(), text2.end());
		note(200, 10, 100, 50, 30, 0, color, WHITE, out2.c_str());
		string text3 = "Level:" + std::to_string(keys.plane_level[keys.plane_id] + 1);
		wstring out3(text3.begin(), text3.end());
		note(420, 10, 100, 50, 30, 0, color, WHITE, out3.c_str());
		//返回菜单
		if (keys.condition == 2 && keys.key_num == 48)
		{
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
	else if (current_index == 5)
	{

	}
	else if (current_index == 6)
	{
		plane_house();
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
		note(0, 500, 720, 70, 60, 0, LIGHTGREEN, WHITE, L"STAGE01 COMPLETE!");
	}
}

void Ui::plane_house()
{
	//数据
	static vector<vector<int>> up_cost{
		{1,2,4,1},
		{4,6,2,1},
		{4,6,2,4,2},
		{4,7,3,5,2}
	};//maxlevel:5,5,6,6
	static vector<vector<int>> up_kind{
		{0,0,0,1},
		{0,0,1,2},
		{0,0,1,1,2},
		{0,0,1,1,2}
	};//0:star,1:moon,2:sun
	static vector<vector<int>> hps{
		{300,350,420,500,600 },
		{ 300,370,450,540,650 },
		{ 400,470,550,640,740,850 },
		{ 200,250,310,380,460,550 }
	};
	static vector<vector<int>> mps{
		{200,230,260,300,360 },
		{ 300,350,400,460,520 },
		{ 200,230,260,300,350,400 },
		{ 220,250,280,320,370,420 }
	};
	static vector<vector<int>> attacks{
		{ 100,120,145,170,200 },
		{ 80,110,140,175,220 },
		{ 100,120,150,180,210,250 },
		{ 130,160,200,240,300,370 }
	};
	static vector<vector<int>> shields{
		{ 0,20,40,60,75 },
		{ 20,35,50,60,70 },
		{ 15,30,40,50,65,75 },
		{ 10,20,30,45,55,60 }
	};
	static vector<vector<int>> strikes{
		{ 0,2,4,7,10 },
		{ 2,4,7,10,13 },
		{ 2,5,8,11,15,19 },
		{ 10,13,17,22,27,35 }
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
		}
		else if (up_kind[temp_id][keys.plane_level[temp_id]] == 1 && keys.moon >= cost) {
			keys.plane_level[temp_id]++;
			keys.moon -= cost;
			flag = 5;
		}
		else if (up_kind[temp_id][keys.plane_level[temp_id]] == 2 && keys.sun >= cost) {
			keys.plane_level[temp_id]++;
			keys.sun -= cost;
			flag = 5;
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
		note(0, 900, 720, 50, 45, 0, color, WHITE, L"无特殊被动");
	}
	else if (temp_id == 1) {
		string text6 = std::to_string(keys.plane_level[temp_id] * 5 + 5);
		wstring out6(text6.begin(), text6.end());
		note(0, 320, 720, 40, 30, 0, color, WHITE, L"Patchouli");
		note(0, 900, 720, 50, 45, 0, color, WHITE, L"每12秒恢复HP");
		note(164, 900, 720, 50, 45, 0, color, WHITE, out6.c_str());
	}
	else if (temp_id == 2) {
		note(0, 320, 720, 40, 30, 0, color, WHITE, L"Sanae");
		note(0, 900, 720, 50, 45, 0, color, WHITE, L"有20%概率防御力翻倍");
	}
	else if (temp_id == 3) {
		note(0, 320, 720, 40, 30, 0, color, WHITE, L"Meirin");
		note(0, 900, 720, 50, 45, 0, color, WHITE, L"有20%概率暴击率翻倍");
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
	note(0, 950, 240, 40, 35, 0, color, WHITE, out3.c_str());
	string text4 = "moon:" + std::to_string(keys.moon);
	wstring out4(text4.begin(), text4.end());
	note(240, 950, 240, 40, 35, 0, color, WHITE, out4.c_str());
	string text5 = "sun:" + std::to_string(keys.sun);
	wstring out5(text5.begin(), text5.end());
	note(480, 950, 240, 40, 35, 0, color, WHITE, out5.c_str());

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
		return;
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
	else if (keys.key_card == 90)//对1位置操控
	{
		if (card_now[1] == -1) {
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
		else if (card_select[card_now[1]]->get_state() == 1 && card_now[0] != -1 && keys.mp > card_select[card_now[1]]->get_cost(card_now[1])) {
			keys.mp -= card_select[card_now[1]]->get_cost(card_now[1]);
			card_select[card_now[1]]->set_state(2);
			music_id = 9;
		}
	}
	keys.key_card = 0;
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
			if (enemy->state == 2)
				continue;//敌机已经寄了就不用做判断
			else if (enemy->state == 1)
			{
				if (enemy->get_id() == 4) {
					drops.push_back(new Drop(enemy->position[2], enemy->position[3], 4));//moon
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
			else if (shot->flag != 1 && sqrt(pow(abs(shot->get_x() + 16 - enemy->position[2]), 2) + pow(abs(shot->get_y() + 16 - enemy->position[3]), 2)) < 20)
			{
				enemy->hp -= keys.attack * (1 + ((rand() % 100) < keys.strike));
				shot->flag = 1;
				if (enemy->hp > 0)
					music_id = 11;
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
			if (shot->flag != 1 && sqrt(pow(abs(shot->get_x() + 16 - plane->position[2]), 2) + pow(abs(shot->get_y() + 16 - plane->position[3]), 2)) < 10)
			{
				keys.hp -= (enemy->attack - keys.shield);
				plane->set_stage(plane->get_stage() - 1);
				shot->flag = 1;
				music_id = 11;
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
			music_id = 12;
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
				keys.moon++;
				break;
			}
		}
	}
}

void Ui::input()
{
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
			else if (msg.message == WM_KEYDOWN && keys.condition == 1)
			{
				if (msg.vkcode >= 48 && msg.vkcode <= 57)
				{
					keys.key_num = msg.vkcode;
				}
			}
			else if (msg.message == WM_KEYDOWN && keys.condition == 2)
			{
				if (msg.vkcode >= 48 && msg.vkcode <= 57)
				{
					keys.key_num = msg.vkcode;
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
		Sleep(DWORD(400.0 / FPS));
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

