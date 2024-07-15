#pragma once
#include "main.h"
#include "keyhouse.h"
//µôÂäÎï,³ß´çÎª32*32
class Drop
{
public:
	void draw();
	Drop(int,int,int);
	int get_id();
	int state;
	int get_x();
	int get_y();

private:
	int id;
	int x;
	int y;
	void put_bk_image(int, int, IMAGE);
};