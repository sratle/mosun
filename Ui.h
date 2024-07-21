#pragma once
#include "Card.h"
#include "Drop.h"
#include "Enemy.h"
#include "Tool.h"
#include "main.h"
#include "Plane.h"
#include "keyhouse.h"

//整体UI设计，本次项目不采用鼠标，全键盘操控
class Ui
{
private:
	int width;//窗口长宽
	int height;
	int current_index;//当前页面id
	int music_id;//控制当前播放的音效
	int bgm_id;//控制当前播放的bgm
	vector<IMAGE*> pages;//页面背景的图片指针
	void add_page(IMAGE*);
	void set_current_index(int);
	void draw_control();
	void note(int, int, int, int, int, int, COLORREF, COLORREF, const wstring&);
	void judge();//判定用函数
	void level_1();//关卡1函数，里面分为数个阶段
	void enemys_reset();//重置敌机
	void card_control();//卡牌效果
	void plane_house();//机库函数
	vector<int> defeat_target;//目标击败的总数，主要用于自动化统计敌机数量，完成关卡推进

public:
	void music_control();//控制当前的音效
	void bgm_control();//控制当前的bgm
	void input();//输入
	Ui(int, int);//输入长宽
	~Ui() {};
	void init();
	void run();//执行循环
	void close();
	void put_bk_image(int, int, IMAGE);

	Plane* plane;//自己的飞机，每次进入战斗之前都会重置数据
	vector<Enemy*> enemys;//敌机，包含BOSS和普通飞机
	vector<Tool*> tools;//一些小部件的定义包含其中
	vector<Card*> card_select;//每次战斗可以选择六张卡，数据压入其中,id标识0~15
	vector<int> card_now;//手上同时拥有的卡牌有两张，可以打出其中的一张，并在定时之后刷新，标识card_Select中的pos,存id
	vector<Drop*> drops;//掉落物
};