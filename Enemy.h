#pragma once
#include "keyhouse.h"
#include "Shot.h"

//敌机
class Enemy
{
public:
	virtual void draw() {};
	void put_bk_image(int, int, IMAGE);
	vector<int> position;//0，1：渲染坐标，2，3：判定坐标
};

class simple_enemy :public Enemy
{
public:
	simple_enemy(int,int);//需传入初始化判定位置
	void draw() override;
	int attack;
	int hp;
	double speed;
	int state;//是否存活

private:
	vector<Shot*> shots;
	vector<int> record_time = { 0 };
	int height;
	int width;
};

