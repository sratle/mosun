#include "Shot.h"
extern Ui ui;
extern keyhouse key_house;

Shot::Shot(int id,int rotate)
	:x(key_house.plane_self[2]), y(key_house.plane_self[3]), id(id), flag(0), rotate(rotate)
{
}

void Shot::draw() 
{
	ui.put_bk_image(x, y, key_house.shots_image[7 * id + rotate]);
}