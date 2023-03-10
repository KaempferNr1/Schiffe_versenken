#include "headers/Draw.h"
#include "headers/computer.h"
using namespace std;
void Draw::drawMap(HANDLE& console, int x, vector<string>& map) {
	CONSOLE_SCREEN_BUFFER_INFO screen;
	HANDLE console2 = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &screen);
	COORD pos = { 0, 0 };
	pos.Y = 0;
	pos.X = x;
	DWORD bytesWritten;
	int height = map.size();
	for (int y = 0; y < height; y++) {
		std::wstring outputstr = s2ws(map[y],1);
		pos.Y = y;
		pos.X = x;
		WriteConsoleOutputCharacter(console2, outputstr.c_str(), outputstr.length()-1, pos, &bytesWritten);
	}
	SetConsoleActiveScreenBuffer(console2);
}
//void Draw::setmap(string& x,HANDLE& console) {
//	string temp;
//	CONSOLE_SCREEN_BUFFER_INFO screen;
//	GetConsoleScreenBufferInfo(console, &screen);
//	vector<int> temp2;
//	for (size_t i = 0; i < mapp.size(); i++){
//		mappp[i] = "";
//		mappp[i] = map1 + mapp[i] + mapp2[i] + mapp3[i];
//
//	}
//	mappp[25] = x;
//	int width = screen.dwSize.X;
//	for (size_t k = 0; k < mappp.size(); k++){
//		temp = ""; 
//		if ((unsigned int)width > mappp[k].size())
//		{
//			for (int q = 0; q < (signed int)(width - mappp[k].size()); q++)
//			{
//				temp = temp + " ";
//			}
//		}
//
//		mappp[k] = mappp[k] + temp;
//	}
//}

void Draw::makemap(vector<vector<bool>>& ships_see, vector<vector<bool>>& ships, vector<vector<char*>>& charptrs, bool z) {
	for (int i = 0; i < sizefield; i++) {
		for (int k = 0; k < sizefield; k++) {
			if (ships_see[i][k] == 0 && (ships[i][k] == 0 || !z)) {
				*charptrs[i][k] = unused;
			}
			else if ((ships_see[i][k] == 0 && ships[i][k] == 1) && z) {
				*charptrs[i][k] = ship;

			}
			else if (ships_see[i][k] == 1 && ships[i][k] == 1) {
				*charptrs[i][k] = hit;
			}
			else {
				*charptrs[i][k] = miss;
			}
		}
	}

}

int stoii(string& a, int x) {
	int supi = 0;
	int xy = ( x  == 48) ? 57 : (x == 65)? 90 : 97;
	for (char k : a) {
		if ((int)k >= x && (int)k <= xy) {

			supi = ((int)k - x) + supi * 10;
		}
	}
	return supi;
}
//(zaehler % 2 == 1) ? (makemap(players[0].treffer, p2.eigeneschiffe, charptrs, 1), makemap(p2.treffer, players[0].eigeneschiffe, charptrs2, 0)) : (makemap(players[1].treffer, players[0].eigeneschiffe, charptrs, 1), makemap(players[0].treffer, players[1].eigeneschiffe, charptrs2, 0));
		/**playptr1 = (zaehler % 2) ? '2' : '1';
		*playptr2 = (zaehler % 2) ? '1' : '2';*/
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
void Draw::drawPvP(HANDLE& console ,Draw& drawer) {
	array<Player, 2> players;
	COORD cursorPos = {0,0};
	//Compare cp;
	int zaehler = 0;
	int wahlR = 0;
	int wahlS = 0;
	string wahl_temp = "0";
	//bool hit_current_zug = 0;
	//player.placeships(drawer);
	//system("cls");
	int n = 0;
	int m = 1;
	for (int i = 0; i < 2; i++)
	{
		players[i].placeships(drawer);
	}
	string temp ="Waehlen sie die Reihe: ";
	string temp2 = "Waehlen sie die Spalte: ";
	string temp3 = "Druecken sie enter";
	while (!game_end) {
		string waiter;
		if (zaehler % 2 == 0) {
			m = 1;
			n = 0;
		}
		else{
			m = 0;
			n = 1;
		}

		makemap(players[m].treffer, players[n].eigeneschiffe, charptrs, 1);
		makemap(players[n].treffer, players[m].eigeneschiffe, charptrs2, 0);
		setmap(console,mappp,mapp,mapp2,mapp3,nthing);
		drawMap(console, 0,mappp);
		do{
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			setmap(console, mappp, mapp, mapp2, mapp3, temp);
			drawMap(console, 0, mappp);
			wahlget(wahlR, wahl_temp, 0);
			cursorPos.X = 24;cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			setmap(console, mappp, mapp, mapp2, mapp3, temp2);
			drawMap(console, 0, mappp);
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			wahlget(wahlS, wahl_temp, 2);
			//cout << wahlS;
		}while (! players[m].validmove(wahlR, wahlS));
		//players[m].movemaker(wahlR, wahlS, zaehler % 2, drawer);
		//cper.movemaker(wahlR,wahlS,drawer,players[m],players[n]);
		players[m].treffer[wahlR][wahlS] = 1;
		makemap(players[n].treffer, players[m].eigeneschiffe, charptrs, 1);
		makemap(players[m].treffer, players[n].eigeneschiffe, charptrs2, 0);
		setmap(console, mappp, mapp, mapp2, mapp3, temp3);
		drawMap(console, 0, mappp);
		cursorPos.X = 24; cursorPos.Y = 25;
		SetConsoleCursorPosition(console, cursorPos);
		system("pause");
		if (players[m].treffer[wahlR][wahlS] == 1 && players[n].eigeneschiffe[wahlR][wahlS] == 1) {
			//hit_current_zug = 1;
			players[m].trefferuebrig--;
			if (players[m].trefferuebrig == 0) {
				game_end = true;
			}
		}
		else {
			zaehler++;
		}	
	}
	players[0].resettonormal(drawer);
	string gamer = "Player x hat gewonnen";
	game_end = false;
}

