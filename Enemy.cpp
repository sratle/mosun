#include "Enemy.h"
extern keyhouse keys;

//simple_enemy �򵥵���ǰ���䵥���ӵ��ķɻ�
simple_enemy::simple_enemy(int x, int y, int g)
	:width(64), height(128)
{
	attack = 150;
	hp = 300;
	speed = 0.6;
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
	//�볡����
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 10);
		record_time[1] += 5 + deff / 12;
		return;
	}
	//��Ⱦ����
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//�����������Ҫ�Ķ���ģ�飬�ӵ�����
		shots.push_back(new Shot(3, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 2);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//�����л��ӵ���̬
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//�����������Ҫ�Ķ���ģ�飬�ӵ��˶�
		shot->set_pos(shot->get_x(), shot->get_y() + 8);
		//end
		shot->draw();
	}
	//ɾ��ģ�飬��Ķ����˴�Ϊһ���ӵ�һ������
	if (shots.size() > 3 && shots[0]->flag) {
		delete shots[0];
		shots.erase(shots.begin());
	}
}

//lock_simple �򵥵��ܹ����������ĵ����ӵ��ĵл�
lock_simple::lock_simple(int x, int y, int g, int* x_t, int* y_t)
	:width(64), height(128), plane_x(x_t), plane_y(y_t)
{
	attack = 150;
	hp = 300;
	speed = 0.7;
	state = 0;
	group = g;
	position.push_back(x - width / 2);
	position.push_back(y - height / 2);
	position.push_back(x);
	position.push_back(y);
}

void lock_simple::draw()
{
	if (state!=0)
		return;
	if (hp <= 0 && state == 0) {
		state = 1;
		keys.set_flag(group, keys.get_flag(1) + 1);
		return;
	}
	//�볡����
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 10);
		record_time[1] += 5 + deff / 12;
		return;
	}
	//��Ⱦ����
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//�����������Ҫ�Ķ���ģ�飬�ӵ�����
		shots.push_back(new Shot(3, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 2);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//�����л��ӵ���̬
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//�����������Ҫ�Ķ���ģ�飬�ӵ��˶�
		shot->set_pos(shot->get_x() + (*plane_x - position[2]) * 6.0 / (float)(*plane_y - position[3]), shot->get_y() + 8);
		//end
		shot->draw();
	}
	//ɾ��ģ�飬��Ķ����˴�Ϊһ���ӵ�һ������
	if (shots.size() > 3 && shots[0]->flag) {
		delete shots[0];
		shots.erase(shots.begin());
	}
}

//simple_three �򵥵���ǰ���������ӵ��ķɻ�
simple_three::simple_three(int x, int y, int g)
	:width(64), height(128)
{
	attack = 150;
	hp = 500;
	speed = 0.6;
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
	//�볡����
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 12);
		record_time[1] += 5 + deff / 12;
		return;
	}
	//��Ⱦ����
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//�����������Ҫ�Ķ���ģ�飬�ӵ�����
		shots.push_back(new Shot(3, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] + 10, shots.back()->get_y() - 2);
		shots.push_back(new Shot(3, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 2);
		shots.push_back(new Shot(3, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 42, shots.back()->get_y() - 2);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//�����л��ӵ���̬
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//�����������Ҫ�Ķ���ģ�飬�ӵ��˶�
		shot->set_pos(shot->get_x(), shot->get_y() + 8);
		//end
		shot->draw();
	}
	//ɾ��ģ�飬��Ķ����˴�Ϊһ���ӵ�һ������
	if (shots.size() > 6 && shots[0]->flag && shots[1]->flag && shots[2]->flag) {
		delete shots[0];
		delete shots[1];
		delete shots[2];
		shots.erase(shots.begin());
		shots.erase(shots.begin());
		shots.erase(shots.begin());
	}
}

//lock_super �ܹ����������ĵ��и����ӵ��ĵл�,�ѻ���
lock_super::lock_super(int x, int y, int g, int* x_t, int* y_t)
	:width(64), height(128), plane_x(x_t), plane_y(y_t)
{
	attack = 300;
	hp = 400;
	speed = 0.9;
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
	//�볡����
	if (record_time[1] < position[1])
	{
		int deff = position[1] - record_time[1];
		put_bk_image(position[0], record_time[1], keys.enemy_image[id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + height / 2, 10);
		record_time[1] += 5 + deff / 12;
		return;
	}
	//��Ⱦ����
	put_bk_image(position[0], position[1], keys.enemy_image[id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 10);
	if ((keys.timer - record_time[0]) > (FPS * speed))
	{
		//�����������Ҫ�Ķ���ģ�飬�ӵ�����
		shots.push_back(new Shot(4, 10, position[2], position[3]));
		shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 2);
		//end
		record_time[0] = keys.timer;
	}
	int flag = 0;//�����л��ӵ���̬
	for (auto shot : shots)
	{
		if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
			shot->flag = 1;
		}
		//�����������Ҫ�Ķ���ģ�飬�ӵ��˶�
		shot->set_pos(shot->get_x() + (*plane_x - position[2]) * 10.0 / (float)(*plane_y - position[3]), shot->get_y() + 16);
		//end
		shot->draw();
	}
	//ɾ��ģ�飬��Ķ����˴�Ϊһ���ӵ�һ������
	if (shots.size() > 3 && shots[0]->flag) {
		delete shots[0];
		shots.erase(shots.begin());
	}
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
