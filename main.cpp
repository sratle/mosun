#include "Ui.h"
#pragma comment(linker,"/subsystem:windows /entry:mainCRTStartup")
keyhouse keys;
Ui ui(720, 1028);//���ڴ�С

int main() {
	ui.init();
	ui.run();
	return 0;
}