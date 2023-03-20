#include "headers/Draw.h"
#include "headers/computer.h"
#include "headers/player.h"
using namespace std;
//#if defined(_WIN32) || defined(_WIN64) 
//int currentsize = 0;
//int lastsize = 0;
void Draw::drawMap(int x, vector<string>& map, bool mapp2_true) { // x ist die verschiebung von der ganzen map nach rechts 
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(console, &screen);
	COORD pos = { 0, 0 };
	pos.Y = 0;
	pos.X = x;
	DWORD bytesWritten1 = 0; //DWORD ist ein unsigned long ich schreibe hier aber DWORD weil es so einfache ist zwischen Win Api und anderen sachen zu unterscheiden
	DWORD bytesWritten2 = 0;
	DWORD bytesWritten3 = 0;
	WORD z = 15;
	int height = map.size();
	//if (currentsize != lastsize){
	//	cout << "bitte die fontsize vom Terminal ändern";
	//	for (int i = 0; i < height; i++){
	//		pos.Y = i;
	//		for (int k = 0; k < map[i].size(); k++){
	//			WriteConsoleOutputAttribute(console, &z, 1, pos, &bytesWritten3);
	//		}
	//	}
	//}
	for (int y = 0; y < height; y++) {
		std::wstring outputstr = s2ws(map[y], 1); // hier mache ich aus dem string vom vektor<string> map am index y ein wide string. Wide strings sind strings aus 2 byte großen chars.
		pos.Y = y;								  // hier sage ich, dass die coordinate pos 1 nach unten geht
		pos.X = x;								  // das ist für die rechtsverschiebung
		WriteConsoleOutputCharacter(console, outputstr.c_str(), outputstr.length() - 1, pos, &bytesWritten1); //hier beschreibe ich das terminal
		//pos.Y = y;
		//pos.X = x;
		//WriteConsoleOutputAttribute(console,&z , outputstr.length() - 1, pos, &bytesWritten2);
		if (y < 10) { //
			for (int i = 0; i < 10; i++) {
				COORD copycord = coords[y][i];
				copycord.X += x;
				WORD c1 = colors[y][i]; //ich hatte ein paar probleme hier wenn ich einfach colors[y][i] in die function WriteConsoleOutputAttribute geben gab es ein paar bugs
				WORD c2 = colors2[y][i];
				WriteConsoleOutputAttribute(console, &c1, 1, copycord, &bytesWritten2);
				if (mapp2_true) {
					WriteConsoleOutputAttribute(console, &c2, 1, coords2[y][i], &bytesWritten2);
				}
			}
			if (y < 5) {
				COORD c = coords3[y];
				c.X += x;
				if (!mapp2_true) {
					c.X = c.X - 61;  //61 is the size of one row of mapp2
				}
				WriteConsoleOutputAttribute(console, &colors3[y], 1, c, &bytesWritten2);
			}
		}
	}
	SetConsoleActiveScreenBuffer(console);
	//lastsize = currentsize;
}
void Draw::cursPosSet(int x, int y) {
	COORD cursorpos = { 0,0 };
	cursorpos.X = x; cursorpos.Y = y;
	SetConsoleCursorPosition(console, cursorpos);
}

template<typename _T, typename __T>
void Draw::setmakedrawmap(vector<string>& m2, string& x, _T& p1, __T& p2, bool z, bool u, int x2, bool mapp2_true) { // die funktion macht erstmal die ganze karte und dann fügt sie diese zusammen und schließlich  
	static_assert(std::is_same<_T, Player>::value || std::is_same<_T, Computer>::value, "argument 3 muss entweder vom Typ Player oder Computer sein");   // damit hier nicht die falschen argumente reinkommen
	static_assert(std::is_same<__T, Player>::value || std::is_same<__T, Computer>::value, "argument 4 muss entweder vom Typ Player oder Computer sein");
	makemap(p2.treffer, p1.eigeneschiffe, charptrs, z, colors); // z und u sagen ob wir sehen sollen wo die schiffe sind

	if (mapp2_true) { // wenn mapp2 im code benutzt wird dann wird das hier gemacht
		makemap(p1.treffer, p2.eigeneschiffe, charptrs2, u, colors2);
		setmap(mappp, mapp, m2, mapp3, x);
	}
	else {
		setmap(mappp, mapp, emptyvec, mapp3, x);
	}
	// x ist ein string der je nach nutzen anders ist
	// mappp ist die gesamte karte die gezeigt wird mapp3 ist das stück wo die legende zu sehen ist
	// mapp ist ein stueck der karte welche immer gezeigt werden muss
	drawMap(x2, mappp, mapp2_true);    //x2 ist wie weit das ganze konstrukt nach rechts verschoben wird
}

