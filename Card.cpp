#include "Card.h"
extern keyhouse keys;

Card::Card(int id)
	:id(id), pos(0), state(0), r_time(1)
{
}

//只有card_now中有的函数才会被渲染，然后state0的时候处于低位，选中卡牌state1处于高位，相同时刻只能有一张卡牌处于高位
//对于处于高位的卡牌，再按一下卡牌进入state2就会被打出,打出结束之后进入state3，触发效果
void Card::draw()
{
	if (state == 3)
		return;
	if (state == 2)
	{
		put_bk_image(15 + 80 * pos, 836 - state * 16 - r_time * 80, keys.card_image[id]);
		r_time++;
		if (r_time > 11)
		{
			state = 3;
			r_time = 1;
		}
		return;
	}
	put_bk_image(15 + 80 * pos, 836 - state * 16, keys.card_image[id]);
	//选中加边框
	if (state == 1)
	{
		setlinestyle(PS_SOLID, 1);
		setlinecolor(WHITE);
		rectangle(15 + 80 * pos, 836 - state * 16, 15 + 80 * pos + 64, 836 - state * 16 + 128);
		setlinecolor(RED);
		rectangle(14 + 80 * pos, 835 - state * 16, 16 + 80 * pos + 64, 837 - state * 16 + 128);
	}
}

int Card::get_cost(int id)
{
	return mp_cost[id];
}

int Card::get_id()
{
	return id;
}

int Card::get_state()
{
	return state;
}

void Card::set_pos(int p)
{
	pos = p;
}

void Card::set_state(int s)
{
	state = s;
}

void Card::put_bk_image(int x, int y, IMAGE img)
{
	IMAGE img1;
	DWORD* d1;
	img1 = img;
	d1 = GetImageBuffer(&img1);
	float h, s, l;
	for (int i = 0; i < img1.getheight() * img1.getwidth(); i++) {
		RGBtoHSL(BGR(d1[i]), &h, &s, &l);
		if (l < 0.03)
		{
			d1[i] = BGR(WHITE);
		}
		if (d1[i] != BGR(WHITE))
		{
			d1[i] = 0;
		}
	}
	putimage(x, y, &img1, SRCAND);
	putimage(x, y, &img, SRCPAINT);
}