#pragma once
#include "keyhouse.h"
//子弹，image32*32
class Shot
{
public:
	int flag;//是否出界,判定结束
	void draw();
	Shot(int, int, int, int);//id,rotate,x,y
	void set_pos(double, double);//渲染坐标x,y
	double get_x();
	double get_y();
	void set_r(int);
	int get_r();
	void set_id(int);
	int get_id();
	~Shot() {};

private:
	double x;//plane中更改坐标数据，注意此处是渲染坐标，若是调用x+16，y+16
	double y;
	int id;//子弹id
	int rotate;//0~6：向上，7~14：向下
	void put_bk_image(int, int, IMAGE);
};

