#include "Draw.h"
using namespace std;
void Draw::drawMap(HANDLE& console) {
	COORD pos = { 0, 0 };
	DWORD bytesWritten;
	int height = mappp.size();
	for (int x = 0; x < height; x++) {
		std::wstring wrapper = s2ws(mappp[x],1);
		pos.Y = x;
		WriteConsoleOutputCharacter(console, wrapper.c_str(), wrapper.length()-1, pos, &bytesWritten);
	}
	SetConsoleActiveScreenBuffer(console);
}
void Draw::makeMap(string x) {
	for (int i = 0; i < mapp.size(); i++){
		mappp[i] = "";
		mappp[i] = mapp[i] + mapp2[i] + mapp3[i] + "                                         ";
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
		for (int i = 0; i < moeglichkeiten.size(); i++){
			cout << "\t" << i + 1 << "\t" << moeglichkeiten[i];
		}
	}
	cin >> as;
	//if (x == 1 || x == 2) { auswahl = stoii(as); }
	auswahl = (x == 1 || x == 2) ? stoii(as,48):stoii(as,65);
}
void Draw::drawPvP(HANDLE& console) {
	COORD cursorPos;
	int zaehler = 0;
	int wahlR = 0;
	int wahlS = 0;
	string wahl_temp = "0";
	string waiter;
	Player player;
	//player.placeships();
	system("cls");
	makeMap(nthing);
	drawMap(console);
	system("cls");
	string temp ="Waehlen sie die Reihe: ";
	string temp2 = "Waehlen sie die Spalte: ";
	string temp3 = "Press Key to continue";
	while (!game_end) {
		*playptr1 = (zaehler % 2) ? '2' : '1';
		*playptr2 = (zaehler % 2) ? '1' : '2';
		makeMap(" ");
		drawMap(console);

		do{
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			makeMap(temp); drawMap(console);
			wahlget(wahlR, wahl_temp, 0);
			cursorPos.X = 24;cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			makeMap(temp2);drawMap(console);
			cursorPos.X = 24; cursorPos.Y = 25;
			SetConsoleCursorPosition(console, cursorPos);
			wahlget(wahlS, wahl_temp, 2);
			//cout << wahlS;
		} while (! player.validmove(wahlR,wahlS,(zaehler%2)));

		player.movemaker(wahlR, wahlS, zaehler % 2);
		makeMap(temp3);
		drawMap(console);
		cursorPos.X = 24; cursorPos.Y = 25;
		SetConsoleCursorPosition(console, cursorPos);
		cin >> waiter;
		zaehler = (zaehler >= 100) ? 0 : zaehler + 1;
	}

}

void Draw::drawPv(){
}

void Draw::drawPvC(){
}

void Draw::drawCvC(){
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

