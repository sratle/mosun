#include "Enemy.h"
extern keyhouse keys;

//simple_enemy 简单的往前发射单列子弹的飞机
simple_enemy::simple_enemy(int x, int y, int g)
	:width(64), height(128)
{
	attack = 150;
	hp = 500;
	speed = 0.3;
	state = 0;
	group = g;
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
		state = 1;
		keys.set_flag(group, keys.get_flag(1) + 1);
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
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
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
	:width(64), height(128), plane_x(x_t), plane_y(y_t)
{
	attack = 150;
	hp = 400;
	speed = 0.3;
	state = 0;
	group = g;
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
		state = 1;
		keys.set_flag(group, keys.get_flag(1) + 1);
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
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
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
	:width(64), height(128)
{
	attack = 150;
	hp = 600;
	speed = 0.25;
	state = 0;
	group = g;
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
		state = 1;
		keys.set_flag(group, keys.get_flag(1) + 1);
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
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
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
		shot->set_pos(shot->get_x(), shot->get_y() + 16);
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
	:width(64), height(128), plane_x(x_t), plane_y(y_t)
{
	attack = 300;
	hp = 600;
	speed = 0.6;
	state = 0;
	group = g;
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
		state = 1;
		keys.set_flag(group, keys.get_flag(1) + 1);
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
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//下面设计是需要改动的模块，子弹出鞘
		shots.push_back(new Shot(4, 10, position[2], position[3]));
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
		double dx = 24.0 * (float)(*plane_x - position[2]) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
		double dy = 24.0 * (float)(*plane_y - position[3]) / (float)(abs(*plane_y - position[3]) + abs(*plane_x - position[2]));
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

//boss1 第一关的boss
boss_1::boss_1(int x, int y, int g, int* x_t, int* y_t)
	:width(90), height(128), plane_x(x_t), plane_y(y_t), stage(0)
{
	attack = 150;
	hp = 1500;
	speed = 0.6;
	state = 0;
	group = g;
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
		state = 1;
		keys.set_flag(group, keys.get_flag(1) + 1);
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
	//渲染机体
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(RED);
	fillcircle(position[2], position[3], 6);
	//一阶段
	if (stage == 0)
	{
		//子弹数量
		static int num_1 = 18;
		if (hp <= 0 && state == 0)
		{
			stage = 1;
			hp = 2000;
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
				if (shots[i]->flag == 0)
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
					rand_save.push_back(rand() % 8 + 8);
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
				if (shots[i]->flag == 0)
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
