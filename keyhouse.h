#pragma once
#include "main.h"
#include "Card.h"
class keyhouse
{
public:
	//资源预加载
	vector<IMAGE> sakuya;
	vector<IMAGE> plane_image;
	vector<IMAGE> enemy_image;
	vector<IMAGE> shots_image;//一张图片加载七次，-30，-20，-10，0，10，20，30度
	void load_shots(LPCTSTR);
	//键盘输入
	vector<BYTE> key_any;//condition0
	vector<BYTE> key_num;//condition1
	int key_move;//condition2
	int key_card;//condition2
	//坐标数据
	vector<vector<int>> shot_self;
	vector<vector<int>> shot_enemy;
	vector<vector<int>> plane_enemy;
	vector<int> plane_self;
	//卡片数据
	vector<Card> card_all;
	vector<Card> card_select;
	vector<Card> card_now;
	//控制用变量
	int condition;
	int move_flag;
	int timer;
	int plane_time;
	int shot_time;
	int level;
	//背包资源
	int star_value;//save
	int anu;//save
	int isthar;//save
	//机体数据
	int plane_id;//从ui.planes_data中加载对应id
	int mp;
	int hp;
	int attack;
	int shield;
	int strike;
	vector<int> plane_level{ 0,0,0,0 };//save 存储四种机体的当前等级
	int plane_unlock;//顺序解锁 1~3

	keyhouse();
	void load();//将存档加载
	void save();//存档
};

