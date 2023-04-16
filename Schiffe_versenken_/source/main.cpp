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
void clearscreen(Draw&);

// min size damit es funktioniert 170
int main() {
	Draw drawer;	
	bool windowopen = true;
	std::string auswahl_temp = "";
	int auswahl = 4;
	srand((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());

	//unique_ptr<> user;
	while (windowopen) {
		reset(drawer);
		system("pause");
		clearscreen(drawer);
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
			break;
		case 6:
			drawer.mostlikelysq(drawer);
			break;
		default:
			std::cout << "okay dann tschau";
			windowopen = false;
			break;
		}
	}
	return 0;
}
void clearscreen(Draw& drawer) {
	system("cls");
	/*wstring w = L"                                                                                                                                                                          ";
	system("color F");
	DWORD bytesWritten = 0;
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(drawer.console, &screen);
	COORD pos = { 0,0 };
	int width = screen.dwSize.X;
	if ((unsigned)width > w.size()) {
		for (int q = 0; q < (signed int)(width - w.size()); q++) {
			w = w + L" ";
		}
	}
	for (int i = 0; i < 26; i++) {
		pos.Y = i;
	*///WriteConsoleOutputCharacterW(drawer.console, w.c_str(), (DWORD)w.length() - 1, pos, &bytesWritten); //hier beschreibe ich das terminal
	//}
	//pos.X = 0;
	//pos.Y = 0;
	//SetConsoleCursorPosition(drawer.console, pos);
}
void reset(Draw& drawer) {
	drawer.zaehler = 0;
	*drawer.charptrs3[3][0] = '1';
	*drawer.charptrs3[2][0] = '2';
	*drawer.charptrs3[1][0] = '1';
	*drawer.charptrs3[0][0] = '1';
	*drawer.charptrs3[3][1] = '1';
	*drawer.charptrs3[2][1] = '2';
	*drawer.charptrs3[1][1] = '1';
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