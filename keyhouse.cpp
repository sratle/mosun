#include "keyhouse.h"

keyhouse::keyhouse()
	:condition(0), timer(0), anu(0), star_value(0), isthar(0), attack(0), hp(0), mp(0), shield(0), temp_time(0),
	move_flag(0), key_card(0), key_move(0), plane_id(0), plane_unlock(0), strike(0), level(0)
{
	//Ô¤¼ÓÔØ
	IMAGE sakuya_1;
	loadimage(&sakuya_1, L"assets/sakuya1.png");
	sakuya.push_back(sakuya_1);
	IMAGE sakuya_2;
	loadimage(&sakuya_2, L"assets/sakuya2.png");
	sakuya.push_back(sakuya_2);
	IMAGE sakuya_3;
	loadimage(&sakuya_3, L"assets/sakuya3.png");
	sakuya.push_back(sakuya_3);
	IMAGE swq_1;
	loadimage(&swq_1, L"assets/swq.png");
	plane_image.push_back(swq_1);
}
