#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

#include "global.h"
#include "computer.h"
#include "Draw.h"
#include "player.h"
#include "highscore.h"
using namespace std;

int main() {
	Draw drawer;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
	bool windowopen = true;
	string auswahl_temp = "-";
	int auswahl = 0;
	Player player;
	while (windowopen){
		player.resettonormal();
		drawer.wahlget(auswahl, auswahl_temp, 1);
		switch (auswahl)
		{
		case 1:

			drawer.drawPvP(hConsole);
			break;
		case 2:
			drawer.drawPv();
			break;
		case 3:
			drawer.drawPvC();
			break;
		case 4:
			drawer.drawCvC();
			break;
		default:
			cout << "okay dann tschau";
			windowopen = false;
			break;
		}
	}

	return 0;
}
