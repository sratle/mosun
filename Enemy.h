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
	int group = 1;
};

class simple_enemy :public Enemy
{
public:
	simple_enemy(int, int,int);//�贫���ʼ���ж�λ��
	void draw() override;

private:
	const int id = 0;//��ʶ����л���id
	vector<int> record_time = { 0 , 0 };
	int height;
	int width;
};

class lock_simple :public Enemy
{
public:
	lock_simple(int, int, int,int*,int*);//�贫���ʼ���ж�λ��,�ؿ�id���Լ��ɻ�������ָ��
	void draw() override;

private:
	const int id = 1;
	vector<int> record_time = { 0 , 0 };
	int height;
	int width;
	int* plane_x;
	int* plane_y;
};

