#include "Plane.h"
extern keyhouse keys;

ur::ur() {}

void ur::skill()
{
	return;
}

void ur::upgrade()//初始化调用
{
	keys.hp = hps[keys.plane_level[0]];
	keys.mp = mps[keys.plane_level[0]];
	keys.attack = attacks[keys.plane_level[0]];
	keys.shield = shields[keys.plane_level[0]];
	keys.strike = strikes[keys.plane_level[0]];
}

void ur::draw()//扫描子弹库，增减子弹，修改子弹坐标，然后渲染所有子弹
{
	//控制函数
	control();
	//子弹渲染
	if (stage == 0)
	{
		//复用模块
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块
			shots.push_back(new Shot(0, 3, position[2], position[3]));
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
			//下面设计是需要改动的模块
			shot->set_pos(shot->get_x(), shot->get_y() - 2);
			//end
			shot->draw();
		}
		//删除模块，需改动，此处为一个子弹一组的情况
		if (shots.size() > 3 && shots[0]->flag) {
			delete shots[0];
			shots.erase(shots.begin());
		}
		//复用end
	}
	else if (stage == 1)
	{
		//复用模块
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块
			shots.push_back(new Shot(0, 2, position[2], position[3]));
			shots.back()->set_pos(position[2] + 8, shots.back()->get_y() - 6);
			shots.push_back(new Shot(1, 3, position[2], position[3]));
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
			//下面设计是需要改动的模块
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
		//删除模块，需改动，此处为三个子弹一组的情况
		if (shots.size() > 6 && shots[0]->flag && shots[1]->flag && shots[2]->flag) {
			delete shots[0];
			delete shots[1];
			delete shots[2];
			shots.erase(shots.begin());
			shots.erase(shots.begin());
			shots.erase(shots.begin());
		}
		//复用end
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

void Plane::control()
{
	//渲染机体
	put_bk_image(position[0], position[1], keys.plane_image[keys.plane_id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 5);
	//adsw移动控制
	if (keys.condition == 2 && keys.key_move == 65)
	{
		position[0] -= 3 + 5 * keys.move_flag;
		//恢复按键编码
		keys.key_move = 0;
	}
	else if (keys.condition == 2 && keys.key_move == 68)
	{
		position[0] += 3 + 5 * keys.move_flag;
		keys.key_move = 0;
	}
	else if (keys.condition == 2 && keys.key_move == 83)
	{
		position[1] += 3 + 5 * keys.move_flag;
		keys.key_move = 0;
	}
	else if (keys.condition == 2 && keys.key_move == 87)
	{
		position[1] -= 3 + 5 * keys.move_flag;
		keys.key_move = 0;
	}//按下了capslock
	else if (keys.condition == 2 && keys.key_card == 20)
	{
		keys.move_flag = 1 - keys.move_flag;
		keys.key_card = 0;
	}//把判定坐标压入坐标中
	position[2] = position[0] + 32;
	position[3] = position[1] + 64;

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