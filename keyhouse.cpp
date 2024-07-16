#include "keyhouse.h"

keyhouse::keyhouse()
	:condition(0), timer(0), anu(0), star_value(0), isthar(0), attack(0), hp(0), mp(0), shield(0),
	key_card(0),  plane_id(0), plane_unlock(0), strike(0), level(0)
{
	//加载函数或许可以使用成员函数进行代码优化
	//预加载
	IMAGE sakuya_1;
	loadimage(&sakuya_1, L"assets/sakuya1.png");
	sakuya.push_back(sakuya_1);
	IMAGE sakuya_2;
	loadimage(&sakuya_2, L"assets/sakuya2.png");
	sakuya.push_back(sakuya_2);
	IMAGE sakuya_3;
	loadimage(&sakuya_3, L"assets/sakuya3.png");
	sakuya.push_back(sakuya_3);
	//plane
	IMAGE swq_1;
	loadimage(&swq_1, L"assets/swq.png");
	plane_image.push_back(swq_1);
	//enemy
	IMAGE yuyuko_1;//0
	loadimage(&yuyuko_1, L"assets/yuyuko.png");
	enemy_image.push_back(yuyuko_1);
	IMAGE reimu_1;//1
	loadimage(&reimu_1, L"assets/reimu.png");
	enemy_image.push_back(reimu_1);
	IMAGE tenshi_1;//2
	loadimage(&tenshi_1, L"assets/tenshi.png");
	enemy_image.push_back(tenshi_1);
	IMAGE alice_1;//3
	loadimage(&alice_1, L"assets/alice.png");
	enemy_image.push_back(alice_1);
	//drop
	IMAGE updrop_1;
	loadimage(&updrop_1, L"assets/updrop.png");
	drop_image.push_back(updrop_1);
	IMAGE hp_1;
	loadimage(&hp_1, L"assets/hp.png");
	drop_image.push_back(hp_1);
	IMAGE mp_1;
	loadimage(&mp_1, L"assets/mp.png");
	drop_image.push_back(mp_1);
	IMAGE star_1;
	loadimage(&star_1, L"assets/star.png");
	drop_image.push_back(star_1);
	//bullet
	load_shots(L"assets/BulletAa000.png");
	load_shots(L"assets/BulletAa001.png");
	load_shots(L"assets/BulletAa002.png");
	load_shots(L"assets/BulletAa003.png");
	load_shots(L"assets/BulletAa004.png");
	load_shots(L"assets/BulletAa005.png");
	load_shots(L"assets/BulletAa006.png");
	//effect
}

int keyhouse::get_flag(int pos)
{
	while (desigh_flags.size() <= pos)
		desigh_flags.push_back(0);
	return desigh_flags[pos];
}

void keyhouse::set_flag(int pos, int val)
{
	while (desigh_flags.size() <= pos)
		desigh_flags.push_back(0);
	desigh_flags[pos] = val;
}

int keyhouse::get_flag_size()
{
	return (int)desigh_flags.size();
}

void keyhouse::load_shots(LPCTSTR imgfile)
{
	IMAGE img1, img2, img3, img4, img5, img6, img7;
	IMAGE img8, img9, img10, img11, img12, img13, img14;
	loadimage(&img4, imgfile);
	rotateimage(&img1, &img4, -PI / 6, BLACK, TRUE);
	rotateimage(&img2, &img4, -PI / 9, BLACK, TRUE);
	rotateimage(&img3, &img4, -PI / 18, BLACK, TRUE);
	rotateimage(&img5, &img4, PI / 18, BLACK, TRUE);
	rotateimage(&img6, &img4, PI / 9, BLACK, TRUE);
	rotateimage(&img7, &img4, PI / 6, BLACK, TRUE);
	rotateimage(&img8, &img4, PI * 5 / 6, BLACK, TRUE);
	rotateimage(&img9, &img4, PI * 8 / 9, BLACK, TRUE);
	rotateimage(&img10, &img4, PI * 17 / 18, BLACK, TRUE);
	rotateimage(&img11, &img4, PI, BLACK, TRUE);
	rotateimage(&img12, &img4, PI * 17 / 18, BLACK, TRUE);
	rotateimage(&img13, &img4, PI * 10 / 9, BLACK, TRUE);
	rotateimage(&img14, &img4, PI * 7 / 6, BLACK, TRUE);
	shots_image.push_back(img1);
	shots_image.push_back(img2);
	shots_image.push_back(img3);
	shots_image.push_back(img4);
	shots_image.push_back(img5);
	shots_image.push_back(img6);
	shots_image.push_back(img7);
	shots_image.push_back(img8);
	shots_image.push_back(img9);
	shots_image.push_back(img10);
	shots_image.push_back(img11);
	shots_image.push_back(img12);
	shots_image.push_back(img13);
	shots_image.push_back(img14);
}
