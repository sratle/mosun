#pragma once
#include "keyhouse.h"
#include "Shot.h"

//�л�
class Enemy
{
public:
	virtual void draw() {};
	void put_bk_image(int, int, IMAGE);

	vector<int> position;//0��1����Ⱦ���꣬2��3���ж�����
	vector<Shot*> shots;
	int attack = 0;
	int hp = 0;
	double speed = 0;
	int state = 0;//�Ƿ���
};

class simple_enemy :public Enemy
{
public:
	simple_enemy(int, int);//�贫���ʼ���ж�λ��
	void draw() override;

private:
	vector<int> record_time = { 0 , 0 };
	int height;
	int width;
};

