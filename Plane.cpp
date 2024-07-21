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
	//入场动画
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
		int flag = 0;//用于切换子弹形态
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块
			shot->set_pos(shot->get_x(), shot->get_y() - 22);
			//end
			shot->draw();
		}
		//删除模块，需改动，此处为一个子弹一组的情况
		if (shots.size() > 10 && shots[0]->flag) {
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
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块
			if (flag == 0) {
				shot->set_pos(shot->get_x() + 1, shot->get_y() - 24);
			}
			else if (flag == 1) {
				shot->set_pos(shot->get_x(), shot->get_y() - 24);
			}
			else if (flag == 2) {
				shot->set_pos(shot->get_x() - 1, shot->get_y() - 24);
			}
			flag++;
			if (flag == 3)
				flag = 0;
			//end
			shot->draw();
		}
		//删除模块，需改动，此处为三个子弹一组的情况,注意调整size的值
		if (shots.size() > 18 && shots[0]->flag && shots[1]->flag && shots[2]->flag) {
			delete shots[0];
			delete shots[1];
			delete shots[2];
			shots.erase(shots.begin());
			shots.erase(shots.begin());
			shots.erase(shots.begin());
		}
		//复用end
	}
	else if (stage == 2)
	{
		//复用模块
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块
			shots.push_back(new Shot(0, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] + 20, shots.back()->get_y() - 16);
			shots.push_back(new Shot(1, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 16);
			shots.push_back(new Shot(0, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 52, shots.back()->get_y() - 16);
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块
			shot->set_pos(shot->get_x(), shot->get_y() - 24);
			//end
			shot->draw();
		}
		//删除模块，需改动，此处为三个子弹一组的情况
		if (shots.size() > 30 && shots[0]->flag && shots[1]->flag && shots[2]->flag) {
			delete shots[0];
			delete shots[1];
			delete shots[2];
			shots.erase(shots.begin());
			shots.erase(shots.begin());
			shots.erase(shots.begin());
		}
		//复用end
	}
	else if (stage == 3)
	{
		//复用模块
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块
			shots.push_back(new Shot(0, 2, position[2], position[3]));
			shots.back()->set_pos(position[2] + 32, shots.back()->get_y() - 16);
			shots.push_back(new Shot(1, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] + 16, shots.back()->get_y() - 16);
			shots.push_back(new Shot(1, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 16, shots.back()->get_y() - 16);
			shots.push_back(new Shot(1, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 48, shots.back()->get_y() - 16);
			shots.push_back(new Shot(0, 4, position[2], position[3]));
			shots.back()->set_pos(position[2] - 64, shots.back()->get_y() - 16);
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块
			if (flag == 0) {
				shot->set_pos(shot->get_x() + 1, shot->get_y() - 22);
			}
			else if (flag == 1 || flag == 2 || flag == 3) {
				shot->set_pos(shot->get_x(), shot->get_y() - 24);
			}
			else if (flag == 4) {
				shot->set_pos(shot->get_x() - 1, shot->get_y() - 22);
			}
			flag++;
			if (flag == 5)
				flag = 0;
			//end
			shot->draw();
		}
		//删除模块，需改动，此处为五个子弹一组的情况
		if (shots.size() > 30 && shots[0]->flag && shots[1]->flag && shots[2]->flag && shots[3]->flag && shots[4]->flag) {
			delete shots[0];
			delete shots[1];
			delete shots[2];
			delete shots[3];
			delete shots[4];
			shots.erase(shots.begin());
			shots.erase(shots.begin());
			shots.erase(shots.begin());
			shots.erase(shots.begin());
			shots.erase(shots.begin());
		}
		//复用end
	}
}

//增加stage之后注意改动这个函数
void ur::set_stage(int stage_t) {
	stage = stage_t;
	static int max_stage = 3;
	if (stage > max_stage) {
		stage = max_stage;
		return;
	}
	if (stage < 0) {
		stage = 0;
		return;
	}
	shot_clear();
	if (stage == 0)
		speed = 0.1;
	else if (stage == 1)
		speed = 0.2;
	else if (stage == 2)
		speed = 0.1;
	else if (stage == 3)
		speed = 0.15;
}

int ur::get_stage() {
	return stage;
}

int ur::get_maxhp() {
	return hps[keys.plane_level[0]];
}

int ur::get_maxmp() {
	return mps[keys.plane_level[0]];
}

int ur::get_maxlevel() {
	return max_level;
}

nanna::nanna() {}

void nanna::skill()
{
	if (keys.timer - record_time[2] > FPS * 12) {
		keys.hp += 5 * keys.plane_level[1] + 5;
		if (keys.hp > hps[keys.plane_level[1]])
			keys.hp = hps[keys.plane_level[1]];
		record_time[2] = keys.timer;
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
	//入场动画
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
	//控制函数
	control();
	//子弹渲染
	if (stage == 0)
	{
		//复用模块
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块
			shots.push_back(new Shot(7, 3, position[2], position[3]));
			shots.back()->set_pos(position[2]+4 , shots.back()->get_y() - 2);
			shots.push_back(new Shot(7, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 36, shots.back()->get_y() - 2);
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;//用于切换子弹形态
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块
			
			shot->set_pos(shot->get_x(), shot->get_y() - 22);
			//end
			shot->draw();
		}
		//删除模块，需改动
		if (shots.size() > 30 && shots[0]->flag && shots[1]->flag) {
			delete shots[0];
			delete shots[1];
			shots.erase(shots.begin());
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
			shots.push_back(new Shot(7, 3, position[2], position[3]));
			shots.back()->set_pos(position[2]+4, shots.back()->get_y() +12);
			shots.push_back(new Shot(7, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 36, shots.back()->get_y() +12);
			shots.push_back(new Shot(9, 3, position[2], position[3]));
			shots.back()->set_pos(position[2]+4, shots.back()->get_y() -32);
			shots.push_back(new Shot(9, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 36, shots.back()->get_y() -32);
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;//用于切换子弹形态
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
				shot->flag = 1;
			}
			//下面设计是需要改动的模块
			shot->set_pos(shot->get_x(), shot->get_y() - 20);
			//end
			shot->draw();
		}
		//删除模块，需改动，改进版本
		static int num_1 = 4;
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
		//复用end
	}
	else if (stage == 2)
	{
		//复用模块
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块
			shots.push_back(new Shot(7, 3, position[2], position[3]));
			shots.back()->set_pos(position[2]-16, shots.back()->get_y());
			shots.push_back(new Shot(7, 3, position[2], position[3]));
			shots.back()->set_pos(position[2]-56, shots.back()->get_y());
			shots.push_back(new Shot(7, 3, position[2], position[3]));
			shots.back()->set_pos(position[2]+24, shots.back()->get_y());
			shots.push_back(new Shot(9, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 36, shots.back()->get_y() -32);
			shots.push_back(new Shot(9, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] +4, shots.back()->get_y() - 32);
			shots.push_back(new Shot(11, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] -16, shots.back()->get_y() - 64);
			//end
			record_time[0] = keys.timer;
		}
		int flag = 0;//用于切换子弹形态
		for (auto shot : shots)
		{
			if ((shot->get_x() < 0) || (shot->get_y() < 0) || (shot->get_x() > 720) || (shot->get_y() > 1028)) {
				shot->flag = 1;
				continue;
			}
			//下面设计是需要改动的模块
			shot->set_pos(shot->get_x(), shot->get_y() - 18);
			//end
			shot->draw();
		}
		//删除模块，需改动，改进版本
		static int num_1 = 6;
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
		//复用end
	}
	else if (stage == 3)
	{
		//复用模块
		if ((keys.timer - record_time[0]) > (FPS * speed))
		{
			//下面设计是需要改动的模块
			shots.push_back(new Shot(7, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] +4, shots.back()->get_y()+12);
			shots.push_back(new Shot(7, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 36, shots.back()->get_y()+12);
			shots.push_back(new Shot(9, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] + 4, shots.back()->get_y()-32);
			shots.push_back(new Shot(9, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 36, shots.back()->get_y()-32);
			shots.push_back(new Shot(13, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] + 44, shots.back()->get_y()+12);
			shots.back()->flag = 2;
			shots.push_back(new Shot(13, 3, position[2], position[3]));
			shots.back()->set_pos(position[2] - 76, shots.back()->get_y()+12);
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
			//下面设计是需要改动的模块
			if (flag <= 3) {
				shot->set_pos(shot->get_x(), shot->get_y() - 20);
			}
			else if (flag == 4){
				if (shot->flag!=1)
					shot->flag++;
				if (shot->flag<26){
					shot->set_pos(shot->get_x() + 4, shot->get_y() - 16);
				}
				else {
					shot->set_pos(shot->get_x() - 4, shot->get_y() - 16);
				}
			}
			else if (flag == 5) {
				if (shot->flag != 1)
					shot->flag++;
				if (shot->flag < 26) {
					shot->set_pos(shot->get_x() - 4, shot->get_y() - 16);
				}
				else {
					shot->set_pos(shot->get_x() + 4, shot->get_y() - 16);
				}
			}
			flag++;
			if (flag ==6)
				flag = 0;
			//end
			shot->draw();
		}
		//删除模块，需改动，改进版本
			static int num_1 = 6;
		if (shots.size() > num_1 * 6) {
			for (int i = 0; i < num_1; i++) {
				if (shots[i]->flag !=1)
				     return;
			}
			for (int i = 0; i < num_1; i++)
				delete shots[i];
			for (int i = 0; i < num_1; i++)
				shots.erase(shots.begin());
		}
		//复用end
	}
}

void nanna::set_stage(int stage_t) {
	stage = stage_t;
	static int max_stage = 3;
	if (stage > max_stage) {
		stage = max_stage;
		return;
	}
	if (stage < 0) {
		stage = 0;
		return;
	}
	shot_clear();
	if (stage == 0)
		speed = 0.15;
	else if (stage == 1)
		speed = 0.2;
	else if (stage == 2)
		speed = 0.2;
	else if (stage == 3)
		speed = 0.15;
}

int nanna::get_stage() {
	return stage;
}

int nanna::get_maxhp() {
	return hps[keys.plane_level[0]];
}

int nanna::get_maxmp() {
	return mps[keys.plane_level[0]];
}

int nanna::get_maxlevel() {
	return max_level;
}

ea::ea() {}

void ea::skill()
{
	record_time[2] = rand() % 100;
	if (record_time[2]>20) {
		keys.shield = shields[keys.plane_level[2]] * 2;
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
	record_time[2] = rand() % 100;
	if (record_time[2]>20) {
		keys.strike = strikes[keys.plane_level[3]] * 2;
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
	//渲染机体
	put_bk_image(position[0], position[1], keys.plane_image[keys.plane_id]);
	setfillcolor(WHITE);
	fillcircle(position[2], position[3], 5);
	skill();
	if (abs(position[2] - keys.move[0]) > 24){
		if (position[2] > keys.move[0])
			position[2] = position[2] - 24;
		else
			position[2] = position[2] + 24;
	}
	else {
		position[2] = keys.move[0];
	}
	if (abs(position[3] - keys.move[1]) > 24) {
		if (position[3] > keys.move[1])
			position[3] = position[3] - 24;
		else
			position[3] = position[3] + 24;
	}
	else {
		position[3] = keys.move[1];
	}
	position[0] = position[2] - 32;
	position[1] = position[3] - 64;

	if (position[0] < 0) {
		position[0] = 0;
		position[2] = 32;
	}
	if (position[0] > 656) {
		position[0] = 656;
		position[2] = 688;
	}
	if (position[1] < 64) {
		position[1] = 64;
		position[3] = 128;
	}
	if (position[1] > 964) {
		position[1] = 964;
		position[3] = 1028;
	}
}

void Plane::shot_clear()
{
	if (shots.empty())
		return;
	for (auto shot : shots)
		delete shot;
	shots.clear();
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
