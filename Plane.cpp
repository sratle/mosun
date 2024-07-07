#include "Plane.h"
extern keyhouse key_house;

ur::ur() {}

void ur::skill() {
	return;
}

void ur::upgrade()
{
	key_house.hp = hps[key_house.plane_level[0]];
	key_house.mp = mps[key_house.plane_level[0]];
	key_house.attack = attacks[key_house.plane_level[0]];
	key_house.shield = shields[key_house.plane_level[0]];
	key_house.strike = strikes[key_house.plane_level[0]];
}

nanna::nanna() {}

void nanna::skill() {
	if (key_house.timer - key_house.temp_time > FPS * 20) {
		key_house.hp += 5 * key_house.plane_level[1];
		if (key_house.hp > hps[key_house.plane_level[1]])
			key_house.hp = hps[key_house.plane_level[1]];
		key_house.temp_time = key_house.timer;
	}
}

void nanna::upgrade()
{
	key_house.hp = hps[key_house.plane_level[1]];
	key_house.mp = mps[key_house.plane_level[1]];
	key_house.attack = attacks[key_house.plane_level[1]];
	key_house.shield = shields[key_house.plane_level[1]];
	key_house.strike = strikes[key_house.plane_level[1]];
}

ea::ea() {}

void ea::skill() {
	if ((key_house.timer - key_house.temp_time) % 2 == 0) {
		key_house.shield = shields[key_house.plane_level[2]] * 2;
		key_house.temp_time = key_house.timer;
	}
	else {
		key_house.shield = shields[key_house.plane_level[2]];
	}
}

void ea::upgrade()
{
	key_house.hp = hps[key_house.plane_level[2]];
	key_house.mp = mps[key_house.plane_level[2]];
	key_house.attack = attacks[key_house.plane_level[2]];
	key_house.shield = shields[key_house.plane_level[2]];
	key_house.strike = strikes[key_house.plane_level[2]];
}

enlil::enlil() {}

void enlil::skill() {
	if ((key_house.timer - key_house.temp_time) % 2 == 0) {
		key_house.strike = strikes[key_house.plane_level[3]] * 2;
		key_house.temp_time = key_house.timer;
	}
	else {
		key_house.strike = strikes[key_house.plane_level[3]];
	}
}

void enlil::upgrade()
{
	key_house.hp = hps[key_house.plane_level[3]];
	key_house.mp = mps[key_house.plane_level[3]];
	key_house.attack = attacks[key_house.plane_level[3]];
	key_house.shield = shields[key_house.plane_level[3]];
	key_house.strike = strikes[key_house.plane_level[3]];
}