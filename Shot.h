#pragma once
#include "keyhouse.h"
//�ӵ�
class Shot
{
public:
	int flag;//�Ƿ����
	void draw();
	Shot(int,int);//id,rotate
	void set_pos(int, int);//x,y
	int get_x();
	int get_y();
	void set_r(int);
	int get_r();
	void set_id(int);
	int get_id();

private:
	int x;//plane�и�����������
	int y;
	int id;//�ӵ�id
	int rotate;
	void put_bk_image(int, int, IMAGE);
};

