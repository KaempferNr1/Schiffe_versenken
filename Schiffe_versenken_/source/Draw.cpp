#include "headers/Draw.h"
#include "headers/computer.h"
using namespace std;
//#if defined(_WIN32) || defined(_WIN64) 
void Draw::drawMap(HANDLE& console, int x, vector<string>& map, bool mapp2_true) {
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(console, &screen);
	COORD pos = { 0, 0 };
	pos.Y = 0;
	pos.X = x;
	DWORD bytesWritten;
	DWORD bytesWritten2;
	WORD z = 3;
	int height = map.size();
	for (int y = 0; y < height; y++) {
		std::wstring outputstr = s2ws(map[y], 1);
		pos.Y = y;
		pos.X = x;
		//cout << map[y];

		WriteConsoleOutputCharacter(console, outputstr.c_str(), outputstr.length() - 1, pos, &bytesWritten);
		if (y < 10)
		{

			for (int i = 0; i < 10; i++)
			{
				COORD copycord = coords[y][i];
				copycord.X += x;
				WORD c1 = colors[y][i];
				WORD c2 = colors2[y][i];
				WriteConsoleOutputAttribute(console, &c1, 1, copycord, & bytesWritten2);
				if (mapp2_true)
				{
					WriteConsoleOutputAttribute(console, &c2, 1, coords2[y][i], &bytesWritten2);
				}


			}
			if (y < 5)
			{
				COORD c = coords3[y];
				c.X += x;
				if (!mapp2_true)
				{
					c.X =c.X - 61;
				}
				WriteConsoleOutputAttribute(console, &colors3[y], 1, c, &bytesWritten2);
			}

		}


		//WriteConsoleOutputAttribute(console,)
	}
	SetConsoleActiveScreenBuffer(console);
}
void Draw::cursPosSet(HANDLE& console, int x, int y, COORD& cursorpos) {
	cursorpos.X = x; cursorpos.Y = y;
	SetConsoleCursorPosition(console, cursorpos);
}

