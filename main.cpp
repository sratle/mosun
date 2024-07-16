#include "Ui.h"
#pragma comment(linker,"/subsystem:windows /entry:mainCRTStartup")
keyhouse keys;
Ui ui(720, 1028);//´°¿Ú´óĞ¡

int main() {
	ui.init();
	ui.run();
	return 0;
}