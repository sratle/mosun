#include "Plane.h"
extern keyhouse keys;

ur::ur() {}

void ur::skill()
{
	return;
}

void ur::upgrade()//��ʼ������
{
	keys.hp = hps[keys.plane_level[0]];
	keys.mp = mps[keys.plane_level[0]];
	keys.attack = attacks[keys.plane_level[0]];
	keys.shield = shields[keys.plane_level[0]];
	keys.strike = strikes[keys.plane_level[0]];
}

void ur::draw()//ɨ���ӵ��⣬�����ӵ����޸��ӵ����꣬Ȼ����Ⱦ�����ӵ�
{
	//�볡����
	if (record_time[1] > position[1])
	{
		put_bk_image(position[0], record_time[1], keys.plane_image[keys.plane_id]);
		setfillcolor(WHITE);
		fillcircle(position[2], record_time[1] + 64, 5);
		record_time[1] -= 5;
		return;
	}
	else
		record_time[1] = 0;
	//���ƺ���
	control();
	//�ӵ���Ⱦ
	if (stage == 0)
	{
		//����ģ��
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//�����������Ҫ�Ķ���ģ��
			shots.push_back(new Shot(0, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 2);
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;//�����л��ӵ���̬
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1280)) {
				shot->flag = 1;
			}
			//�����������Ҫ�Ķ���ģ��
			shot->set_pos(shot->get_x(), shot->get_y() - 6);
			//end
			shot->draw();
		}
		//ɾ��ģ�飬��Ķ����˴�Ϊһ���ӵ�һ������
		if (shots.size() > 3 && shots[0]->flag) {
			delete shots[0];
			shots.erase(shots.begin());
		}
		//����end
	}
	else if (stage == 1)
	{
		//����ģ��
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//�����������Ҫ�Ķ���ģ��
			shots.push_back(new Shot(0, 2, position[2], position[3]));
			shots.back()->set_pos(position[2] + 8, shots.back()->get_y() - 16);
			shots.push_back(new Shot(1, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 16);
			shots.push_back(new Shot(0, 4, position[2], position[3]));
			shots.back()->set_pos(position[2] - 40, shots.back()->get_y() - 16);
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1280)) {
				shot->flag = 1;
			}
			//�����������Ҫ�Ķ���ģ��
			if (flag == 0) {
				shot->set_pos(shot->get_x() + 2, shot->get_y() - 15);
			}
			else if (flag == 1) {
				shot->set_pos(shot->get_x(), shot->get_y() - 15);
			}
			else if (flag == 2) {
				shot->set_pos(shot->get_x() - 2, shot->get_y() - 15);
			}
			flag++;
			if (flag == 3)
				flag = 0;
			//end
			shot->draw();
		}
		//ɾ��ģ�飬��Ķ����˴�Ϊ�����ӵ�һ������
		if (shots.size() > 6 && shots[0]->flag && shots[1]->flag && shots[2]->flag) {
			delete shots[0];
			delete shots[1];
			delete shots[2];
			shots.erase(shots.begin());
			shots.erase(shots.begin());
			shots.erase(shots.begin());
		}
		//����end
	}
}

void ur::set_stage(int stage_t) {
	stage = stage_t;
	if (stage == 0)
		speed = 0.6;
	else if (stage == 1)
		speed = 0.45;
	else if (stage == 2)
		speed = 0.4;
}

int ur::get_stage() {
	return stage;
}

nanna::nanna() {}

void nanna::skill()
{
	if (keys.timer - record_time[1] > FPS * 20) {
		keys.hp += 5 * keys.plane_level[1];
		if (keys.hp > hps[keys.plane_level[1]])
			keys.hp = hps[keys.plane_level[1]];
		record_time[1] = keys.timer;
	}
}

void nanna::upgrade()
{
	keys.hp = hps[keys.plane_level[1]];
	keys.mp = mps[keys.plane_level[1]];
	keys.attack = attacks[keys.plane_level[1]];
	keys.shield = shields[keys.plane_level[1]];
	keys.strike = strikes[keys.plane_level[1]];
}

void nanna::draw()
{

}

void nanna::set_stage(int stage_t) {
	stage = stage_t;
}

int nanna::get_stage() {
	return stage;
}

ea::ea() {}

void ea::skill()
{
	if ((keys.timer - record_time[1]) % 2 == 0) {
		keys.shield = shields[keys.plane_level[2]] * 2;
		record_time[1] = keys.timer;
	}
	else {
		keys.shield = shields[keys.plane_level[2]];
	}
}

void ea::upgrade()
{
	keys.hp = hps[keys.plane_level[2]];
	keys.mp = mps[keys.plane_level[2]];
	keys.attack = attacks[keys.plane_level[2]];
	keys.shield = shields[keys.plane_level[2]];
	keys.strike = strikes[keys.plane_level[2]];
}

void ea::draw()
{

}

void ea::set_stage(int stage_t) {
	stage = stage_t;
}

int ea::get_stage() {
	return stage;
}

enlil::enlil() {}

void enlil::skill()
{
	if ((keys.timer - record_time[1]) % 2 == 0) {
		keys.strike = strikes[keys.plane_level[3]] * 2;
		record_time[1] = keys.timer;
	}
	else {
		keys.strike = strikes[keys.plane_level[3]];
	}
}

void enlil::upgrade()
{
	keys.hp = hps[keys.plane_level[3]];
	keys.mp = mps[keys.plane_level[3]];
	keys.attack = attacks[keys.plane_level[3]];
	keys.shield = shields[keys.plane_level[3]];
	keys.strike = strikes[keys.plane_level[3]];
}

void enlil::draw()
{

}

void enlil::set_stage(int stage_t) {
	stage = stage_t;
}

int enlil::get_stage() {
	return stage;
}

void Plane::control()
{
	//��Ⱦ����
	put_bk_image(position[0], position[1], keys.plane_image[keys.plane_id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 5);
	//adsw�ƶ�����
	if (keys.key_move == 65 && keys.condition == 2)
	{
		position[0] -= 4 + 4 * keys.get_flag(0);
		//���ж�����ѹ��������
		position[2] = position[0] + 32;
		//�ָ���������
		keys.key_move = 0;
	}
	else if (keys.key_move == 68 && keys.condition == 2)
	{
		position[0] += 4 + 4 * keys.get_flag(0);
		position[2] = position[0] + 32;
		keys.key_move = 0;
	}
	else if (keys.key_move == 83 && keys.condition == 2)
	{
		position[1] += 4 + 4 * keys.get_flag(0);
		position[3] = position[1] + 64;
		keys.key_move = 0;
	}
	else if (keys.key_move == 87 && keys.condition == 2)
	{
		position[1] -= 4 + 4 * keys.get_flag(0);
		position[3] = position[1] + 64;
		keys.key_move = 0;
	}//������capslock
	else if (keys.key_card == 20 && keys.condition == 2)
	{
		keys.set_flag(0, 1 - keys.get_flag(0));
		keys.key_card = 0;
	}
}

void Plane::put_bk_image(int x, int y, IMAGE img)
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