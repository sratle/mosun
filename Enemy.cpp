#include "Enemy.h"
extern keyhouse keys;
//设计最大弹速25

//simple_enemy 简单的往前发射单列子弹的飞机
simple_enemy::simple_enemy(int x, int y, int g)
{
	width = 64;
	height = 128;
	attack = 100;
	hp = 500;
	max_hp = hp;
	speed = 0.75;
	state = 0;
	group = g;
	score = 100;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void simple_enemy::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0) {
		if (record_time[2] < 10) {
			put_bk_image(position[0], position[1] + 32, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.set_flag(group, keys.get_flag(group) + 1);
		keys.score += score;
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		//判定点
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 10);
		record_time[1] += 5 + deff / 12;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	//血条
	setlinecolor(WHITE);
	setfillcolor(RED);
	setbkmode(TRANSPARENT);
	rectangle(position[2] - 32, position[3] - 64, position[2] + 32, position[3] - 56);
	solidrectangle(position[2] - 32, position[3] - 64, position[2] - 32 + 64 * ((double)hp / (double)max_hp), position[3] - 56);

	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//下面设计是需要改动的模块，子弹出鞘
		shots.push_back(new Shot(3, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 2);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//用于切换子弹形态
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//下面设计是需要改动的模块，子弹运动
		shot->set_pos(shot->get_x(), shot->get_y() + 16);
		//end
		shot->draw();
	}
	//删除模块，需改动，此处为一个子弹一组的情况
	if (shots.size() > 3 && shots[0]->flag) {
		delete shots[0];
		shots.erase(shots.begin());
	}
}

//lock_simple 简单的能够发射锁定的单列子弹的敌机
lock_simple::lock_simple(int x, int y, int g, int* x_t, int* y_t)
	:plane_x(x_t), plane_y(y_t)
{
	width = 64;
	height = 128;
	attack = 150;
	hp = 400;
	max_hp = hp;
	speed = 0.7;
	state = 0;
	group = g;
	score = 150;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void lock_simple::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0) {
		if (record_time[2] < 10) {
			put_bk_image(position[0], position[1] + 32, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 10);
		record_time[1] += 5 + deff / 12;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	//血条
	setlinecolor(WHITE);
	setfillcolor(RED);
	setbkmode(TRANSPARENT);
	rectangle(position[2] - 32, position[3] - 64, position[2] + 32, position[3] - 56);
	solidrectangle(position[2] - 32, position[3] - 64, position[2] - 32 + 64 * ((double)hp / (double)max_hp), position[3] - 56);

	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//下面设计是需要改动的模块，子弹出鞘
		shots.push_back(new Shot(3, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, position[3] - 16);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//用于切换子弹形态
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//下面设计是需要改动的模块，子弹运动
		double dx = 16.0 * (float)(*plane_x - position[2]) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
		double dy = 16.0 * (float)(*plane_y - position[3]) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
		shot->set_pos(shot->get_x() + dx, shot->get_y() + dy);
		//end
		shot->draw();
	}
	//删除模块，需改动，此处为一个子弹一组的情况
	if (shots.size() > 3 && shots[0]->flag) {
		delete shots[0];
		shots.erase(shots.begin());
	}
}

//simple_three 简单的往前发射三列子弹的飞机
simple_three::simple_three(int x, int y, int g)
{
	width = 64;
	height = 128;
	attack = 100;
	hp = 600;
	max_hp = hp;
	speed = 0.7;
	state = 0;
	group = g;
	score = 200;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void simple_three::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0) {
		if (record_time[2] < 10) {
			put_bk_image(position[0], position[1] + 32, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 12);
		record_time[1] += 5 + deff / 12;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	//血条
	setlinecolor(WHITE);
	setfillcolor(RED);
	setbkmode(TRANSPARENT);
	rectangle(position[2] - 32, position[3] - 64, position[2] + 32, position[3] - 56);
	solidrectangle(position[2] - 32, position[3] - 64, position[2] - 32 + 64 * ((double)hp / (double)max_hp), position[3] - 56);

	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//下面设计是需要改动的模块，子弹出鞘
		shots.push_back(new Shot(3, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] + 28, shots.back()->get_y() - 2);
		shots.push_back(new Shot(3, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 2);
		shots.push_back(new Shot(3, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 60, shots.back()->get_y() - 2);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//用于切换子弹形态
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//下面设计是需要改动的模块，子弹运动
		if (flag == 0) {
			shot->set_pos(shot->get_x() + 0.7, shot->get_y() + 18);
		}
		else if (flag == 1) {
			shot->set_pos(shot->get_x(), shot->get_y() + 16);
		}
		else if (flag == 2) {
			shot->set_pos(shot->get_x() - 0.7, shot->get_y() + 18);
		}
		flag++;
		if (flag == 3)
			flag = 0;
		//end
		shot->draw();
	}
	//删除模块，需改动，此处为一个子弹一组的情况
	if (shots.size() > 6 && shots[0]->flag && shots[1]->flag && shots[2]->flag) {
		delete shots[0];
		delete shots[1];
		delete shots[2];
		shots.erase(shots.begin());
		shots.erase(shots.begin());
		shots.erase(shots.begin());
	}
}

//lock_super 能够发射锁定的单列高速子弹的敌机,狙击手
lock_super::lock_super(int x, int y, int g, int* x_t, int* y_t)
	:plane_x(x_t), plane_y(y_t)
{
	width = 64;
	height = 128;
	attack = 200;
	hp = 600;
	max_hp = hp;
	speed = 1.0;
	state = 0;
	group = g;
	score = 200;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void lock_super::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0) {
		if (record_time[2] < 10) {
			put_bk_image(position[0], position[1] + 32, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 10);
		record_time[1] += 5 + deff / 12;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	//血条
	setlinecolor(WHITE);
	setfillcolor(RED);
	setbkmode(TRANSPARENT);
	rectangle(position[2] - 32, position[3] - 64, position[2] + 32, position[3] - 56);
	solidrectangle(position[2] - 32, position[3] - 64, position[2] - 32 + 64 * ((double)hp / (double)max_hp), position[3] - 56);

	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//下面设计是需要改动的模块，子弹出鞘
		double dx = 24.0 * (float)(*plane_x - position[2]) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
		double dy = 24.0 * (float)(*plane_y - position[3]) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
		shots.push_back(new Shot(4, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 6);
		shots.back()->set_dpos(dx, dy);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//用于切换子弹形态
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//下面设计是需要改动的模块，子弹运动
		shot->set_pos(shot->get_x() + shot->get_dx(), shot->get_y() + shot->get_dy());
		//end
		shot->draw();
	}
	//删除模块，需改动，此处为一个子弹一组的情况
	if (shots.size() > 3 && shots[0]->flag) {
		delete shots[0];
		shots.erase(shots.begin());
	}
}

//boss1 第一关的boss
boss_1::boss_1(int x, int y, int g, int* x_t, int* y_t)
	:plane_x(x_t), plane_y(y_t), stage(0)
{
	width = 90;
	height = 128;
	attack = 150;
	hp = 3000;
	max_hp = hp;
	speed = 0.8;
	state = 0;
	group = g;
	score = 1000;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void boss_1::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0 && stage == 1) {
		if (record_time[2] < 20) {
			put_bk_image(position[0], position[1] + 32, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(RED);
		fillcircle(position[2], record_time[1] + height / 2, 12);
		record_time[1] += 5 + deff / 20;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(RED);
	fillcircle(position[2], position[3], 6);
	//血条
	setlinecolor(WHITE);
	if (stage == 0) {
		setfillcolor(YELLOW);
	}
	else if (stage == 1) {
		setfillcolor(RED);
	}
	setbkmode(TRANSPARENT);
	rectangle(100, 50, 620, 58);
	solidrectangle(100, 50, 100 + 520 * ((double)hp / (double)max_hp), 58);

	//一阶段
	if (stage == 0)
	{
		//子弹数量
		static int num_1 = 18;
		if (hp <= 0 && state == 0)
		{
			stage = 1;
			speed = 1.0;
			hp = 3500;
			max_hp = hp;
			if (shots.empty())
				return;
			for (auto shot : shots)
				delete shot;
			shots.clear();
		}
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块，子弹出鞘
			shots.push_back(new Shot(5, 10, position[2], position[3]));
			shots.back()->set_pos(position[2] - 160, position[3] - 16);
			for (int i = 0; i < 16; i++) {
				shots.push_back(new Shot(4, 10, position[2], position[3]));
				shots.back()->set_pos(position[2] - 256 + i * 32, position[3] - 16);
			}
			shots.push_back(new Shot(5, 10, position[2], position[3]));
			shots.back()->set_pos(position[2] + 128, position[3] - 16);
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;//用于切换子弹形态
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块，子弹运动
			double dx_1 = 20.0 * (float)(*plane_x - position[2] + 144) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
			double dx_2 = 20.0 * (float)(*plane_x - position[2] - 144) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
			double dy = 20.0 * (float)(*plane_y - position[3]) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
			if (flag == 0) {
				shot->set_pos(shot->get_x() + dx_1, shot->get_y() + dy);
			}
			else if (flag == 1 || flag == 2) {
				shot->set_pos(shot->get_x() + 1, shot->get_y() + 20);
			}
			else if (flag == 3) {
				shot->set_pos(shot->get_x() + 2, shot->get_y() + 20);
			}
			else if (flag > 3 && flag <= 6) {
				shot->set_pos(shot->get_x(), shot->get_y() + 16);
			}
			else if (flag > 6 && flag < 11) {
				shot->set_pos(shot->get_x(), shot->get_y() + 12);
			}
			else if (flag >= 11 && flag < 14) {
				shot->set_pos(shot->get_x(), shot->get_y() + 16);
			}
			else if (flag == 14) {
				shot->set_pos(shot->get_x() - 2, shot->get_y() + 20);
			}
			else if (flag == 15 || flag == 16) {
				shot->set_pos(shot->get_x() - 1, shot->get_y() + 20);
			}
			else if (flag == 17) {
				shot->set_pos(shot->get_x() + dx_2, shot->get_y() + dy);
			}
			flag++;
			if (flag == 18)
				flag = 0;
			//end
			shot->draw();
		}
		//删除模块，需改动,18shots
		if (shots.size() > num_1 * 6) {
			for (int i = 0; i < num_1; i++) {
				if (shots[i]->flag != 1)
					return;
			}
			for (int i = 0; i < num_1; i++)
				delete shots[i];
			for (int i = 0; i < num_1; i++)
				shots.erase(shots.begin());
		}
	}
	//二阶段
	if (stage == 1)
	{
		//子弹数量
		static int num_2 = 18;
		if (rand_save.empty())
		{
			for (int j = 0; j < 16; j++)
			{
				for (int i = 0; i < num_2; i++)//随机方向
					rand_save.push_back(rand() % 5 - 2);
				for (int i = 0; i < num_2; i++)//随机速度
					rand_save.push_back(rand() % 8 + 6);
			}
		}
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块，子弹出鞘
			static int flag_shot = 0;
			shots.push_back(new Shot(5, 10, position[2], position[3]));
			shots.back()->set_pos(position[2] - 160, position[3] - 16);
			for (int i = 0; i < num_2 - 2; i++) {
				shots.push_back(new Shot(4, 10, position[2], position[3]));
				shots.back()->set_pos(position[2] - 256 + i * 32 + flag_shot * 64, position[3] - 16);
			}
			shots.push_back(new Shot(5, 10, position[2], position[3]));
			shots.back()->set_pos(position[2] + 128, position[3] - 16);
			flag_shot++;
			if (flag_shot == 2)
				flag_shot = -1;
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;//用于切换子弹形态
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块，子弹运动
			double dx_1 = 24.0 * (float)(*plane_x - position[2] + 144) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
			double dx_2 = 24.0 * (float)(*plane_x - position[2] - 144) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
			double dy = 24.0 * (float)(*plane_y - position[3]) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
			if (flag == 0) {
				shot->set_pos(shot->get_x() + dx_1, shot->get_y() + dy);
			}
			else if (flag > 0 && flag < 17) {
				shot->set_pos(shot->get_x() + rand_save[flag + num_2 * 2 * (flag - 1)], shot->get_y() + rand_save[num_2 + num_2 * 2 * (flag - 1) + flag]);
			}
			else if (flag == 17) {
				shot->set_pos(shot->get_x() + dx_2, shot->get_y() + dy);
			}
			flag++;
			if (flag == 18)
				flag = 0;
			//end
			shot->draw();
		}
		//删除模块，需改动,18shots
		if (shots.size() > num_2 * 6) {
			for (int i = 0; i < num_2; i++) {
				if (shots[i]->flag != 1)
					return;
			}
			for (int i = 0; i < num_2; i++)
				delete shots[i];
			for (int i = 0; i < num_2; i++)
				shots.erase(shots.begin());
		}
	}
}

int boss_1::get_id()
{
	return id;
}

//lock_extend 能够发射锁定的三列高速子弹的敌机
lock_extend::lock_extend(int x, int y, int g, int* x_t, int* y_t)
	:plane_x(x_t), plane_y(y_t)
{
	width = 64;
	height = 128;
	attack = 150;
	hp = 900;
	max_hp = hp;
	speed = 0.75;
	state = 0;
	group = g;
	score = 300;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void lock_extend::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0) {
		if (record_time[2] < 10) {
			put_bk_image(position[0], position[1] + 32, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 12);
		record_time[1] += 5 + deff / 12;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	//血条
	setlinecolor(WHITE);
	setfillcolor(RED);
	setbkmode(TRANSPARENT);
	rectangle(position[2] - 32, position[3] - 64, position[2] + 32, position[3] - 56);
	solidrectangle(position[2] - 32, position[3] - 64, position[2] - 32 + 64 * ((double)hp / (double)max_hp), position[3] - 56);
	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//下面设计是需要改动的模块，子弹出鞘
		double dx = 18.0 * (float)(*plane_x - position[2]) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
		double dy = 18.0 * (float)(*plane_y - position[3]) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));

		shots.push_back(new Shot(6, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] + 28, shots.back()->get_y() - 2);
		shots.back()->set_dpos(dx, dy);
		shots.push_back(new Shot(6, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 2);
		shots.back()->set_dpos(dx, dy);
		shots.push_back(new Shot(6, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 60, shots.back()->get_y() - 2);
		shots.back()->set_dpos(dx, dy);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//用于切换子弹形态
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//下面设计是需要改动的模块，子弹运动
		if (flag == 0) {
			shot->set_pos(shot->get_x() + shot->get_dx() * 1.2, shot->get_y() + shot->get_dy() * 1.15);
		}
		else if (flag == 1) {
			shot->set_pos(shot->get_x() + shot->get_dx(), shot->get_y() + shot->get_dy());
		}
		else if (flag == 2) {
			shot->set_pos(shot->get_x() + shot->get_dx() * 1.2, shot->get_y() + shot->get_dy() * 1.15);
		}
		flag++;
		if (flag == 3)
			flag = 0;
		//end
		shot->draw();
	}
	//删除模块，需改动，此处为一个子弹一组的情况
	static int num_2 = 3;
	if (shots.size() > num_2 * 6) {
		for (int i = 0; i < num_2; i++) {
			if (shots[i]->flag != 1)
				return;
		}
		for (int i = 0; i < num_2; i++)
			delete shots[i];
		for (int i = 0; i < num_2; i++)
			shots.erase(shots.begin());
	}
}

//five_super 能够发射五列子弹的敌机
five_super::five_super(int x, int y, int g, int r)
	:rotate(r)
{
	width = 64;
	height = 128;
	attack = 150;
	hp = 1000;
	max_hp = hp;
	speed = 1.0;
	state = 0;
	group = g;
	score = 300;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void five_super::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0) {
		if (record_time[2] < 10) {
			put_bk_image(position[0], position[1] + 32, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 12);
		record_time[1] += 5 + deff / 12;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	//血条
	setlinecolor(WHITE);
	setfillcolor(RED);
	setbkmode(TRANSPARENT);
	rectangle(position[2] - 32, position[3] - 64, position[2] + 32, position[3] - 56);
	solidrectangle(position[2] - 32, position[3] - 64, position[2] - 32 + 64 * ((double)hp / (double)max_hp), position[3] - 56);
	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//下面设计是需要改动的模块，子弹出鞘
		for (int i = 0; i < 5; i++) {
			shots.push_back(new Shot(20, 10, position[2], position[3]));
			shots.back()->set_pos(position[2] - 80 + i * 32, position[3] - 14);
		}
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//用于切换子弹形态
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//下面设计是需要改动的模块，子弹运动
		if (flag == 0 || flag == 2 || flag == 4) {
			shot->set_pos(shot->get_x(), shot->get_y() + 16);
		}
		else if (flag == 1 || flag == 3) {
			shot->set_pos(shot->get_x() + rotate, shot->get_y() + 18);
		}
		flag++;
		if (flag == 5)
			flag = 0;
		//end
		shot->draw();
	}
	//删除模块，需改动，此处为一个子弹一组的情况
	static int num_2 = 5;
	if (shots.size() > num_2 * 6) {
		for (int i = 0; i < num_2; i++) {
			if (shots[i]->flag != 1)
				return;
		}
		for (int i = 0; i < num_2; i++)
			delete shots[i];
		for (int i = 0; i < num_2; i++)
			shots.erase(shots.begin());
	}
}

//three_move 能够发射三列子弹的移动敌机
three_move::three_move(int x, int y, int g)
	:left_x(x - 100), right_x(x + 100)
{
	width = 64;
	height = 128;
	attack = 150;
	hp = 900;
	max_hp = hp;
	speed = 0.9;
	state = 0;
	group = g;
	score = 350;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void three_move::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0) {
		if (record_time[2] < 10) {
			put_bk_image(position[0], position[1] + 32, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 14);
		record_time[1] += 5 + deff / 12;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//move
	static int move_flag = 0;
	if (move_flag == 0) {
		position[0] -= 2;
		position[2] -= 2;
		if (position[2] <= left_x) {
			move_flag = 1;
			position[2] = left_x;
			position[0] = left_x - width / 2;
		}
	}
	else if (move_flag == 1) {
		position[0] += 2;
		position[2] += 2;
		if (position[2] >= right_x) {
			move_flag = 0;
			position[2] = right_x;
			position[0] = right_x - width / 2;
		}
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	//血条
	setlinecolor(WHITE);
	setfillcolor(RED);
	setbkmode(TRANSPARENT);
	rectangle(position[2] - 32, position[3] - 64, position[2] + 32, position[3] - 56);
	solidrectangle(position[2] - 32, position[3] - 64, position[2] - 32 + 64 * ((double)hp / (double)max_hp), position[3] - 56);
	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//下面设计是需要改动的模块，子弹出鞘
		shots.push_back(new Shot(23, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] + 28, shots.back()->get_y() - 2);
		shots.back()->set_dpos(-5, 0);
		shots.push_back(new Shot(23, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 2);
		shots.back()->set_dpos(0, 0);
		shots.push_back(new Shot(23, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 60, shots.back()->get_y() - 2);
		shots.back()->set_dpos(5, 0);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//用于切换子弹形态
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//下面设计是需要改动的模块，子弹运动
		shot->set_pos(shot->get_x() + shot->get_dx(), shot->get_y() + 12);
		//end
		shot->draw();
	}
	//删除模块，需改动，此处为一个子弹一组的情况
	static int num_2 = 3;
	if (shots.size() > num_2 * 6) {
		for (int i = 0; i < num_2; i++) {
			if (shots[i]->flag != 1)
				return;
		}
		for (int i = 0; i < num_2; i++)
			delete shots[i];
		for (int i = 0; i < num_2; i++)
			shots.erase(shots.begin());
	}
}

//boss2 第二关的boss
boss_2::boss_2(int x, int y, int g, int* x_t, int* y_t)
	:plane_x(x_t), plane_y(y_t), stage(0), left_x(x - 40), right_x(x + 40)
{
	width = 92;
	height = 104;
	attack = 150;
	hp = 5000;
	max_hp = hp;
	speed = 1.4;
	state = 0;
	group = g;
	score = 1200;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void boss_2::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0 && stage == 1) {
		if (record_time[2] < 20) {
			put_bk_image(position[0], position[1] + 20, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(RED);
		fillcircle(position[2], record_time[1] + height / 2, 12);
		record_time[1] += 5 + deff / 20;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(RED);
	fillcircle(position[2], position[3], 6);
	//血条
	setlinecolor(WHITE);
	if (stage == 0) {
		setfillcolor(YELLOW);
	}
	else if (stage == 1) {
		setfillcolor(RED);
	}
	setbkmode(TRANSPARENT);
	rectangle(100, 50, 620, 58);
	solidrectangle(100, 50, 100 + 520 * ((double)hp / (double)max_hp), 58);
	//一阶段
	static double scale = 0.9;//子弹速度系数
	if (stage == 0)
	{
		static int move_flag = 0;
		if (move_flag == 0) {
			position[0] -= 3;
			position[2] -= 3;
			if (position[2] <= left_x) {
				move_flag = 1;
				position[2] = left_x;
				position[0] = left_x - width / 2;
			}
		}
		else if (move_flag == 1) {
			position[0] += 3;
			position[2] += 3;
			if (position[2] >= right_x) {
				move_flag = 0;
				position[2] = right_x;
				position[0] = right_x - width / 2;
			}
		}
		//子弹数量
		static int num_1 = 18;
		if (hp <= 0 && state == 0)
		{
			stage = 1;
			speed = 1.1;
			hp = 6000;
			max_hp = hp;
			if (shots.empty())
				return;
			for (auto shot : shots)
				delete shot;
			shots.clear();
		}
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块，子弹出鞘
			for (int i = 0; i < 18; i++) {
				shots.push_back(new Shot(22, 10, position[2], position[3]));
				shots.back()->set_pos(position[2] - 288 + i * 32, position[3] - 16);
				shots.back()->set_dpos(double(i) - 8.5, sqrt(9 * 9 - pow(double(i) - 8.5, 2)));
				shots.back()->flag = 4;
			}
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;//用于切换子弹形态
		//反弹设计
		for (auto shot : shots)
		{
			if (((shot->get_x() < 0) || (shot->get_x() > 688)) && (shot->flag == 4)) {
				shot->flag = 2;
			}
			else if (((shot->get_x() < 0) || (shot->get_x() > 688)) && (shot->flag == 2)) {
				shot->flag = 4;
			}
			else if ((shot->get_y() < 0) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块，子弹运动
			shot->set_pos(shot->get_x() + scale * (shot->get_dx() * (shot->flag - 3)), shot->get_y() + scale * shot->get_dy());
			//end
			shot->draw();
		}
		//删除模块，需改动,18shots
		if (shots.size() > num_1 * 6) {
			for (int i = 0; i < num_1; i++) {
				if (shots[i]->flag != 1)
					return;
			}
			for (int i = 0; i < num_1; i++)
				delete shots[i];
			for (int i = 0; i < num_1; i++)
				shots.erase(shots.begin());
		}
	}
	//二阶段
	if (stage == 1)
	{
		static int move_flag = 0;
		if (move_flag == 0) {
			position[0] -= 3;
			position[2] -= 3;
			if (position[2] <= left_x) {
				move_flag = 1;
				position[2] = left_x;
				position[0] = left_x - width / 2;
			}
		}
		else if (move_flag == 1) {
			position[0] += 3;
			position[2] += 3;
			if (position[2] >= right_x) {
				move_flag = 0;
				position[2] = right_x;
				position[0] = right_x - width / 2;
			}
		}
		//子弹数量
		static int num_2 = 18;
		if (rand_save.empty())
		{
			for (int j = 0; j < num_2; j++)
			{
				for (int i = 0; i < num_2; i++)//随机速度
					rand_save.push_back(rand() % 8 + 5);
			}
		}
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块，子弹出鞘
			for (int i = 0; i < 18; i++) {
				shots.push_back(new Shot(22, 10, position[2], position[3]));
				shots.back()->set_pos(position[2] - 288 + i * 32, position[3] - 16);
				shots.back()->set_dpos(double(i) - rand_save[i * (rand() % 18)], sqrt(rand_save[i * (rand() % 18)] * rand_save[i * (rand() % 18)] + 2 - pow(double(i) - rand_save[i * (rand() % 18)], 2)));
				shots.back()->flag = 4;
			}
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;//用于切换子弹形态
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_x() > 720) && (shot->flag == 4)) {
				shot->flag = 2;
			}
			else if ((shot->get_x() < 0) || (shot->get_x() > 720) && (shot->flag == 2)) {
				shot->flag = 4;
			}
			else if ((shot->get_y() < 0) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块，子弹运动
			shot->set_pos(shot->get_x() + scale * (shot->get_dx() * (shot->flag - 3)), shot->get_y() + scale * shot->get_dy());
			//end
			shot->draw();
		}
		//删除模块，需改动,18shots
		if (shots.size() > num_2 * 6) {
			for (int i = 0; i < num_2; i++) {
				if (shots[i]->flag != 1)
					return;
			}
			for (int i = 0; i < num_2; i++)
				delete shots[i];
			for (int i = 0; i < num_2; i++)
				shots.erase(shots.begin());
		}
	}
}

int boss_2::get_id()
{
	return id;
}

//six_super 往前发射六列子弹的飞机
six_super::six_super(int x, int y, int g)
{
	width = 64;
	height = 128;
	attack = 150;
	hp = 1400;
	max_hp = hp;
	speed = 0.75;
	state = 0;
	group = g;
	score = 400;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void six_super::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0) {
		if (record_time[2] < 10) {
			put_bk_image(position[0], position[1] + 32, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 12);
		record_time[1] += 5 + deff / 12;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	//血条
	setlinecolor(WHITE);
	setfillcolor(RED);
	setbkmode(TRANSPARENT);
	rectangle(position[2] - 32, position[3] - 64, position[2] + 32, position[3] - 56);
	solidrectangle(position[2] - 32, position[3] - 64, position[2] - 32 + 64 * ((double)hp / (double)max_hp), position[3] - 56);
	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//下面设计是需要改动的模块，子弹出鞘
		shots.push_back(new Shot(23, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 48, shots.back()->get_y() - 16);
		shots.back()->set_dpos(-5, 16);
		shots.push_back(new Shot(22, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 48, shots.back()->get_y() - 16);
		shots.back()->set_dpos(0, 18);
		shots.push_back(new Shot(23, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 48, shots.back()->get_y() - 16);
		shots.back()->set_dpos(5, 16);
		shots.push_back(new Shot(23, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] + 16, shots.back()->get_y() + 16);
		shots.back()->set_dpos(-5, 16);
		shots.push_back(new Shot(22, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] + 16, shots.back()->get_y() + 16);
		shots.back()->set_dpos(0, 18);
		shots.push_back(new Shot(23, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] + 16, shots.back()->get_y() + 16);
		shots.back()->set_dpos(5, 16);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//用于切换子弹形态
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//下面设计是需要改动的模块，子弹运动
		shot->set_pos(shot->get_x() + shot->get_dx(), shot->get_y() + shot->get_dy());
		//end
		shot->draw();
	}
	//删除模块，需改动，此处为一个子弹一组的情况
	static int num_2 = 6;
	if (shots.size() > num_2 * 6) {
		for (int i = 0; i < num_2; i++) {
			if (shots[i]->flag != 1)
				return;
		}
		for (int i = 0; i < num_2; i++)
			delete shots[i];
		for (int i = 0; i < num_2; i++)
			shots.erase(shots.begin());
	}
}

//five_trans 往前发射五列子弹的飞机，改变弹道
five_trans::five_trans(int x, int y, int g)
{
	width = 64;
	height = 128;
	attack = 150;
	hp = 1600;
	max_hp = hp;
	speed = 0.7;
	state = 0;
	group = g;
	score = 450;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void five_trans::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0) {
		if (record_time[2] < 10) {
			put_bk_image(position[0], position[1] + 32, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 12);
		record_time[1] += 5 + deff / 12;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	//血条
	setlinecolor(WHITE);
	setfillcolor(RED);
	setbkmode(TRANSPARENT);
	rectangle(position[2] - 32, position[3] - 64, position[2] + 32, position[3] - 56);
	solidrectangle(position[2] - 32, position[3] - 64, position[2] - 32 + 64 * ((double)hp / (double)max_hp), position[3] - 56);
	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//下面设计是需要改动的模块，子弹出鞘
		shots.push_back(new Shot(19, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 16);
		shots.back()->set_dpos(0, 20);
		shots.push_back(new Shot(23, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 48, shots.back()->get_y() - 16);
		shots.back()->set_dpos(-3, 16);
		shots.back()->flag = 2;
		shots.push_back(new Shot(23, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 48, shots.back()->get_y() - 16);
		shots.back()->set_dpos(-6, 18);
		shots.back()->flag = 2;
		shots.push_back(new Shot(22, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] + 16, shots.back()->get_y() - 16);
		shots.back()->set_dpos(3, 16);
		shots.back()->flag = 2;
		shots.push_back(new Shot(22, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] + 16, shots.back()->get_y() - 16);
		shots.back()->set_dpos(6, 18);
		shots.back()->flag = 2;
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//用于切换子弹形态
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//下面设计是需要改动的模块，子弹运动
		if (shot->flag > 1)
			shot->flag++;
		if (shot->flag == int(FPS * 0.6))
			shot->set_dpos(-(shot->get_dx() * 2), shot->get_dy() - 6);
		shot->set_pos(shot->get_x() + shot->get_dx(), shot->get_y() + shot->get_dy());
		//end
		shot->draw();
	}
	//删除模块，需改动，此处为一个子弹一组的情况
	static int num_2 = 5;
	if (shots.size() > num_2 * 6) {
		for (int i = 0; i < num_2; i++) {
			if (shots[i]->flag != 1)
				return;
		}
		for (int i = 0; i < num_2; i++)
			delete shots[i];
		for (int i = 0; i < num_2; i++)
			shots.erase(shots.begin());
	}
}

//boss3 第三关的boss
boss_3::boss_3(int x, int y, int g, int* x_t, int* y_t)
	:plane_x(x_t), plane_y(y_t), stage(0), left_x(x - 60), right_x(x + 60)
{
	width = 116;
	height = 120;
	attack = 150;
	hp = 8000;
	max_hp = hp;
	speed = 0.8;
	state = 0;
	group = g;
	score = 2000;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void boss_3::draw()
{
	if (state != 0)
		return;
	if (hp <= 0 && state == 0 && stage == 1) {
		if (record_time[2] < 20) {
			put_bk_image(position[0], position[1] + 20, keys.boom_image[record_time[2] % 5]);
			record_time[2]++;
			return;
		}
		state = 1;
		keys.score += score;
		keys.set_flag(group, keys.get_flag(group) + 1);
		return;
	}
	//入场动画
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(RED);
		fillcircle(position[2], record_time[1] + height / 2, 12);
		record_time[1] += 5 + deff / 20;
		return;
	}
	else if (attack_flag == 0) {
		attack_flag = 1;
	}
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(RED);
	fillcircle(position[2], position[3], 6);
	//血条
	setlinecolor(WHITE);
	if (stage == 0) {
		setfillcolor(YELLOW);
	}
	else if (stage == 1) {
		setfillcolor(RED);
	}
	setbkmode(TRANSPARENT);
	rectangle(100, 50, 620, 58);
	solidrectangle(100, 50, 100 + 520 * ((double)hp / (double)max_hp), 58);
	//一阶段
	if (stage == 0)
	{
		static int move_flag = 0;
		if (move_flag == 0) {
			position[0] -= 3;
			position[2] -= 3;
			if (position[2] <= left_x) {
				move_flag = 1;
				position[2] = left_x;
				position[0] = left_x - width / 2;
			}
		}
		else if (move_flag == 1) {
			position[0] += 3;
			position[2] += 3;
			if (position[2] >= right_x) {
				move_flag = 0;
				position[2] = right_x;
				position[0] = right_x - width / 2;
			}
		}
		//子弹数量
		static int num_1 = 24;
		if (hp <= 0 && state == 0)
		{
			stage = 1;
			speed = 0.8;
			hp = 10000;
			max_hp = hp;
			if (shots.empty())
				return;
			for (auto shot : shots)
				delete shot;
			shots.clear();
		}
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块，子弹出鞘
			srand((unsigned)time(NULL));
			for (int i = 0; i < 6; i++) {
				shots.push_back(new Shot(22, 10, position[2], position[3]));
				shots.back()->set_pos(position[2] + 124, position[3] + 180);
				shots.back()->set_dpos(i * 2 - 5, sqrt(8 * 8 - pow(i * 2 - 5, 2)));
			}
			for (int i = 0; i < 6; i++) {
				shots.push_back(new Shot(22, 10, position[2], position[3]));
				shots.back()->set_pos(position[2] - 156, position[3] + 180);
				shots.back()->set_dpos(i * 2 - 5, sqrt(8 * 8 - pow(i * 2 - 5, 2)));
			}
			for (int i = 0; i < 6; i++) {
				shots.push_back(new Shot(23, 10, position[2], position[3]));
				shots.back()->set_pos(100, 100 + i * 80);
				shots.back()->set_dpos((i - 8) / 2.0, i + 2);
			}
			for (int i = 0; i < 6; i++) {
				shots.push_back(new Shot(23, 10, position[2], position[3]));
				shots.back()->set_pos(620, 100 + i * 80);
				shots.back()->set_dpos((8 - i) / 2.0, i + 2);
			}
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;//用于切换子弹形态
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块，子弹运动
			shot->set_pos(shot->get_x() + shot->get_dx() * (shot->flag - 3), shot->get_y() + shot->get_dy());
			//end
			shot->draw();
		}
		//删除模块，需改动
		if (shots.size() > num_1 * 6) {
			for (int i = 0; i < num_1; i++) {
				if (shots[i]->flag != 1)
					return;
			}
			for (int i = 0; i < num_1; i++)
				delete shots[i];
			for (int i = 0; i < num_1; i++)
				shots.erase(shots.begin());
		}
	}
	//二阶段
	if (stage == 1)
	{
		static int move_flag = 0;
		if (move_flag == 0) {
			position[0] -= 3;
			position[2] -= 3;
			if (position[2] <= left_x) {
				move_flag = 1;
				position[2] = left_x;
				position[0] = left_x - width / 2;
			}
		}
		else if (move_flag == 1) {
			position[0] += 3;
			position[2] += 3;
			if (position[2] >= right_x) {
				move_flag = 0;
				position[2] = right_x;
				position[0] = right_x - width / 2;
			}
		}
		//子弹数量
		static int num_2 = 24;
		if (rand_save.empty())
		{
			for (int j = 0; j < num_2; j++)
			{
				for (int i = 0; i < num_2; i++)//随机速度
					rand_save.push_back(rand() % 8 + 4);
			}
		}
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块，子弹出鞘
			for (int i = 0; i < 23; i++) {
				shots.push_back(new Shot(24, 10, position[2], position[3]));
				shots.back()->set_pos(position[2] - 280 + i * 24, position[3] - 16);
				shots.back()->set_dpos(double(i) / 2 - rand_save[i * (rand() % 23)], sqrt(rand_save[i * (rand() % 23)] * rand_save[i * (rand() % 23)] + 2 - pow(double(i) / 2 - rand_save[i * (rand() % 18)], 2)));
				shots.back()->flag = 4;
			}
			shots.push_back(new Shot(17, 10, position[2], position[3]));
			shots.back()->set_pos(*plane_x, position[3] - 16);
			shots.back()->set_dpos(0, 25);
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;//用于切换子弹形态
		for (auto shot : shots)
		{
			if (((shot->get_x() < 0) || (shot->get_x() > 688)) && (shot->flag == 4)) {
				shot->flag = 2;
			}
			else if (((shot->get_x() < 0) || (shot->get_x() > 688)) && (shot->flag == 2)) {
				shot->flag = 4;
			}
			else if ((shot->get_y() < 0) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块，子弹运动
			shot->set_pos(shot->get_x() + shot->get_dx() * (shot->flag - 3), shot->get_y() + shot->get_dy());
			//end
			shot->draw();
		}
		//删除模块，需改动,18shots
		if (shots.size() > num_2 * 6) {
			for (int i = 0; i < num_2; i++) {
				if (shots[i]->flag != 1)
					return;
			}
			for (int i = 0; i < num_2; i++)
				delete shots[i];
			for (int i = 0; i < num_2; i++)
				shots.erase(shots.begin());
		}
	}
}

int boss_3::get_id()
{
	return id;
}

void Enemy::put_bk_image(int x, int y, IMAGE img)
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
