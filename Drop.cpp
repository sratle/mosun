#include "Drop.h"
extern keyhouse keys;

Drop::Drop(int xt, int yt, int idt)
	:x(xt), y(yt), id(idt), state(0)
{
}

void Drop::draw()
{
	if (state == 1)
		return;
	put_bk_image(x - 16, y - 16, keys.drop_image[id]);
	y += 6;
	if (y > 1300)
		state = 1;
}

int Drop::get_id()
{
	return id;
}

int Drop::get_x()
{
	return x;
}

int Drop::get_y()
{
	return y;
}

void Drop::put_bk_image(int x, int y, IMAGE img)
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