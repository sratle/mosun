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
	virtual int get_maxlevel() { return 0; };

	vector<Shot*> shots;
	vector<int> position{ 324,868,360,932 };//0��1����Ⱦ���꣬2��3���ж�����

protected:
	void put_bk_image(int, int, IMAGE);
	void control();//�����ƶ�����Ⱦ����
	void shot_clear();
};

//id:0
class ur : public Plane {
private:
	int hps[8]{ 300,350,400,460,520,580,640,700 };
	int mps[8]{ 200,230,260,300,350,400,450,500 };
	int attacks[8]{ 100,120,140,160,180,210,240,270 };
	int shields[8]{ 0,10,20,30,40,50,55,60 };//���׼���ֵ
	int strikes[8]{ 0,2,4,7,10,13,15,18 };//������
	int max_level = 8;
	vector<int> record_time = { 0 ,1000 ,0 };//�ӵ����볡����������
	int stage = 0;//�ӵ��׶�
	double speed = 0.8;//�ӵ������ٶ�,ԽСԽ��
public:
	void set_stage(int) override;
	int get_stage() override;
	int get_maxhp() override;
	int get_maxmp() override;
	int get_maxlevel() override;
	void skill() override;
	void upgrade() override;
	void draw() override;
	ur();
};

//id:1
class nanna : public Plane {
private:
	int hps[5]{ 300,370,440,520,600 };
	int mps[5]{ 300,350,400,450,500 };
	int attacks[5]{ 80,110,140,175,210 };
	int shields[5]{ 20,35,50,60,70 };
	int strikes[5]{ 2,4,7,10,12 };
	int max_level = 5;
	vector<int> record_time = { 0,1000,0 };
	int stage = 0;//�ӵ��׶�
	double speed = 0.8;//�ӵ������ٶ�
public:
	void set_stage(int) override;
	int get_stage() override;
	int get_maxhp() override;
	int get_maxmp() override;
	int get_maxlevel() override;
	void skill() override;
	void upgrade() override;
	void draw() override;
	nanna();
};

//id:2
class ea :public Plane {
private:
	int hps[6]{ 400,450,500,550,620,700 };
	int mps[6]{ 200,230,260,300,350,400 };
	int attacks[6]{ 100,120,145,170,200,230 };
	int shields[6]{ 15,30,40,50,60,70 };
	int strikes[6]{ 2,5,8,11,14,16 };
	int max_level = 6;
	vector<int> record_time = { 0,1000,0 };
	int stage = 0;//�ӵ��׶�
	double speed = 0.8;//�ӵ������ٶ�
public:
	void set_stage(int) override;
	int get_stage() override;
	int get_maxhp() override;
	int get_maxmp() override;
	int get_maxlevel() override;
	void skill() override;
	void upgrade() override;
	void draw() override;
	ea();
};

//id:3
class enlil :public Plane {
private:
	int hps[6]{ 200,250,300,350,400,450 };
	int mps[6]{ 220,250,280,320,360,400 };
	int attacks[6]{ 130,150,180,220,260,300 };
	int shields[6]{ 10,20,30,40,45,50 };
	int strikes[6]{ 10,13,17,21,25,30 };
	int max_level = 6;
	vector<int> record_time = { 0,1000,0 };
	int stage = 0;//�ӵ��׶�
	double speed = 0.8;//�ӵ������ٶ�
public:
	void set_stage(int) override;
	int get_stage() override;
	int get_maxhp() override;
	int get_maxmp() override;
	int get_maxlevel() override;
	void skill() override;
	void upgrade() override;
	void draw() override;
	enlil();
};