#pragma once
#include "Card.h"
#include "Drop.h"
#include "main.h"
#include "Plane.h"
#include "keyhouse.h"

//整体UI设计，本次项目不采用鼠标，全键盘操控
class Ui
{
private:
	int width;
	int height;
	int fps;
	int current_index;
	vector<IMAGE*> pages;
	void add_page(IMAGE*);
	void set_current_index(int);
	void draw_control();
	void put_bk_image(int,int ,IMAGE);
	void note(int,int,int,int,int,int, const wstring&);

public:
	Ui(int, int,int);
	~Ui() {};
	void init();
	void run();
	void close();
	vector<Plane*> planes_data;
};