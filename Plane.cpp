#include "Plane.h"
extern keyhouse keys;

ur::ur() {}

void ur::skill()
{
	return;
}

void ur::upgrade()
{
	keys.hp = hps[keys.plane_level[0]];
	keys.mp = mps[keys.plane_level[0]];
	keys.attack = attacks[keys.plane_level[0]];
	keys.shield = shields[keys.plane_level[0]];
	keys.strike = strikes[keys.plane_level[0]];
}

void ur::draw()//ɨ���ӵ��⣬�����ӵ����޸��ӵ����꣬Ȼ����Ⱦ�����ӵ�
{
	if (stage == 0)
	{
		//����ģ��
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//�����������Ҫ�Ķ���ģ��
			shots.push_back(new Shot(0, 3,position[2],position[3]));
			shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 2);
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0)) {
				shot->flag = 1;
			}
			//�����������Ҫ�Ķ���ģ��
			shot->set_pos(shot->get_x(), shot->get_y() - 2);
			//end
			shot->draw();
		}
		//ɾ��ģ�飬��Ķ����˴�Ϊһ���ӵ�һ������
		if (shots[0]->flag) {
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
			shots.back()->set_pos(position[2] + 8, shots.back()->get_y() - 6);
			shots.push_back(new Shot(0, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 6);
			shots.push_back(new Shot(0, 4, position[2], position[3]));
			shots.back()->set_pos(position[2] - 40, shots.back()->get_y() - 6);
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
				shot->set_pos(shot->get_x() + 1, shot->get_y() - 6);
			}
			else if (flag == 1) {
				shot->set_pos(shot->get_x(), shot->get_y() - 6);
			}
			else if (flag == 2) {
				shot->set_pos(shot->get_x() - 1, shot->get_y() - 6);
			}
			flag++;
			if (flag == 3)
				flag = 0;
			//end
			shot->draw();
		}
		//ɾ��ģ�飬��Ķ����˴�Ϊ�����ӵ�һ������
		if (shots[0]->flag & shots[1]->flag & shots[2]->flag) {
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

nanna::nanna() {}

void nanna::skill()
{
	if (keys.timer - keys.plane_time > FPS * 20) {
		keys.hp += 5 * keys.plane_level[1];
		if (keys.hp > hps[keys.plane_level[1]])
			keys.hp = hps[keys.plane_level[1]];
		keys.plane_time = keys.timer;
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

ea::ea() {}

void ea::skill()
{
	if ((keys.timer - keys.plane_time) % 2 == 0) {
		keys.shield = shields[keys.plane_level[2]] * 2;
		keys.plane_time = keys.timer;
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

enlil::enlil() {}

void enlil::skill()
{
	if ((keys.timer - keys.plane_time) % 2 == 0) {
		keys.strike = strikes[keys.plane_level[3]] * 2;
		keys.plane_time = keys.timer;
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