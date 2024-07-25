#include "Ui.h"
#pragma comment(linker,"/subsystem:windows /entry:mainCRTStartup")
keyhouse keys;
Ui ui(720, 980);//´°¿Ú´óĞ¡

int main() {
	ui.init();
	std::thread th_1(&Ui::music_control, &ui);
	std::thread th_2(&Ui::bgm_control, &ui);
	std::thread th_3(&Ui::input, &ui);
	ui.run();
	return 0;
}