template<typename _T, typename __T>
int Draw::gameloop(Draw& drawer, _T& p1, __T& p2, bool z, bool x, bool y, bool c) {//der erste bool sagt ob man die schiffe in der linken map sehen kann
	//der zweite bool sagt ob man die schiffe in der rechten map sehen kann
	//der dritte bool sagt ob die rechte map ueberhaupt existiert
	//der vierte bool sagt ob die map sich bei jedem zug nicht aendert
	static_assert(is_same<_T, Player>::value || is_same<_T, Computer>::value, "argument 2 needs to be of type Player or Computer ");   // das ist dafür, dass nicht die falschen typen reingemacht werden
	static_assert(is_same<__T, Player>::value || is_same<__T, Computer>::value, "argument 3 needs to be of type Player or Computer ");
	int wahlS = 0;
	int wahlR = 0;
	string wahl_temp;
	if (c) { // wenn immer die gleiche map seien soll
		if (zaehler % 2 == 0) { // is 0 wenn spieler 1 dran ist
			do {
				if (is_same<_T, Player>::value || !y) {
					playermove(p1, p2, wahlR, wahlS, z, x, y);
				}
				else {
					wahlR = rand() % 10;
					wahlS = rand() % 10;
				}
			} while (!p1.validmove(wahlR, wahlS, p1.treffer));
			p1.treffer[wahlR][wahlS] = 1;
		}
		else {
			do {
				if (is_same<__T, Player>::value || !y) {

					playermove(p1, p2, wahlR, wahlS, z, x, y);

				}
				else {
					wahlR = rand() % 10;
					wahlS = rand() % 10;
				}
			} while (!p2.validmove(wahlR, wahlS, p2.treffer));
			p2.treffer[wahlR][wahlS] = 1;
		}
	}
	else {
		do {
			if (is_same<_T, Player>::value || !y) {

				playermove(p1, p2, wahlR, wahlS, z, x, y);

			}
			else {
				wahlR = rand() % 10;
				wahlS = rand() % 10;
			}
		} while (!p1.validmove(wahlR, wahlS, p1.treffer));
		p1.treffer[wahlR][wahlS] = 1;
	}
	if (is_same<_T, __T>::value && is_same<_T, Player>::value) {
		setmakedrawmap(mapp2, temp2, p1, p2, 0, 0, 0, y);
		cursPosSet(0, 25);
		system("pause");
	}
	else {
		setmakedrawmap(mapp2, nthing, p1, p2, z, x, 0, y);
	}
	cursPosSet(24, 25);
	if (c) {
		if (zaehler % 2 == 0) { // ist gleich eins wenn spieler 1 drann ist so nach der logik
			zaehler = gamecheck(p1, p2, wahlR, wahlS);

		}
		else {
			zaehler = gamecheck(p2, p1, wahlR, wahlS);
		}
	}
	else
	{
		zaehler = gamecheck(p1, p2, wahlR, wahlS);

	}
	return zaehler;
}

