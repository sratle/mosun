#include "keyhouse.h"

keyhouse::keyhouse()
	:condition(0), timer(0), sun(100), star_value(100), moon(100), attack(0), hp(0), mp(0), shield(0),
	key_card(0), plane_id(0), plane_unlock(0), strike(0), stage(0), score(0)
{
	//Ԥ����
	load_image_asset(L"assets/sakuya1.png", 0);
	load_image_asset(L"assets/sakuya2.png", 0);
	load_image_asset(L"assets/sakuya3.png", 0);
	//plane
	load_image_asset(L"assets/chirno.png", 1);
	load_image_asset(L"assets/patchouli.png", 1);
	load_image_asset(L"assets/sanae.png", 1);
	load_image_asset(L"assets/meirin.png", 1);
	//enemy
	load_image_asset(L"assets/yuyuko.png", 2);//0
	load_image_asset(L"assets/reimu.png", 2);//1
	load_image_asset(L"assets/tenshi.png", 2);//2
	load_image_asset(L"assets/alice.png", 2);//3
	load_image_asset(L"assets/yukari.png", 2);//4 boss1
	load_image_asset(L"assets/suwako.png", 2);//5
	load_image_asset(L"assets/satono.png", 2);//6
	load_image_asset(L"assets/megumu.png", 2);//7
	load_image_asset(L"assets/suika.png", 2);//8 boss2
	load_image_asset(L"assets/marisa.png", 2);//9
	load_image_asset(L"assets/satori.png", 2);//10
	load_image_asset(L"assets/utsuho.png", 2);//11 boss3
	//drop
	load_image_asset(L"assets/updrop.png", 3);
	load_image_asset(L"assets/hp.png", 3);
	load_image_asset(L"assets/mp.png", 3);
	load_image_asset(L"assets/star.png", 3);
	load_image_asset(L"assets/moon.png", 3);
	load_image_asset(L"assets/moon.png", 3);
	load_image_asset(L"assets/sun.png", 3);
	//boom
	load_image_asset(L"assets/boom01.png", 4);
	load_image_asset(L"assets/boom02.png", 4);
	load_image_asset(L"assets/boom03.png", 4);
	load_image_asset(L"assets/boom04.png", 4);
	load_image_asset(L"assets/boom05.png", 4);
	//card
	//bullet
	load_shots(L"assets/BulletAa000.png");//0
	load_shots(L"assets/BulletAa001.png");//1
	load_shots(L"assets/BulletAa002.png");//2
	load_shots(L"assets/BulletAa003.png");//3
	load_shots(L"assets/BulletAa004.png");//4
	load_shots(L"assets/BulletAa005.png");//5
	load_shots(L"assets/BulletAa006.png");//6
	load_shots(L"assets/bulletCc000.png");//7
	load_shots(L"assets/bulletCc001.png");//8
	load_shots(L"assets/bulletCc002.png");//9
	load_shots(L"assets/bulletCc003.png");//10
	load_shots(L"assets/bulletCc004.png");//11
	load_shots(L"assets/bulletCc005.png");//12
	load_shots(L"assets/bulletDd000.png");//13
	load_shots(L"assets/bulletDd001.png");//14
	load_shots(L"assets/bulletEa000.png");//15
	load_shots(L"assets/bulletEa001.png");//16
	load_shots(L"assets/bulletEa002.png");//17
	load_shots(L"assets/bulletEa003.png");//18
	load_shots(L"assets/bulletEa004.png");//19
	load_shots(L"assets/bulletBb000.png");//20
	load_shots(L"assets/bulletBb001.png");//21
	load_shots(L"assets/bulletBb002.png");//22
	load_shots(L"assets/bulletBb003.png");//23
	load_shots(L"assets/bulletFf000.png");//24
	load_shots(L"assets/bulletFf001.png");//25
	load_shots(L"assets/bulletFf002.png");//26
	//other

}

void keyhouse::save()
{
	std::ofstream file("savedata/savedata.dat", std::ios::out | std::ios::binary);
	string to_save;
	to_save = std::to_string(star_value) + " " + std::to_string(moon) + " " + std::to_string(sun) + " ";
	for (auto level : plane_level) {
		to_save = to_save + std::to_string(level) + " ";
	}
	for (auto unlock : cards_unlock) {
		to_save = to_save + std::to_string(unlock) + " ";
	}
	to_save = to_save + std::to_string(plane_unlock) + " " + std::to_string(max_score);
	file << to_save;
	file.close();
}

void keyhouse::load()
{
	std::ifstream file("savedata/savedata.dat", std::ios::in | std::ios::binary);
	vector<string> to_load;
	string load_buffer;
	for (int i = 0; i < 25; i++) {
		file >> load_buffer;
		to_load.push_back(load_buffer);
	}
	star_value = std::stoi(to_load[0]);
	moon = std::stoi(to_load[1]);
	sun = std::stoi(to_load[2]);
	for (int i = 3; i < 7; i++) {
		plane_level[i - 3] = std::stoi(to_load[i]);
	}
	for (int i = 7; i < 23; i++) {
		cards_unlock[i - 7] = std::stoi(to_load[i]);
	}
	plane_unlock = std::stoi(to_load[23]);
	max_score = std::stoi(to_load[24]);
	file.close();
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

void keyhouse::load_image_asset(LPCTSTR asset, int id)
{
	IMAGE img;
	loadimage(&img, asset);
	switch (id)
	{
	case 0:
		sakuya.push_back(img);
		break;
	case 1:
		plane_image.push_back(img);
		break;
	case 2:
		enemy_image.push_back(img);
		break;
	case 3:
		drop_image.push_back(img);
		break;
	case 4:
		boom_image.push_back(img);
		break;
	case 5:
		card_image.push_back(img);
		break;
	case 6:
		other_image.push_back(img);
		break;
	}
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
