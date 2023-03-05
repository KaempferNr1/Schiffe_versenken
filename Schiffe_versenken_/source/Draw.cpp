#include "headers\Draw.h"
using namespace std;
void Draw::drawMap(HANDLE& console, int x) {
	COORD pos = { 0, 0 };
	DWORD bytesWritten;
	int height = mappp.size();
	for (int y = 0; y < height; y++) {
		std::wstring wrapper = s2ws(mappp[y],1);
		pos.Y = y;
		pos.X = x;
		WriteConsoleOutputCharacter(console, wrapper.c_str(), wrapper.length()-1, pos, &bytesWritten);
	}
	SetConsoleActiveScreenBuffer(console);
}
void Draw::makeMap(string x) {
	for (size_t i = 0; i < mapp.size(); i++){
		mappp[i] = "";
		mappp[i] = map + mapp[i] + mapp2[i] + mapp3[i] + "                                         ";
	}
	mappp[25] = x + "                                                                              ";
}



int Draw::stoii(string& a, int x) {
	int supi = 0;
	int xy = ( x  == 48) ? 57 : (x == 65)? 90 : 97;
	for (char k : a) {
		if ((int)k >= x && (int)k <= xy) {

			supi = ((int)k - x) + supi * 10;
		}
	}
	return supi;
}

void Draw::wahlget(int& auswahl, string& as, int x) {
	//system("cls");
	if (x == 1) {
		system("cls");
		for (size_t i = 0; i < moeglichkeiten.size(); i++){
			cout << "\t" << i + 1 << "\t" << moeglichkeiten[i];
		}
	}
	cin >> as;
	//if (x == 1 || x == 2) { auswahl = stoii(as); }
	auswahl = (x == 1 || x == 2) ? stoii(as,48):stoii(as,65);
}
void Draw::drawPvP(HANDLE& console ,Draw& drawer, Player& player ) {
	
	COORD cursorPos = {0,0};
	int zaehler = 0;
	int wahlR = 0;
	int wahlS = 0;
	string wahl_temp = "0";
	string waiter;
	//player.placeships();
	system("cls");
	player.test(drawer);
	cin >> waiter;
	system("cls");
	makeMap(nthing);
	drawMap(console, 0);
	system("cls");
	string temp ="Waehlen sie die Reihe: ";
	string temp2 = "Waehlen sie die Spalte: ";
	
	string temp3 = "Press Key to continue";
	while (!game_end) {
		*playptr1 = (zaehler % 2) ? '2' : '1';
		*playptr2 = (zaehler % 2) ? '1' : '2';
		makeMap(" ");
		drawMap(console, 0);

		do{
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			makeMap(temp); drawMap(console, 0);
			wahlget(wahlR, wahl_temp, 0);
			cursorPos.X = 24;cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			makeMap(temp2);drawMap(console, 0);
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			wahlget(wahlS, wahl_temp, 2);
			//cout << wahlS;
		}while (! player.validmove(wahlR,wahlS,(zaehler%2)));
		player.movemaker(wahlR, wahlS, zaehler % 2,drawer);
		makeMap(temp3);
		drawMap(console, 0);
		cursorPos.X = 24; cursorPos.Y = 25;
		SetConsoleCursorPosition(console, cursorPos);
		cin >> waiter;
		zaehler = (zaehler >= 100) ? 0 : zaehler + 1;
	}

}

void Draw::drawPv(HANDLE&, Draw&, Player&){
}

void Draw::drawPvC(HANDLE&, Draw&, Player&){
}

void Draw::drawCvC(HANDLE&, Draw&, Player&){
}

void Draw::setansig(string& x) {

}

wstring Draw::s2ws(const string& s, bool isUtf8)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(isUtf8 ? CP_UTF8 : CP_ACP, 0, s.c_str(), slength, 0, 0);
	std::wstring buf;
	buf.resize(len);
	MultiByteToWideChar(isUtf8 ? CP_UTF8 : CP_ACP, 0, s.c_str(), slength,
		const_cast<wchar_t*>(buf.c_str()), len);
	return buf;
}


//void Map::mapsetter() {
//
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