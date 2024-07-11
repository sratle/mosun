#include "Shot.h"
extern keyhouse keys;

//id,rotate,x,y
Shot::Shot(int id,int rotate,int x,int y)
	:x(x), y(y), id(id), flag(0), rotate(rotate)
{
}

void Shot::draw() 
{
	put_bk_image(x, y, keys.shots_image[14 * id + rotate]);
}

void Shot::put_bk_image(int x, int y, IMAGE img)
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

void Shot::set_pos(int tx,int ty)
{
	x = tx;
	y = ty;
}

int Shot::get_x() {
	return x;
}

int Shot::get_y() {
	return y;
}

int Shot::get_id() {
	return id;
}

int Shot::get_r() {
	return rotate;
}

void Shot::set_r(int r) {
	rotate = r;
}

void Shot::set_id(int tid) {
	id = tid;
}