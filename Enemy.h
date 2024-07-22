#pragma once
#include "keyhouse.h"
#include "Shot.h"

//敌机
class Enemy
{
public:
	virtual void draw() {};
	virtual int get_id() { return 0; };
	void put_bk_image(int, int, IMAGE);

	vector<int> position;//0，1：渲染坐标，2，3：判定坐标
	vector<Shot*> shots;
	int attack = 0;
	int hp = 0;
	double speed = 0;
	int state = 0;//0:初始状态 1：死亡状态但未释放掉落物 2：已经释放掉落物
	int group = 1;
};

class simple_enemy :public Enemy
{
public:
	simple_enemy(int, int, int);//需传入初始化判定位置
	void draw() override;

private:
	const int id = 0;//标识这个敌机的id
	vector<int> record_time = { 0 , 0 , 0 };//0:标识子弹时间 1：标识入场动画 2：标识爆炸动画
	int height;
	int width;
};

class lock_simple :public Enemy
{
public:
	lock_simple(int, int, int, int*, int*);//需传入初始化判定位置,关卡id，自己飞机的坐标指针
	void draw() override;

private:
	const int id = 1;
	vector<int> record_time = { 0 , 0 ,0 };
	int height;
	int width;
	int* plane_x;
	int* plane_y;
};

class simple_three :public Enemy
{
public:
	simple_three(int, int, int);//需传入初始化判定位置
	void draw() override;

private:
	const int id = 2;//标识这个敌机的id
	vector<int> record_time = { 0 , 0 ,0 };
	int height;
	int width;
};

class lock_super :public Enemy
{
public:
	lock_super(int, int, int, int*, int*);//需传入初始化判定位置,关卡id，自己飞机的坐标指针
	void draw() override;

private:
	const int id = 3;
	vector<int> record_time = { 0 , 0,0 };
	int height;
	int width;
	int* plane_x;
	int* plane_y;
};

class boss_1 :public Enemy
{
public:
	boss_1(int, int, int, int*, int*);//需传入初始化判定位置,关卡id，自己飞机的坐标指针
	void draw() override;
	int get_id() override;

private:
	const int id = 4;
	vector<int> record_time = { 0 , 0,0 };
	vector<int> rand_save;
	int height;
	int width;
	int stage;
	int* plane_x;
	int* plane_y;
};

class lock_extend :public Enemy
{
public:
	lock_extend(int, int, int, int*, int*);//需传入初始化判定位置,关卡id，自己飞机的坐标指针
	void draw() override;

private:
	const int id = 5;
	vector<int> record_time = { 0 , 0,0 };
	int height;
	int width;
	int* plane_x;
	int* plane_y;
};