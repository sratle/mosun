#pragma once
#include "main.h"
//标save的是需要存档的
//关键数据存储其中，注意这个类不能越来越臃肿，需要根据逻辑，适当地把一些数据封装到该有的类里面
class keyhouse
{
public:
	//资源预加载
	vector<IMAGE> sakuya;//0
	vector<IMAGE> plane_image;//1
	vector<IMAGE> enemy_image;//2
	vector<IMAGE> drop_image;//3
	vector<IMAGE> boom_image;//4
	vector<IMAGE> card_image;//5
	vector<IMAGE> other_image;//6
	//一张图片加载十四次，-30，-20，-10，0，10，20，30，150，160，170，180，190，200，210度
	//1：6用10度，1：3用20度，1：2用30度
	vector<IMAGE> shots_image;
	//键盘输入
	int key_any;//condition0
	int key_num;//condition1
	int key_card;//condition2
	vector<int> move{ 360,932 };
	//控制用变量
	int condition;//键盘输入的状态变量，0：主界面模式，1：菜单模式，2：战斗模式
	int timer;//全局计时器
	int get_flag(int pos);//0:给卡牌设计刷新用 1:用于关卡1的判定，2：用于关卡2的判定，3：用于关卡3的判定，4：无尽的判定
	int get_flag_size();
	void set_flag(int pos, int val);
	int stage;//关卡
	//背包资源
	int star_value;//save
	int sun;//save
	int moon;//save
	vector<int> plane_level{ 0,0,0,0 };//save 存储四种机体的当前等级
	vector<int> cards_unlock{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//save 16张卡的解锁情况
	int plane_unlock;//save 机体解锁
	int max_score;//save
	int score;
	//机体数据,这是当前的飞机数据加载到这里，实时变化控制
	int plane_id;//从ui.planes_data中加载对应id
	int mp;
	int hp;
	int attack;
	int shield;
	int strike;//暴击

	keyhouse();
	void load();//将存档加载
	void save();//存档
	void reset_save();

private:
	vector<int> desigh_flags;
	void load_shots(LPCTSTR);
	void load_image_asset(LPCTSTR, int);
};

