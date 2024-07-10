#pragma once
#include "keyhouse.h"
//子弹，image32*32
class Shot
{
public:
	int flag;//是否出界
	void draw();
	Shot(int,int);//id,rotate
	void set_pos(int, int);//渲染坐标x,y
	int get_x();
	int get_y();
	void set_r(int);
	int get_r();
	void set_id(int);
	int get_id();
	~Shot() {};

private:
	int x;//plane中更改坐标数据，注意此处是渲染坐标，若是调用x+16，y+16
	int y;
	int id;//子弹id
	int rotate;//0~6：向上，7~14：向下
	void put_bk_image(int, int, IMAGE);
};