template<typename _T, typename __T>
int Draw::gamecheck(_T& p1, __T& p2, int& y, int& x) {
	static_assert(std::is_same<_T, Player>::value || std::is_same<_T, Computer>::value, "argument 3 muss entweder vom Typ Player oder Computer sein");   // damit hier nicht die falschen argumente reinkommen
	static_assert(std::is_same<__T, Player>::value || std::is_same<__T, Computer>::value, "argument 4 muss entweder vom Typ Player oder Computer sein");

	if (p1.treffer[y][x] == 1 && p2.eigeneschiffe[y][x] == 1) {
		//hit_current_zug = 1;
		p1.trefferuebrig--;
		if (p1.trefferuebrig == 0) {
			game_end = true;
		}
	}
	else {
		zaehler++;
	}
	return zaehler;
}
void Draw::drawPvP(Draw& drawer) {
	game_end = false;
	array<Player, 2> players;
	zaehler = 0;
	int n = 0;
	int m = 1;
	for (int i = 0; i < 2; i++) {
		players[i].placeships(drawer, console);
	}
	while (!game_end) {
		if (zaehler % 2 == 0) {
			m = 1;
			n = 0;
		}
		else {
			m = 0;
			n = 1;
		}
		zaehler = gameloop(drawer, players[n], players[m], 1, 0, 1, 0);
	}
	players[0].resettonormal(drawer);
}

void Draw::drawPv(Draw& drawer) {
	game_end = false;
	Computer pc;
	zaehler = 0;
	pc.placeships(drawer, console);
	mapp[0] = "Gegner Schiffe                                               ";
	pc.trefferuebrig = 20;
	int zahl = 0;
	while (!game_end) {
		zaehler = gameloop(drawer, pc, pc, 1, 0, 0, 0);
		zahl++;
	}
	pc.resettonormal(drawer);
	mapp[0] = "Eigene Karte                                                 ";
}

void Draw::drawPvC(Draw& drawer) {
	game_end = false;
	Computer pc1;
	Player p1;
	zaehler = 0;

	pc1.placeships(drawer, console);
	p1.placeships(drawer, console);
	while (!game_end) {
		zaehler = gameloop(drawer, p1, pc1, 1, 0, 1, 1);
	}
	system("pause");
}
void Draw::setmap(std::vector<std::string>& result, std::vector<std::string>& mp1, std::vector<std::string>& mp2, std::vector<std::string>& mp3, std::string& x) {
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
void Draw::drawCvC(Draw& drawer) {
	game_end = false;
	array<Computer, 2> pcs;
	int wahlR = 0;
	int wahlS = 0;
	string wahl_temp = "0";
	int n = 0;
	int m = 1;
	for (int i = 0; i < 2; i++)
	{
		pcs[i].placeships(drawer, console);
	}
	pcs[0].trefferuebrig = 20;
	pcs[1].trefferuebrig = 20;
	mapp[0] = "Computer 1                                                   ";
	mapp2[0] = "Computer 2                                                   ";
	while (!game_end) {
		zaehler = gameloop(drawer, pcs[0], pcs[1], 1, 1, 1, 1);
	}
	mapp[0] = "Eigene Karte                                                ";
	mapp2[0] = "Gegner Karte                                                ";
	cursPosSet(0, 25);
	//system("pause");

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
	auswahl = (x == 1 || x == 2) ? stoii(as, 48) : stoii(as, 65);
	return;
}



wstring s2ws(const string& s, bool isUtf8)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(isUtf8 ? CP_UTF8 : CP_ACP, 0, s.c_str(), slength, 0, 0);
	std::wstring buf;
	buf.resize(len);
	MultiByteToWideChar(isUtf8 ? CP_UTF8 : CP_ACP, 0, s.c_str(), slength, const_cast<wchar_t*>(buf.c_str()), len);
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
	int resultInt = 0;
	int xy = (x == 48) ? 57 : (x == 65) ? 90 : 97;
	for (char k : a) {
		if ((int)k >= x && (int)k <= xy) {

			resultInt = ((int)k - x) + resultInt * 10;
		}
	}
	return resultInt;
}
template<typename _T, typename __T>
void Draw::pcmove(Draw&, _T&, __T&, int&, int&){


}

