#pragma once
#include "keyhouse.h"
#include "Shot.h"

//�л�
class Enemy
{
public:
	virtual void draw() {};
	virtual int get_id() { return 0; };
	void put_bk_image(int, int, IMAGE);

	vector<int> position;//0��1����Ⱦ���꣬2��3���ж�����
	vector<Shot*> shots;
	int attack = 0;
	int hp = 0;
	double speed = 0;
	int state = 0;//0:��ʼ״̬ 1������״̬��δ�ͷŵ����� 2���Ѿ��ͷŵ�����
	int group = 1;
};

class simple_enemy :public Enemy
{
public:
	simple_enemy(int, int, int);//�贫���ʼ���ж�λ��
	void draw() override;

private:
	const int id = 0;//��ʶ����л���id
	vector<int> record_time = { 0 , 0 , 0 };//0:��ʶ�ӵ�ʱ�� 1����ʶ�볡���� 2����ʶ��ը����
	int height;
	int width;
};

class lock_simple :public Enemy
{
public:
	lock_simple(int, int, int, int*, int*);//�贫���ʼ���ж�λ��,�ؿ�id���Լ��ɻ�������ָ��
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
	simple_three(int, int, int);//�贫���ʼ���ж�λ��
	void draw() override;

private:
	const int id = 2;//��ʶ����л���id
	vector<int> record_time = { 0 , 0 ,0 };
	int height;
	int width;
};

class lock_super :public Enemy
{
public:
	lock_super(int, int, int, int*, int*);//�贫���ʼ���ж�λ��,�ؿ�id���Լ��ɻ�������ָ��
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
	boss_1(int, int, int, int*, int*);//�贫���ʼ���ж�λ��,�ؿ�id���Լ��ɻ�������ָ��
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
	lock_extend(int, int, int, int*, int*);//�贫���ʼ���ж�λ��,�ؿ�id���Լ��ɻ�������ָ��
	void draw() override;

private:
	const int id = 5;
	vector<int> record_time = { 0 , 0,0 };
	int height;
	int width;
	int* plane_x;
	int* plane_y;
};