#include "keyhouse.h"

keyhouse::keyhouse()
	:condition(0), timer(0), anu(0), star_value(0), isthar(0), attack(0), hp(0), mp(0), shield(0), temp_time(0),
	move_flag(0), key_card(0), key_move(0), plane_id(0), plane_unlock(0), strike(0), level(0)
{
	//‘§º”‘ÿ
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
	load_shots(L"assets/BulletAa000.png");
	load_shots(L"assets/BulletAa001.png");
	load_shots(L"assets/BulletAa002.png");
	load_shots(L"assets/BulletAa003.png");
	load_shots(L"assets/BulletAa004.png");
	load_shots(L"assets/BulletAa005.png");
	load_shots(L"assets/BulletAa006.png");
}

void keyhouse::load_shots(LPCTSTR imgfile)
{
	IMAGE img1, img2, img3, img4, img5, img6, img7;
	loadimage(&img4, imgfile);
	rotateimage(&img1, &img4, -PI / 6, BLACK, TRUE);
	rotateimage(&img2, &img4, -PI / 9, BLACK, TRUE);
	rotateimage(&img3, &img4, -PI / 18, BLACK, TRUE);
	rotateimage(&img5, &img4, PI / 18, BLACK, TRUE);
	rotateimage(&img6, &img4, PI / 9, BLACK, TRUE);
	rotateimage(&img7, &img4, PI / 6, BLACK, TRUE);
	shots_image.push_back(img1);
	shots_image.push_back(img2);
	shots_image.push_back(img3);
	shots_image.push_back(img4);
	shots_image.push_back(img5);
	shots_image.push_back(img6);
	shots_image.push_back(img7);
}