void Draw::drawPv(HANDLE& console, Draw& drawer){
	Computer pc;
	//Player function; //nur für methods hier vllt sollte ich die methods anders machen oder erbschafft einbringen 
	COORD cursorPos = { 0,0 };
	//Compare cper;
	int zaehler = 0;
	int wahlR = 0;
	int wahlS = 0;
	string wahl_temp = "0";
	//bool hit_current_zug = 0;
	//player.placeships(drawer);
	//system("cls");
	int n = 0;
	int m = 1;
	pc.placeships(drawer);
	pc.trefferuebrig = 20;
	string temp = "Waehlen sie die Reihe: ";
	string temp2 = "Waehlen sie die Spalte: ";
	string temp3 = "Druecken sie enter";
	mapp[0] = "Gegner Schiffe";
	while (!game_end) {
	string waiter;
		if (zaehler % 2 == 0) {
			m = 1;
			n = 0;
		}
		else {
			m = 0;
			n = 1;
		}

		makemap(pc.treffer, pc.eigeneschiffe, charptrs, 1);
		//makemap(players[n].treffer, players[m].eigeneschiffe, charptrs2, 0);
		//setmap(console, mappp, mapp, emptyvec, mapp3, nthing);
		//drawMap(console, 0, mappp);
		do {
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			setmap(console, mappp, mapp, emptyvec, mapp3, temp);
			drawMap(console, 0, mappp);
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			wahlget(wahlR, wahl_temp, 0);
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			setmap(console, mappp, mapp, emptyvec, mapp3, temp2);
			drawMap(console, 0, mappp);
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			wahlget(wahlS, wahl_temp, 2);
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
		} while (!pc.validmove(wahlR, wahlS));
		//players[m].movemaker(wahlR, wahlS, zaehler % 2, drawer);
		//cper.movemaker(wahlR,wahlS,drawer,players[m],players[n]);
		pc.treffer[wahlR][wahlS] = 1;
		makemap(pc.treffer, pc.eigeneschiffe, charptrs, 1);
		//makemap(players[m].treffer, players[n].eigeneschiffe, charptrs2, 0);
		//setmap(temp3, console);
		setmap(console, mappp, mapp, emptyvec, mapp3, nthing);
		drawMap(console, 0, mappp);
		cursorPos.X = 0; cursorPos.Y = 25;
		SetConsoleCursorPosition(console, cursorPos);

		system("pause");
		//cin >> waiter;
		if (pc.treffer[wahlR][wahlS] == 1 && pc.eigeneschiffe[wahlR][wahlS] == 1) {
			//hit_current_zug = 1;
			pc.trefferuebrig--;
			if (pc.trefferuebrig == 0) {
				game_end = true;
			}
		}
		zaehler++;
	}
	pc.resettonormal(drawer);
	string gamer = "Player x hat gewonnen";
	game_end = false;
}

