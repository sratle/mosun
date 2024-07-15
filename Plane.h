#pragma once
#include "keyhouse.h"
#include "Shot.h"

//�����ɻ�
class Plane
{
public:
	//��ų�ʼ����,�ڳ�ʼ��������Ϸ��ʱ����г�ʼ���趨
	virtual void skill() {};//����Ķ��ؼ���
	virtual void upgrade() {};//��������,�ڻ����ʼ��֮����е��ã����ص�ǰ�ȼ�������
	virtual void draw() {};//����Ŀǰ�ͷŵ��ӵ�
	virtual void set_stage(int) {};
	virtual int get_stage() { return 0; };
	virtual int get_maxhp() { return 0; };
	virtual int get_maxmp() { return 0; };
	int lock_flag = 0;

	void put_bk_image(int, int, IMAGE);
	void control();//�����ƶ�����Ⱦ����
	vector<Shot*> shots;
	vector<int> position{324,900,360,964};//0��1����Ⱦ���꣬2��3���ж�����
};

//id:0
class ur : public Plane {
private:
	int hps[5]{ 300,350,420,500,600 };
	int mps[5]{ 200,230,260,300,360 };
	int attacks[5]{ 100,120,145,170,200 };
	int shields[5]{ 0,20,40,60,75 };//���׼���ֵ
	int strikes[5]{ 0,2,4,7,10 };//������
	int max_level = 5;
	vector<int> record_time = { 0 ,1000};
	int stage = 0;//�ӵ��׶�
	double speed = 0.8;//�ӵ������ٶ�,ԽСԽ��
public:
	void set_stage(int) override;
	int get_stage() override;
	int get_maxhp() override;
	int get_maxmp() override;
	void skill() override;
	void upgrade() override;
	void draw() override;
	ur();
};

//id:1
class nanna : public Plane {
private:
	int hps[5]{ 300,370,450,540,650 };
	int mps[5]{ 300,350,400,460,520 };
	int attacks[5]{ 80,110,140,175,220 };
	int shields[5]{ 20,35,50,60,70 };
	int strikes[5]{ 2,4,7,10,13 };
	int max_level = 5;
	vector<int> record_time = { 0,1000 };
	int stage = 0;//�ӵ��׶�
	double speed = 0.8;//�ӵ������ٶ�
public:
	void set_stage(int) override;
	int get_stage() override;
	void skill() override;
	void upgrade() override;
	void draw() override;
	nanna();
};

//id:2
class ea :public Plane {
private:
	int hps[6]{ 400,470,550,640,740,850 };
	int mps[6]{ 200,230,260,300,350,400 };
	int attacks[6]{ 100,120,150,180,210,250 };
	int shields[6]{ 15,30,40,50,65,75 };
	int strikes[6]{ 2,5,8,11,15,19 };
	int max_level = 6;
	vector<int> record_time = { 0,1000 };
	int stage = 0;//�ӵ��׶�
	double speed = 0.8;//�ӵ������ٶ�
public:
	void set_stage(int) override;
	int get_stage() override;
	void skill() override;
	void upgrade() override;
	void draw() override;
	ea();
};

//id:3
class enlil :public Plane {
private:
	int hps[6]{ 200,250,310,380,460,550 };
	int mps[6]{ 220,250,280,320,370,420 };
	int attacks[6]{ 130,160,200,240,300,370 };
	int shields[6]{ 10,20,30,45,55,60 };
	int strikes[6]{ 10,13,17,22,27,35 };
	int max_level = 6;
	vector<int> record_time = { 0,1000 };
	int stage = 1;//�ӵ��׶�
	double speed = 0.8;//�ӵ������ٶ�
public:
	void set_stage(int) override;
	int get_stage() override;
	void skill() override;
	void upgrade() override;
	void draw() override;
	enlil();
};