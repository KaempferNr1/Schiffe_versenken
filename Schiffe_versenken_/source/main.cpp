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
typedef long long ll;

int main() {
	//std::mt19937_64 random_engine(std::chrono::system_clock::now().time_since_epoch().count());
	//srand(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
	Draw drawer;
	//Player player;
	//Computer computer;
	//Highscore highscore;
	//map.mapsetter();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
	bool windowopen = true;
	string auswahl_temp = "-";
	int auswahl = 0;
	cout << "hallo welt11";
	cin >> auswahl_temp;
	
	while (windowopen) {
		//player.resettonormal(drawer);
		drawer.wahlget(auswahl, auswahl_temp, 1);
		switch (auswahl)
		{
		case 1:
			drawer.drawPvP(hConsole, drawer);
			break;
		case 2:
			drawer.drawPv(hConsole, drawer);
			break;
		case 3:
			drawer.drawPvC(hConsole, drawer);
			break;
		case 4:
			drawer.drawCvC(hConsole, drawer);
			break;
		default:
			cout << "okay dann tschau";
			windowopen = false;
			break;
		}
	}
	return 0;
}
//	
//	mapp = {
//	   "Player 1:                                                    ",
//	   "  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                  ",
//	   "---------------------------------------------                ",
//	   "A | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | A                ",
//	   "---------------------------------------------                ",
//	   "B | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | B                ",
//	   "---------------------------------------------                ",
//	   "C | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | C                ",
//	   "---------------------------------------------                ",
//	   "D | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | D                ",
//	   "---------------------------------------------                ",
//	   "E | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | E                ",
//	   "---------------------------------------------                ",
//	   "F | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | F                ",
//	   "---------------------------------------------                ",
//	   "G | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | G                ",
//	   "---------------------------------------------                ",
//	   "H | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | H                ",
//	   "---------------------------------------------                ",
//	   "I | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | I                ",
//	   "---------------------------------------------                ",
//	   "J | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | J                ",
//	   "---------------------------------------------                ",
//	   "  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                  "
//	};
//	mapp2 = {
//		"Player 2:                                                    ",
//		"  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                  ",
//		"---------------------------------------------                ",
//		"A | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | A                ",
//		"---------------------------------------------                ",
//		"B | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | B                ",
//		"---------------------------------------------                ",
//		"C | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | C                ",
//		"---------------------------------------------                ",
//		"D | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | D                ",
//		"---------------------------------------------                ",
//		"E | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | E                ",
//		"---------------------------------------------                ",
//		"F | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | F                ",
//		"---------------------------------------------                ",
//		"G | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | G                ",
//		"---------------------------------------------                ",
//		"H | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | H                ",
//		"---------------------------------------------                ",
//		"I | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | I                ",
//		"---------------------------------------------                ",
//		"J | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | J                ",
//		"---------------------------------------------                ",
//		"  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                  "
//	};
//	map1 = "                ";
//	mapp3 = {
//		"                                ",
//		"Legende:                        ",
//		"                                ",
//		"~ = noch nicht getestetes Wasser",
//		"                                ",
//		"* = Treffer                     ",
//		"                                ",
//		"# = Schiff                      ",
//		"                                ",
//		"o = verfehlt                    ",
//		"                                ",
//		"X = Schiff Kaputt               ",
//		"                                ",
//		"Anzahl Schiffe uebrig:          ",
//		"                                ",
//		"Player 1:       Player2:        ",
//		"                                ",
//		"#### : 1        #### : 1        ",
//		"###  : 2        ###  : 2        ",
//		"##   : 3        ##   : 3        ",
//		"#    : 4        #    : 4        ",
//		"                                ",
//		"                                ",
//		"                                ",
//	};
//	
//	
//	mappp = {
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"",
//		"                                     ",
//		"                                     ",
//		"                                     ",
//		"                                     ",
//		"                                     ",
//		"                                     ",
//	};
//	
//	charptrs = {
//		{&mapp[3][4],&mapp[3][8],&mapp[3][12],&mapp[3][16],&mapp[3][20], &mapp[3][24], &mapp[3][28], &mapp[3][32], &mapp[3][36], &mapp[3][40]},
//		{&mapp[5][4],&mapp[5][8],&mapp[5][12],&mapp[5][16],&mapp[5][20], &mapp[5][24], &mapp[5][28], &mapp[5][32], &mapp[5][36], &mapp[5][40]},
//		{&mapp[7][4],&mapp[7][8],&mapp[7][12],&mapp[7][16],&mapp[7][20], &mapp[7][24], &mapp[7][28], &mapp[7][32], &mapp[7][36], &mapp[7][40]},
//		{&mapp[9][4],&mapp[9][8],&mapp[9][12],&mapp[9][16],&mapp[9][20], &mapp[9][24], &mapp[9][28], &mapp[9][32], &mapp[9][36], &mapp[9][40]},
//		{&mapp[11][4],&mapp[11][8],&mapp[11][12],&mapp[11][16],&mapp[11][20], &mapp[11][24], &mapp[11][28], &mapp[11][32], &mapp[11][36], &mapp[11][40]},
//		{&mapp[13][4],&mapp[13][8],&mapp[13][12],&mapp[13][16],&mapp[13][20], &mapp[13][24], &mapp[13][28], &mapp[13][32], &mapp[13][36], &mapp[13][40]},
//		{&mapp[15][4],&mapp[15][8],&mapp[15][12],&mapp[15][16],&mapp[15][20], &mapp[15][24], &mapp[15][28], &mapp[15][32], &mapp[15][36], &mapp[15][40]},
//		{&mapp[17][4],&mapp[17][8],&mapp[17][12],&mapp[17][16],&mapp[17][20], &mapp[17][24], &mapp[17][28], &mapp[17][32], &mapp[17][36], &mapp[17][40]},
//		{&mapp[19][4],&mapp[19][8],&mapp[19][12],&mapp[19][16],&mapp[19][20], &mapp[19][24], &mapp[19][28], &mapp[19][32], &mapp[19][36], &mapp[19][40]},
//		{&mapp[22][4],&mapp[22][8],&mapp[22][12],&mapp[22][16],&mapp[22][20], &mapp[22][24], &mapp[22][28], &mapp[22][32], &mapp[22][36], &mapp[22][40]},
//	};
//	charptrs2 = {
//		{&mapp2[3][4],&mapp2[3][8],&mapp2[3][12],&mapp2[3][16],&mapp2[3][20], &mapp2[3][24], &mapp2[3][28], &mapp2[3][32], &mapp2[3][36], &mapp2[3][40]},
//		{&mapp2[5][4],&mapp2[5][8],&mapp2[5][12],&mapp2[5][16],&mapp2[5][20], &mapp2[5][24], &mapp2[5][28], &mapp2[5][32], &mapp2[5][36], &mapp2[5][40]},
//		{&mapp2[7][4],&mapp2[7][8],&mapp2[7][12],&mapp2[7][16],&mapp2[7][20], &mapp2[7][24], &mapp2[7][28], &mapp2[7][32], &mapp2[7][36], &mapp2[7][40]},
//		{&mapp2[9][4],&mapp2[9][8],&mapp2[9][12],&mapp2[9][16],&mapp2[9][20], &mapp2[9][24], &mapp2[9][28], &mapp2[9][32], &mapp2[9][36], &mapp2[9][40]},
//		{&mapp2[11][4],&mapp2[11][8],&mapp2[11][12],&mapp2[11][16],&mapp2[11][20], &mapp2[11][24], &mapp2[11][28], &mapp2[11][32], &mapp2[11][36], &mapp2[11][40]},
//		{&mapp2[13][4],&mapp2[13][8],&mapp2[13][12],&mapp2[13][16],&mapp2[13][20], &mapp2[13][24], &mapp2[13][28], &mapp2[13][32], &mapp2[13][36], &mapp2[13][40]},
//		{&mapp2[15][4],&mapp2[15][8],&mapp2[15][12],&mapp2[15][16],&mapp2[15][20], &mapp2[15][24], &mapp2[15][28], &mapp2[15][32], &mapp2[15][36], &mapp2[15][40]},
//		{&mapp2[17][4],&mapp2[17][8],&mapp2[17][12],&mapp2[17][16],&mapp2[17][20], &mapp2[17][24], &mapp2[17][28], &mapp2[17][32], &mapp2[17][36], &mapp2[17][40]},
//		{&mapp2[19][4],&mapp2[19][8],&mapp2[19][12],&mapp2[19][16],&mapp2[19][20], &mapp2[19][24], &mapp2[19][28], &mapp2[19][32], &mapp2[19][36], &mapp2[19][40]},
//		{&mapp2[21][4],&mapp2[21][8],&mapp2[21][12],&mapp2[21][16],&mapp2[21][20], &mapp2[21][24], &mapp2[21][28], &mapp2[21][32], &mapp2[21][36], &mapp2[21][40]},
//	};
//	charptrs3 = {
//		{&mapp3[17][7],&mapp3[17][24]},
//		{&mapp3[18][7],&mapp3[18][24]},
//		{&mapp3[19][7],&mapp3[19][24]},
//		{&mapp3[20][7],&mapp3[20][24]}
//	};
//	playptr1 = &mapp[0][23];
//	playptr2 = &mapp2[0][7];
//	nthing = " ";
//}