void Draw::drawPvC(HANDLE& console, Draw& drawer){
	Computer pc1;
	Player p1;
	pc1.placeships(drawer);
	p1.placeships(drawer);
	game_end = false;
}
void dosomething() {

}
void Draw::setmap(HANDLE& console, std::vector<std::string>& result, std::vector<std::string>& mp1, std::vector<std::string>& mp2, std::vector<std::string>& mp3, std::string&x) {
	string temp;
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(console, &screen);
	vector<int> temp2;
	for (size_t i = 0; i < mp1.size(); i++) {
		result[i] = "";
		result[i] = map1 + mp1[i] + mp2[i] + mp3[i];

	}
	result[25] = x;
	int width = screen.dwSize.X;
	for (size_t k = 0; k < result.size(); k++) {
		temp = "";
		if ((unsigned)width > result[k].size()){
			for (int q = 0; q < (signed int)(width - result[k].size()); q++){
				temp = temp + " ";
			}
		}

		result[k] = result[k] + temp;
	}
}
void Draw::drawCvC(HANDLE& console, Draw& drawer){
	array<Computer, 2> pcs;
	COORD cursorPos = { 0,0 };
	//Compare cper;
	int zaehler = 0;
	int wahlR = 0;
	int wahlS = 0;
	string wahl_temp = "0";
	//bool hit_current_zug = 0;
	//player.placeships(drawer);
	//system("cls");
	int n = 0;
	int m = 1;
	for (int i = 0; i < 2; i++)
	{
		pcs[i].placeships(drawer);
	}
	string temp = "Waehlen sie die Reihe: ";
	string temp2 = "Waehlen sie die Spalte: ";
	string temp3 = "Druecken sie enter";
	while (!game_end) {
		/**playptr1 = (zaehler % 2) ? '2' : '1';
		*playptr2 = (zaehler % 2) ? '1' : '2';*/

		//(zaehler % 2 == 1) ? (makemap(players[0].treffer, p2.eigeneschiffe, charptrs, 1), makemap(p2.treffer, players[0].eigeneschiffe, charptrs2, 0)) : (makemap(players[1].treffer, players[0].eigeneschiffe, charptrs, 1), makemap(players[0].treffer, players[1].eigeneschiffe, charptrs2, 0));
		string waiter;
		if (zaehler % 2 == 0) {
			m = 1;
			n = 0;
		}
		else {
			m = 0;
			n = 1;
		}

		makemap(pcs[m].treffer, pcs[n].eigeneschiffe, charptrs, 1);
		makemap(pcs[n].treffer, pcs[m].eigeneschiffe, charptrs2, 0);
		setmap(console, mappp, mapp, mapp2, mapp3, nthing);
		drawMap(console, 0, mappp);
		do {
			wahlR = rand() % 10;
			wahlS = rand() % 10;
			//cout << wahlS;
		} while (!pcs[m].validmove(wahlR, wahlS));
		//players[m].movemaker(wahlR, wahlS, zaehler % 2, drawer);
		//cper.movemaker(wahlR,wahlS,drawer,players[m],players[n]);
		pcs[m].treffer[wahlR][wahlS] = 1;
		makemap(pcs[n].treffer, pcs[m].eigeneschiffe, charptrs, 1);
		makemap(pcs[m].treffer, pcs[n].eigeneschiffe, charptrs2, 0);
		setmap(console, mappp, mapp, mapp2, mapp3, temp3);
		drawMap(console, 0, mappp);
		cursorPos.X = 24; cursorPos.Y = 25;
		SetConsoleCursorPosition(console, cursorPos);
		cin >> waiter;
		if (pcs[m].treffer[wahlR][wahlS] == 1 && pcs[n].eigeneschiffe[wahlR][wahlS] == 1) {
			//hit_current_zug = 1;
			pcs[m].trefferuebrig--;
			if (pcs[m].trefferuebrig == 0) {
				game_end = true;
			}
		}
		else {
			zaehler = (zaehler >= 100) ? 0 : zaehler + 1;
			//hit_current_zug = 0;
		}
	}
}

void Draw::setansig(string& x) {

}

wstring s2ws(const string& s, bool isUtf8)
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