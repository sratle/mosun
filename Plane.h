#pragma once
#include "keyhouse.h"
#include "Shot.h"

//己方飞机
class Plane
{
public:
	//存放初始数据,在初始化进入游戏的时候进行初始化设定
	virtual void skill() {};//机体的独特技能
	virtual void upgrade() {};//机体升级,在机体初始化之后进行调用，加载当前等级的数据
	virtual void draw() {};//画出目前释放的子弹
	void put_bk_image(int, int, IMAGE);
	void control();//控制移动和渲染自身
	vector<int> position{324,900,360,964};//0，1：渲染坐标，2，3：判定坐标
};

//id:1
class ur : public Plane {
private:
	int hps[5]{ 300,350,420,500,600 };
	int mps[5]{ 200,230,260,300,360 };
	int attacks[5]{ 100,120,145,170,200 };
	int shields[5]{ 0,20,40,60,75 };//护甲减免值
	int strikes[5]{ 0,2,4,7,10 };//暴击率
	int max_level = 5;
	vector<Shot*> shots;
	vector<int> record_time = { 0 };
public:
	int stage = 1;//子弹阶段
	double speed = 0.8;//子弹发射速度,越小越快
	void skill() override;
	void upgrade() override;
	void draw() override;
	ur();
};

//id:2
class nanna : public Plane {
private:
	int hps[5]{ 300,370,450,540,650 };
	int mps[5]{ 300,350,400,460,520 };
	int attacks[5]{ 80,110,140,175,220 };
	int shields[5]{ 20,35,50,60,70 };
	int strikes[5]{ 2,4,7,10,13 };
	int max_level = 5;
	vector<Shot*> shots;
	vector<int> record_time = { 0 };
public:
	int stage = 1;//子弹阶段
	double speed = 0.8;//子弹发射速度
	void skill() override;
	void upgrade() override;
	void draw() override;
	nanna();
};

//id:3
class ea :public Plane {
private:
	int hps[6]{ 400,470,550,640,740,850 };
	int mps[6]{ 200,230,260,300,350,400 };
	int attacks[6]{ 100,120,150,180,210,250 };
	int shields[6]{ 15,30,40,50,65,75 };
	int strikes[6]{ 2,5,8,11,15,19 };
	int max_level = 6;
	vector<Shot*> shots;
	vector<int> record_time = { 0 };
public:
	int stage = 1;//子弹阶段
	double speed = 0.8;//子弹发射速度
	void skill() override;
	void upgrade() override;
	void draw() override;
	ea();
};

//id:4
class enlil :public Plane {
private:
	int hps[6]{ 200,250,310,380,460,550 };
	int mps[6]{ 220,250,280,320,370,420 };
	int attacks[6]{ 130,160,200,240,300,370 };
	int shields[6]{ 10,20,30,45,55,60 };
	int strikes[6]{ 10,13,17,22,27,35 };
	int max_level = 6;
	vector<Shot*> shots;
	vector<int> record_time = { 0 };
public:
	int stage = 1;//子弹阶段
	double speed = 0.8;//子弹发射速度
	void skill() override;
	void upgrade() override;
	void draw() override;
	enlil();
};