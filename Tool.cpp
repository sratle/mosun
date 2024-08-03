#include "Tool.h"

hpmp_bar::hpmp_bar(int max_hp,int max_mp,int* hp,int* mp) 
	:max_hp(max_hp),max_mp(max_mp),hp(hp),mp(mp)
{
}

void hpmp_bar::draw()
{
	setlinecolor(WHITE);
	setfillcolor(LIGHTRED);
	setbkmode(TRANSPARENT);
	rectangle(0, 160, 12, 860);
	solidrectangle(0,860-int(700*((double)*hp/(double)max_hp)),12,860);

	setfillcolor(LIGHTBLUE);
	rectangle(708, 160, 720, 860);
	solidrectangle(708, 860 - int(700 * ((double)*mp / (double)max_mp)), 720, 860);
}