template<typename _T, typename __T>
void Draw::playermove(_T& p1, __T& p2, int& wahlR, int& wahlS, bool x, bool y, bool z) {
	string wahl_temp;
	setmakedrawmap(mapp2, temp, p1, p2, x, y, 0, z);
	cursPosSet(24, 25);
	wahlget(wahlR, wahl_temp, 0);
	setmakedrawmap(mapp2, temp2, p1, p2, x, y, 0, z);
	cursPosSet(24, 25);
	wahlget(wahlS, wahl_temp, 2);
	cursPosSet(24, 25);
}
void smallToBig(std::string& s) {
	size_t length = s.size();
	for (size_t i = 0; i < length; i++){
		if (s[i]>='a'&&s[i]<= 'z'){
			s[i] = (s[i] - 32);
		}
	}
}

Draw::Draw() {
	//24;
	mapp = {
		"Eigene Karte                                                 ",
		"  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                  ",
		"---------------------------------------------                ",
		"A | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | A                ",
		"---------------------------------------------                ",
		"B | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | B                ",
		"---------------------------------------------                ",
		"C | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | C                ",
		"---------------------------------------------                ",
		"D | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | D                ",
		"---------------------------------------------                ",
		"E | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | E                ",
		"---------------------------------------------                ",
		"F | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | F                ",
		"---------------------------------------------                ",
		"G | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | G                ",
		"---------------------------------------------                ",
		"H | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | H                ",
		"---------------------------------------------                ",
		"I | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | I                ",
		"---------------------------------------------                ",
		"J | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | J                ",
		"---------------------------------------------                ",
		"  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                  "
	};
	mapp2 = {
	   "Gegner Karte                                                 ",
	   "  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                  ",
	   "---------------------------------------------                ",
	   "A | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | A                ",
	   "---------------------------------------------                ",
	   "B | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | B                ",
	   "---------------------------------------------                ",
	   "C | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | C                ",
	   "---------------------------------------------                ",
	   "D | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | D                ",
	   "---------------------------------------------                ",
	   "E | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | E                ",
	   "---------------------------------------------                ",
	   "F | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | F                ",
	   "---------------------------------------------                ",
	   "G | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | G                ",
	   "---------------------------------------------                ",
	   "H | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | H                ",
	   "---------------------------------------------                ",
	   "I | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | I                ",
	   "---------------------------------------------                ",
	   "J | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | ~ | J                ",
	   "---------------------------------------------                ",
	   "  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                  "
	};
	mapp3 = {
	   "                                ",
	   "Legende:                        ",
	   "                                ",
	   "~ = noch nicht getestetes Wasser",
	   "                                ",
	   "* = Treffer                     ",
	   "                                ",
	   "# = Schiff                      ",
	   "                                ",
	   "o = verfehlt                    ",
	   "                                ",
	   "X = Schiff Kaputt               ",
	   "                                ",
	   "Anzahl Schiffe uebrig:          ",
	   "                                ",
	   "Player 1:       Player2:        ",
	   "                                ",
	   "#### : 1        #### : 1        ",
	   "###  : 2        ###  : 2        ",
	   "##   : 3        ##   : 3        ",
	   "#    : 4        #    : 4        ",
	   "                                ",
	   "                                ",
	   "                                ",
	};

	map1 = "                ";
	mapp3[3][0] = unused;
	mapp3[5][0] = hit;
	mapp3[7][0] = ship;
	mapp3[9][0] = miss;
	mapp3[11][0] = destroyed;
	charptrs = {
		{&mapp[3][4],&mapp[3][8],&mapp[3][12],&mapp[3][16],&mapp[3][20], &mapp[3][24], &mapp[3][28], &mapp[3][32], &mapp[3][36], &mapp[3][40]},
		{&mapp[5][4],&mapp[5][8],&mapp[5][12],&mapp[5][16],&mapp[5][20], &mapp[5][24], &mapp[5][28], &mapp[5][32], &mapp[5][36], &mapp[5][40]},
		{&mapp[7][4],&mapp[7][8],&mapp[7][12],&mapp[7][16],&mapp[7][20], &mapp[7][24], &mapp[7][28], &mapp[7][32], &mapp[7][36], &mapp[7][40]},
		{&mapp[9][4],&mapp[9][8],&mapp[9][12],&mapp[9][16],&mapp[9][20], &mapp[9][24], &mapp[9][28], &mapp[9][32], &mapp[9][36], &mapp[9][40]},
		{&mapp[11][4],&mapp[11][8],&mapp[11][12],&mapp[11][16],&mapp[11][20], &mapp[11][24], &mapp[11][28], &mapp[11][32], &mapp[11][36], &mapp[11][40]},
		{&mapp[13][4],&mapp[13][8],&mapp[13][12],&mapp[13][16],&mapp[13][20], &mapp[13][24], &mapp[13][28], &mapp[13][32], &mapp[13][36], &mapp[13][40]},
		{&mapp[15][4],&mapp[15][8],&mapp[15][12],&mapp[15][16],&mapp[15][20], &mapp[15][24], &mapp[15][28], &mapp[15][32], &mapp[15][36], &mapp[15][40]},
		{&mapp[17][4],&mapp[17][8],&mapp[17][12],&mapp[17][16],&mapp[17][20], &mapp[17][24], &mapp[17][28], &mapp[17][32], &mapp[17][36], &mapp[17][40]},
		{&mapp[19][4],&mapp[19][8],&mapp[19][12],&mapp[19][16],&mapp[19][20], &mapp[19][24], &mapp[19][28], &mapp[19][32], &mapp[19][36], &mapp[19][40]},
		{&mapp[21][4],&mapp[21][8],&mapp[21][12],&mapp[21][16],&mapp[21][20], &mapp[21][24], &mapp[21][28], &mapp[21][32], &mapp[21][36], &mapp[21][40]},
	};
	charptrs2 = {
		{&mapp2[3][4],&mapp2[3][8],&mapp2[3][12],&mapp2[3][16],&mapp2[3][20], &mapp2[3][24], &mapp2[3][28], &mapp2[3][32], &mapp2[3][36], &mapp2[3][40]},
		{&mapp2[5][4],&mapp2[5][8],&mapp2[5][12],&mapp2[5][16],&mapp2[5][20], &mapp2[5][24], &mapp2[5][28], &mapp2[5][32], &mapp2[5][36], &mapp2[5][40]},
		{&mapp2[7][4],&mapp2[7][8],&mapp2[7][12],&mapp2[7][16],&mapp2[7][20], &mapp2[7][24], &mapp2[7][28], &mapp2[7][32], &mapp2[7][36], &mapp2[7][40]},
		{&mapp2[9][4],&mapp2[9][8],&mapp2[9][12],&mapp2[9][16],&mapp2[9][20], &mapp2[9][24], &mapp2[9][28], &mapp2[9][32], &mapp2[9][36], &mapp2[9][40]},
		{&mapp2[11][4],&mapp2[11][8],&mapp2[11][12],&mapp2[11][16],&mapp2[11][20], &mapp2[11][24], &mapp2[11][28], &mapp2[11][32], &mapp2[11][36], &mapp2[11][40]},
		{&mapp2[13][4],&mapp2[13][8],&mapp2[13][12],&mapp2[13][16],&mapp2[13][20], &mapp2[13][24], &mapp2[13][28], &mapp2[13][32], &mapp2[13][36], &mapp2[13][40]},
		{&mapp2[15][4],&mapp2[15][8],&mapp2[15][12],&mapp2[15][16],&mapp2[15][20], &mapp2[15][24], &mapp2[15][28], &mapp2[15][32], &mapp2[15][36], &mapp2[15][40]},
		{&mapp2[17][4],&mapp2[17][8],&mapp2[17][12],&mapp2[17][16],&mapp2[17][20], &mapp2[17][24], &mapp2[17][28], &mapp2[17][32], &mapp2[17][36], &mapp2[17][40]},
		{&mapp2[19][4],&mapp2[19][8],&mapp2[19][12],&mapp2[19][16],&mapp2[19][20], &mapp2[19][24], &mapp2[19][28], &mapp2[19][32], &mapp2[19][36], &mapp2[19][40]},
		{&mapp2[21][4],&mapp2[21][8],&mapp2[21][12],&mapp2[21][16],&mapp2[21][20], &mapp2[21][24], &mapp2[21][28], &mapp2[21][32], &mapp2[21][36], &mapp2[21][40]},
	};
	charptrs3 = {
		{&mapp3[17][7],&mapp3[17][23]},
		{&mapp3[18][7],&mapp3[18][23]},
		{&mapp3[19][7],&mapp3[19][23]},
		{&mapp3[20][7],&mapp3[20][23]}
	};
	coords = {
	{{20,3},{24,3},{28,3},{32,3},{36,3},{40,3},{44,3},{48,3},{52,3},{56,3}},
	{{20,5},{24,5},{28,5},{32,5},{36,5},{40,5},{44,5},{48,5},{52,5},{56,5}},
	{{20,7},{24,7},{28,7},{32,7},{36,7},{40,7},{44,7},{48,7},{52,7},{56,7}},
	{{20,9},{24,9},{28,9},{32,9},{36,9},{40,9},{44,9},{48,9},{52,9},{56,9}},
	{{20,11},{24,11},{28,11},{32,11},{36,11},{40,11},{44,11},{48,11},{52,11},{56,11}},
	{{20,13},{24,13},{28,13},{32,13},{36,13},{40,13},{44,13},{48,13},{52,13},{56,13}},
	{{20,15},{24,15},{28,15},{32,15},{36,15},{40,15},{44,15},{48,15},{52,15},{56,15}},
	{{20,17},{24,17},{28,17},{32,17},{36,17},{40,17},{44,17},{48,17},{52,17},{56,17}},
	{{20,19},{24,19},{28,19},{32,19},{36,19},{40,19},{44,19},{48,19},{52,19},{56,19}},
	{{20,21},{24,21},{28,21},{32,21},{36,21},{40,21},{44,21},{48,21},{52,21},{56,21}}
	};
	coords2 = {
	{{81,3},{85,3},{89,3},{93,3},{97,3},{101,3},{105,3},{109,3},{113,3},{117,3}},
	{{81,5},{85,5},{89,5},{93,5},{97,5},{101,5},{105,5},{109,5},{113,5},{117,5}},
	{{81,7},{85,7},{89,7},{93,7},{97,7},{101,7},{105,7},{109,7},{113,7},{117,7}},
	{{81,9},{85,9},{89,9},{93,9},{97,9},{101,9},{105,9},{109,9},{113,9},{117,9}},
	{{81,11},{85,11},{89,11},{93,11},{97,11},{101,11},{105,11},{109,11},{113,11},{117,11}},
	{{81,13},{85,13},{89,13},{93,13},{97,13},{101,13},{105,13},{109,13},{113,13},{117,13}},
	{{81,15},{85,15},{89,15},{93,15},{97,15},{101,15},{105,15},{109,15},{113,15},{117,15}},
	{{81,17},{85,17},{89,17},{93,17},{97,17},{101,17},{105,17},{109,17},{113,17},{117,17}},
	{{81,19},{85,19},{89,19},{93,19},{97,19},{101,19},{105,19},{109,19},{113,19},{117,19}},
	{{81,21},{85,21},{89,21},{93,21},{97,21},{101,21},{105,21},{109,21},{113,21},{117,21}}
	};
	coords3 = { { 138 ,3},{138 ,5},{138 ,7},{138 ,9},{138, 11} };
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(console, &cursorInfo);
	SetConsoleActiveScreenBuffer(console);
	//CONSOLE_SCREEN_BUFFER_INFO screen;
	//GetConsoleScreenBufferInfo(console, &screen);
	//if (screen.dwSize.X < 170) {
	//	cout << "bitte die momentane font size ändern";
	//	while (screen.dwSize.X < 170) {
	//
	//	}
	//}
	//lastsize = screen.dwSize.X;
}
