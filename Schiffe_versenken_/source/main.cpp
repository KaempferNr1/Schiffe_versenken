#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

#include "headers\global.h"
#include "headers\computer.h"
#include "headers\Draw.h"
#include "headers\player.h"
#include "headers\highscore.h"
#include "headers\Compare.h"
using namespace std;
void reset(Draw&);
int main() {
	system("pause");
	system("cls");
	Draw drawer;	
	// min size damit es funktioniert 170
	bool windowopen = true;
	string auswahl_temp = "";
	int auswahl = 0;
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	while (windowopen) {
		reset(drawer);
		drawer.wahlget(auswahl, auswahl_temp, 1);
		switch (auswahl)	{
		case 1:
			drawer.drawPvP(drawer);
			break;
		case 2:
			drawer.drawPv(drawer);
			break;
		case 3:
			drawer.drawPvC(drawer);
			break;
		case 4:
			drawer.drawCvC(drawer);
			break;
		case 5:
			drawer.mostlikelysq(drawer);
			break;
		default:
			cout << "okay dann tschau";
			windowopen = false;
			break;
		}
	}
	return 0;
}
void reset(Draw& drawer) {
	*drawer.charptrs3[3][0] = '4';
	*drawer.charptrs3[2][0] = '3';
	*drawer.charptrs3[1][0] = '2';
	*drawer.charptrs3[0][0] = '1';
	*drawer.charptrs3[3][1] = '4';
	*drawer.charptrs3[2][1] = '3';
	*drawer.charptrs3[1][1] = '2';
	*drawer.charptrs3[0][1] = '1';
	for (int i = 0; i < sizefield; i++) {
		for (int k = 0; k < sizefield; k++) {
			drawer.charptrs[i][k][0] = unused;
			drawer.charptrs2[i][k][0] = unused;
			drawer.dest1[i][k] = 0;
			drawer.dest2[i][k] = 0;
		}
	}
}
//void cursorInvis(HANDLE& console){
//	CONSOLE_CURSOR_INFO cursorInfo;
//	console = GetStdHandle(STD_OUTPUT_HANDLE);
//	GetConsoleCursorInfo(console, &cursorInfo);
//	cursorInfo.bVisible = false;
//	SetConsoleCursorInfo(console, &cursorInfo);
//	SetConsoleActiveScreenBuffer(console);
//}
//void cursorVis(HANDLE& console) {
//	CONSOLE_CURSOR_INFO cursorInfo;
//	console = GetStdHandle(STD_OUTPUT_HANDLE);
//	GetConsoleCursorInfo(console, &cursorInfo);
//	cursorInfo.bVisible = true;
//	SetConsoleCursorInfo(console, &cursorInfo);
//	SetConsoleActiveScreenBuffer(console);
//}