#pragma once
#include "Ui.h"
//子弹
class Shot
{
public:
	int x;//plane中更改坐标数据
	int y;
	int id;//子弹id
	int flag;//是否出界
	int rotate;
	void draw();
	Shot(int,int);
};

