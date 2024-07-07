#include "Ui.h"
#pragma comment(linker,"/subsystem:windows /entry:mainCRTStartup")
keyhouse key_house;
Ui ui(720, 1280);

int main() {
	ui.init();
	ui.run();
	ui.close();
	return 0;
}