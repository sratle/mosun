#pragma once
#include "main.h"
#include "keyhouse.h"
//�������
class Card
{
public:
	Card(int);//����id
	void draw();//0,1���������ſ�
	int get_id();
	int get_cost(int);
	int get_state();
	void set_state(int);
	void set_pos(int);//���ñ�ʹ�õ����ĸ�λ��

private:
	vector<int> mp_cost{ 
		100,120,80,0,
		100,50,0,0,
		0,0,0,0,
		0,0,0,0 
	};//��������
	int id;//id����set
	int pos;
	int r_time;
	int state;//0,1,2,3��ʶ,һ�㡢��ѡ�С������������Ч����ɾ��card_now,����ʱ����ˢ���������
	void put_bk_image(int, int, IMAGE);
};

