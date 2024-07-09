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
	int current_index;
	vector<IMAGE*> pages;
	void add_page(IMAGE*);
	void set_current_index(int);
	void draw_control();
	void note(int, int, int, int, int, int, const wstring&);

public:
	Ui(int, int);
	~Ui() {};
	void init();
	void run();
	void close();
	void put_bk_image(int, int, IMAGE);
	vector<Plane*> planes_data;
	vector<Card*> cards_data;
	vector<Drop*> drops_data;
};