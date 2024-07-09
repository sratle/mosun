#pragma once
#include "keyhouse.h"
//子弹
class Shot
{
public:
	int flag;//是否出界
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
	int x;//plane中更改坐标数据
	int y;
	int id;//子弹id
	int rotate;
	void put_bk_image(int, int, IMAGE);
};