template<typename _T, typename __T>
void Draw::setmakedrawmap(HANDLE& console,vector<string>& m2, string& x, _T& pc1, __T& pc2, bool z, bool u, int x2,bool mapp2_true) {
	makemap(pc1.treffer, pc2.eigeneschiffe, charptrs, z, colors);
	if (mapp2_true) {
		makemap(pc2.treffer, pc1.eigeneschiffe, charptrs2, u, colors2);
	}
	setmap(console, mappp, mapp, m2, mapp3, x);

	drawMap(console, x2, mappp,mapp2_true);
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




void Draw::drawPvP(HANDLE& console, Draw& drawer) {
	game_end = false;
	array<Player, 2> players;
	COORD cursorPos = { 0,0 };
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
		players[i].placeships(drawer, console);
	}
	string temp = "Waehlen sie die Reihe: ";
	string temp2 = "Waehlen sie die Spalte: ";
	string temp3 = "Druecken sie enter";
	while (!game_end) {
		std::cout << "hallo";
		string waiter;
		if (zaehler % 2 == 0) {
			m = 1;
			n = 0;
		}
		else {
			m = 0;
			n = 1;
		}

		makemap(players[m].treffer, players[n].eigeneschiffe, charptrs, 1, colors);
		makemap(players[n].treffer, players[m].eigeneschiffe, charptrs2, 0, colors2);
		setmap(console, mappp, mapp, mapp2, mapp3, nthing);
		drawMap(console, 0, mappp,1);
		do {
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			setmap(console, mappp, mapp, mapp2, mapp3, temp);
			drawMap(console, 0, mappp,1);
			wahlget(wahlR, wahl_temp, 0);
			SetConsoleCursorPosition(console, cursorPos);
			setmap(console, mappp, mapp, mapp2, mapp3, temp2);
			drawMap(console, 0, mappp,1);
			SetConsoleCursorPosition(console, cursorPos);
			wahlget(wahlS, wahl_temp, 2);
			//cout << wahlS;
		} while (!players[m].validmove(wahlR, wahlS, players[m].treffer));
		//players[m].movemaker(wahlR, wahlS, zaehler % 2, drawer);
		//cper.movemaker(wahlR,wahlS,drawer,players[m],players[n]);
		players[m].treffer[wahlR][wahlS] = 1;
		makemap(players[n].treffer, players[m].eigeneschiffe, charptrs, 1, colors);
		makemap(players[m].treffer, players[n].eigeneschiffe, charptrs2, 0, colors2);
		setmap(console, mappp, mapp, mapp2, mapp3, nthing);
		drawMap(console, 0, mappp,1);
		cursorPos.X = 0; cursorPos.Y = 25;
		SetConsoleCursorPosition(console, cursorPos);
		system("pause");
		cursorPos.X = 24; cursorPos.Y = 25;
		SetConsoleCursorPosition(console, cursorPos);

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

}

void Draw::drawPv(HANDLE& console, Draw& drawer) {
	game_end = false;
	Computer pc;
	COORD cursorPos = { 0,0 };
	int zaehler = 0;
	int wahlR = 0;
	int wahlS = 0;
	string wahl_temp = "0";
	int n = 0;
	int m = 1;
	cursorPos.X = 24;
	cursorPos.Y = 25;
	pc.placeships(drawer, console);
	string temp = "Waehlen sie die Reihe: ";
	string temp2 = "Waehlen sie die Spalte: ";
	string temp3 = "Druecken sie enter";
	mapp[0] = "Gegner Schiffe                                               ";

	pc.trefferuebrig = 20;
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
		//cursorPos.X = 24; cursorPos.Y = 25;
		//makemap(pc.treffer, pc.eigeneschiffe, charptrs, 1, colors);
		//setmakedrawmap(console, mappp, mapp, emptyvec, mapp3, temp, pc, pc, 0, 0, 0, 0);
		do {
			setmakedrawmap(console, emptyvec, temp, pc, pc, 1, 0, 0, 0);
			cursPosSet(console, 24, 25, cursorPos);
			wahlget(wahlR, wahl_temp, 0);
			//setmap(console, mappp, mapp, emptyvec, mapp3, temp2);
			//drawMap(console, 0, mappp);
			setmakedrawmap(console, emptyvec, temp2, pc, pc, 1, 0, 0, 0);
			cursPosSet(console, 24, 25, cursorPos);
			wahlget(wahlS, wahl_temp, 2);
			cursPosSet(console, 24, 25, cursorPos);
		} while (!pc.validmove(wahlR, wahlS, pc.treffer));
		pc.treffer[wahlR][wahlS] = 1;
		setmakedrawmap(console, emptyvec, nthing, pc, pc, 1, 0, 0, 0);
		cursPosSet(console, 0, 25, cursorPos);
		system("pause");
		//makemap(pc.treffer, pc.eigeneschiffe, charptrs, 1);
		//setmap(console, mappp, mapp, emptyvec, mapp3, nthing);
		//drawMap(console, 0, mappp);
		if (pc.treffer[wahlR][wahlS] == 1 && pc.eigeneschiffe[wahlR][wahlS] == 1) {
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
	mapp[0] = "Computer 1                                                   ";
}

void Draw::drawPvC(HANDLE& console, Draw& drawer) {
	Computer pc1;
	Player p1;
	pc1.placeships(drawer, console);
	p1.placeships(drawer, console);
	game_end = false;
}
void Draw::setmap(HANDLE& console, std::vector<std::string>& result, std::vector<std::string>& mp1, std::vector<std::string>& mp2, std::vector<std::string>& mp3, std::string& x) {
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
		if ((unsigned)width > result[k].size()) {
			for (int q = 0; q < (signed int)(width - result[k].size()); q++) {
				temp = temp + " ";
			}
		}

		result[k] = result[k] + temp;
	}
}
void Draw::drawCvC(HANDLE& console, Draw& drawer) {
	game_end = false;
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
		pcs[i].placeships(drawer, console);
	}
	string temp = "Waehlen sie die Reihe: ";
	string temp2 = "Waehlen sie die Spalte: ";
	string temp3 = "Druecken sie enter";
	pcs[0].trefferuebrig = 20;
	pcs[1].trefferuebrig = 20;
	mapp[0] = "Computer 1                                                   ";
	mapp2[0] = "Computer 2                                                   ";
	int zahl = 0;
	pair<Player, Computer> I;
	while (!game_end) {
		string waiter;
		if (zaehler % 2 == 0) {
			m = 0;
			n = 1;
		}
		else {
			m = 1;
			n = 0;
		}
		setmakedrawmap(console,mapp2,nthing, pcs[0], pcs[1], true, true, 0, 1);
		do {
			wahlR = rand() % 10;
			wahlS = rand() % 10;
		} while (!pcs[m].validmove(wahlR, wahlS, pcs[m].treffer));
		pcs[m].treffer[wahlR][wahlS] = 1;
		setmakedrawmap(console, mapp2, nthing, pcs[0], pcs[1], true, true, 0, 1);
		zahl++;
		if (pcs[m].treffer[wahlR][wahlS] == 1 && pcs[n].eigeneschiffe[wahlR][wahlS] == 1) {
			pcs[n].trefferuebrig = pcs[n].trefferuebrig - 1;
			if (pcs[n].trefferuebrig == 0) {
				game_end = true;
			}
		}
		else {
			zaehler++;
		}
	}
	mapp[0] = "Eigene Karte                                                ";
	mapp2[0] = "Gegner Karte                                                ";
	cursPosSet(console, 0, 25, cursorPos);
	std::cout << zahl;
	system("pause");
}


void Draw::setansig(string& x) {

}
void Draw::wahlget(int& auswahl, string& as, int x) {
	//system("cls");
	if (x == 1) {
		system("cls");
		for (size_t i = 0; i < moeglichkeiten.size(); i++) {
			cout << "\t" << i + 1 << "\t" << moeglichkeiten[i];
		}
	}
	cin >> as;
	//if (x == 1 || x == 2) { auswahl = stoii(as); }
	auswahl = (x == 1 || x == 2) ? stoii(as, 48) : stoii(as, 65);
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

void Draw::makemap(vector<vector<bool>>& ships_see, vector<vector<bool>>& ships, vector<vector<char*>>& charptrs, bool z, vector<vector<WORD>>& colorss) {
	for (int i = 0; i < sizefield; i++) {
		for (int k = 0; k < sizefield; k++) {
			if (ships_see[i][k] == 1 && ships[i][k] == 0) {
				*charptrs[i][k] = miss;
				colorss[i][k] = missedc;
			}
			else if ((ships_see[i][k] == 0 && ships[i][k] == 1) && z) {
				*charptrs[i][k] = ship;
				colorss[i][k] = shipc;

			}
			else if (ships_see[i][k] == 1 && ships[i][k] == 1) {
				*charptrs[i][k] = hit;
				colorss[i][k] = hitc;
			}
			else {
				*charptrs[i][k] = unused;
				colorss[i][k] = unusedc;
			}
		}
	}

}

int stoii(string& a, int x) {
	int supi = 0;
	int xy = (x == 48) ? 57 : (x == 65) ? 90 : 97;
	for (char k : a) {
		if ((int)k >= x && (int)k <= xy) {

			supi = ((int)k - x) + supi * 10;
		}
	}
	return supi;
}