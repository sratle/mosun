#pragma once
#include "main.h"
#include "keyhouse.h"
//卡牌设计
class Card
{
public:
	Card(int);//传入id
	void draw();//0,1表明是哪张卡
	int get_id();
	int get_cost(int);
	int get_state();
	void set_state(int);
	void set_pos(int);//设置被使用到了哪个位置

private:
	vector<int> mp_cost{ 
		120,150,100,0,
		120,60,0,200,
		0,0,0,0,
		0,0,0,0 
	};//卡牌消耗
	int id;//id不可set
	int pos;
	int r_time;
	int state;//0,1,2,3标识,一般、被选中、被打出、触发效果后删除card_now,过段时间再刷新随机卡牌
	void put_bk_image(int, int, IMAGE);
};

