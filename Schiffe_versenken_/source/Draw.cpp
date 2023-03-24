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
	//	cout << "bitte die fontsize vom Terminal �ndern";
	//	for (int i = 0; i < height; i++){
	//		pos.Y = i;
	//		for (int k = 0; k < map[i].size(); k++){
	//			WriteConsoleOutputAttribute(console, &z, 1, pos, &bytesWritten3);
	//		}
	//	}
	//}
	for (int y = 0; y < height; y++) {
		std::wstring outputstr = s2ws(map[y], 1); // hier mache ich aus dem string vom vektor<string> map am index y ein wide string. Wide strings sind strings aus 2 byte gro�en chars.
		pos.Y = y;								  // hier sage ich, dass die coordinate pos 1 nach unten geht
		pos.X = x;								  // das ist f�r die rechtsverschiebung
		WriteConsoleOutputCharacter(console, outputstr.c_str(), outputstr.length() - 1, pos, &bytesWritten1); //hier beschreibe ich das terminal
		//pos.Y = y;
		//pos.X = x;
		//WriteConsoleOutputAttribute(console,&z , outputstr.length() - 1, pos, &bytesWritten2);
		if (y < 10) { //
			for (int i = 0; i < 10; i++) {
				COORD copycord = coords[y][i];
				copycord.X += x;
				WORD c1 = colors[y][i]; //ich hatte ein paar probleme hier wenn ich einfach colors[y][i] in die function WriteConsoleOutputAttribute gebe gab es ein paar bugs
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
void Draw::setmakedrawmap(vector<string>& m2, string& x, _T& p1, __T& p2, bool z, bool u, int x2, bool mapp2_true) { // die funktion macht erstmal die ganze karte und dann f�gt sie diese zusammen und schlie�lich  
	static_assert(std::is_same<_T, Player>::value || std::is_same<_T, Computer>::value, "argument 3 muss entweder vom Typ Player oder Computer sein");   // damit hier nicht die falschen argumente reinkommen
	static_assert(std::is_same<__T, Player>::value || std::is_same<__T, Computer>::value, "argument 4 muss entweder vom Typ Player oder Computer sein");
	makemap(p2.treffer, p1.eigeneschiffe, charptrs, z, colors, dest1); // z und u sagen ob wir sehen sollen wo die schiffe sind

	if (mapp2_true) { // wenn mapp2 im code benutzt wird dann wird das hier gemacht
		makemap(p1.treffer, p2.eigeneschiffe, charptrs2, u, colors2, dest2);
		setmap(mappp, mapp, m2, mapp3, x);
	}
	else {
		setmap(mappp, mapp, emptyvec, mapp3, x);
	}
	// x ist ein string der je nach nutzen anders ist
	// mappp ist die gesamte karte die gezeigt wird mapp3 ist das st�ck wo die legende zu sehen ist
	// mapp ist ein stueck der karte welche immer gezeigt werden muss
	drawMap(x2, mappp, mapp2_true);    //x2 ist wie weit das ganze konstrukt nach rechts verschoben wird
}

template<typename _T, typename __T>
int Draw::gameloop(Draw& drawer, _T& p1, __T& p2, bool z, bool x, bool y, bool c) {//der erste bool sagt ob man die schiffe in der linken map sehen kann
	//der zweite bool sagt ob man die schiffe in der rechten map sehen kann
	//der dritte bool sagt ob die rechte map ueberhaupt existiert
	//der vierte bool sagt ob die map sich bei jedem zug nicht aendert
	static_assert(is_same<_T, Player>::value || is_same<_T, Computer>::value, "argument 2 needs to be of type Player or Computer ");   // das ist daf�r, dass nicht die falschen typen reingemacht werden
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
	isdestroyed(drawer, p1, p2);
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
	system("pause");
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
		zaehler = gameloop(drawer, p1, pc1, 1, 1, 1, 1);
	}
	system("pause");
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

void Draw::mostlikelysq(Draw& drawer){
	//Computer pc;
	//int anzahl = 0;
	system("cls");
	//cout << "anzahl der durchl�ufe eingeben";
	//cin >> anzahl;
	//vector<vector<int>> wahrscheinlich = vector<vector<int>>(10,vector<int>(10,0));
	//for (int i = 0; i < anzahl; i++){
	//	pc.placeships(drawer, console);
	//	for (int k = 0; k < 10; k++){
	//		for (int j = 0; j < 10; j++){
	//			if (pc.eigeneschiffe[k][j]){
	//				wahrscheinlich[k][j]++;
	//			}
	//		}
	//	}
	//	for (int g = 0; g < 10; g++){
	//		for (int h = 0; h < 10; h++){
	//			pc.eigeneschiffe[g][h] = 0;
	//		}
	//	}
	//}
	//for (int z = 0; z < 10; z++){
	//	for (int y = 0; y < 9; y++){
	//		cout << wahrscheinlich[z][y] << " , ";
	//	}
	//	cout << wahrscheinlich[z][9] << "\n";
	//}
	
	vector<vector<vector<int>>> durchleaufe = {
		//erster durchlauf mit tausend
		{
			{98, 155, 172, 187, 187, 193, 176, 168, 162, 133 },
			{172, 200, 184, 197, 224, 207, 206, 194, 176, 183},
			{160, 194, 191, 240, 236, 223, 226, 223, 197, 189},
			{170, 219, 220, 241, 223, 228, 242, 221, 202, 203},
			{196, 217, 209, 232, 229, 218, 237, 248, 208, 191},
			{170, 221, 227, 262, 231, 229, 217, 210, 202, 191},
			{197, 225, 236, 216, 214, 242, 258, 229, 196, 187},
			{164, 209, 235, 228, 215, 204, 239, 230, 195, 181},
			{144, 193, 213, 219, 222, 217, 214, 197, 179, 149},
			{116, 154, 194, 172, 176, 163, 169, 155, 153, 134},
		},
		// zweiter durchlauf mit 100.000
		{
			{11861 , 15417 , 17328 , 18118 , 18033 , 18138 , 18369 , 17613 , 15327 , 11715},
			{15447 , 18680 , 20296 , 21057 , 20829 , 20835 , 21034 , 20357 , 18738 , 15532},
			{17425 , 20628 , 22276 , 22826 , 22576 , 22432 , 22738 , 22126 , 20526 , 17696},
			{18181 , 21043 , 22844 , 23336 , 23221 , 23172 , 23128 , 22559 , 20885 , 18484},
			{18162 , 20980 , 22624 , 23119 , 23476 , 23384 , 23308 , 22738 , 21211 , 18547},
			{18014 , 20835 , 22650 , 23121 , 23049 , 23467 , 23297 , 22731 , 20926 , 18179},
			{18078 , 20876 , 22640 , 23319 , 23209 , 23227 , 23484 , 22850 , 20986 , 18189},
			{17459 , 20473 , 22132 , 22800 , 22718 , 22589 , 22991 , 22209 , 20224 , 17502},
			{15577 , 18636 , 20421 , 20881 , 20833 , 20800 , 21213 , 20518 , 18512 , 15496},
			{11869 , 15421 , 17431 , 18168 , 18262 , 18152 , 18449 , 17462 , 15375 , 11925},
		},
		// dritter durchlauf mit 1.000.000
		{
			{118472 , 154102 , 174888 , 181912 , 182031 , 182491 , 183012 , 175172 , 154570 , 117579},
			{154745 , 186355 , 204271 , 209980 , 209449 , 210567 , 211027 , 203723 , 186178 , 154377},
			{174335 , 204446 , 221382 , 227143 , 226409 , 227453 , 227036 , 220186 , 204184 , 174982},
			{181540 , 210572 , 226855 , 233031 , 233104 , 233172 , 234215 , 227592 , 210659 , 182185},
			{181450 , 209240 , 227333 , 232664 , 232498 , 231983 , 233011 , 225524 , 210249 , 181747},
			{181681 , 209559 , 226833 , 232360 , 232116 , 231766 , 232838 , 226990 , 209829 , 182228},
			{182804 , 209809 , 227817 , 233311 , 233184 , 232553 , 232755 , 227388 , 210007 , 182924},
			{175252 , 204014 , 221529 , 226814 , 226431 , 226663 , 227113 , 221885 , 203766 , 175312},
			{154061 , 185942 , 204128 , 210436 , 209615 , 209934 , 210759 , 203769 , 185527 , 154607},
			{117810 , 154455 , 174109 , 182389 , 181844 , 182398 , 182804 , 174610 , 154645 , 117546},
		},
		// vierter durchlauf mit 100.000
		{
			{11797 , 15471 , 17404 , 18067 , 17967 , 18058 , 18141 , 17430 , 15358 , 11623},
			{15386 , 18978 , 20333 , 21086 , 21081 , 21084 , 21035 , 20370 , 18529 , 15194},
			{17383 , 20375 , 21923 , 22916 , 23055 , 22730 , 22654 , 22063 , 20197 , 17275},
			{18125 , 21326 , 22707 , 23400 , 23317 , 23400 , 23258 , 22721 , 21176 , 18105},
			{18123 , 21299 , 22683 , 23311 , 23285 , 23319 , 23078 , 22824 , 21115 , 18106},
			{18196 , 21178 , 22738 , 23213 , 23317 , 23393 , 23380 , 22765 , 21079 , 18251},
			{18021 , 20909 , 22747 , 23144 , 23265 , 23215 , 23311 , 22659 , 21220 , 18334},
			{17311 , 20203 , 22209 , 22499 , 22740 , 22794 , 22731 , 21952 , 20500 , 17504},
			{15313 , 18588 , 20452 , 20993 , 21108 , 21179 , 21183 , 20268 , 18918 , 15505},
			{11976 , 15485 , 17377 , 17955 , 18176 , 18333 , 18064 , 17306 , 15563 , 11839},
		},
		// fuenfter durchlauf mit 10.000.000
		{
			{1182832 , 1541655 , 1749435 , 1823803 , 1816391 , 1818355 , 1824393 , 1747683 , 1543640 , 1181698},
			{1542380 , 1859529 , 2041698 , 2105642 , 2100538 , 2099320 , 2107843 , 2040395 , 1859064 , 1540869},
			{1747169 , 2040721 , 2211334 , 2272008 , 2267037 , 2264852 , 2272931 , 2210932 , 2040079 , 1745661},
			{1825485 , 2106415 , 2271822 , 2332804 , 2328149 , 2327342 , 2335542 , 2271868 , 2107464 , 1824288},
			{1820374 , 2101557 , 2265591 , 2326879 , 2322613 , 2323263 , 2328492 , 2266737 , 2099755 , 1817052},
			{1820689 , 2100767 , 2264683 , 2326896 , 2320835 , 2323942 , 2328965 , 2264989 , 2101337 , 1816855},
			{1826973 , 2106849 , 2271272 , 2333403 , 2327470 , 2328837 , 2333434 , 2271444 , 2106764 , 1822384},
			{1748284 , 2040390 , 2211250 , 2272326 , 2266659 , 2264580 , 2272556 , 2210037 , 2042407 , 1745140},
			{1542243 , 1859244 , 2041277 , 2107846 , 2100771 , 2099670 , 2106335 , 2040041 , 1862377 , 1539532},
			{1180483 , 1542305 , 1748733 , 1824788 , 1817396 , 1816753 , 1822348 , 1746948 , 1543205 , 1181909},
		},
		// sechster durchlauf mit 100.000
		{
			{11553 , 15268 , 17422 , 18189 , 18228 , 18173 , 18360 , 17548 , 15501 , 11766},
			{15311 , 18640 , 20454 , 20895 , 20926 , 20892 , 20963 , 20265 , 18602 , 15364},
			{17419 , 20520 , 22176 , 22647 , 22724 , 22691 , 22819 , 22304 , 20415 , 17354},
			{18382 , 20998 , 22667 , 23150 , 23224 , 23189 , 23382 , 22709 , 21099 , 18238},
			{18458 , 21026 , 22493 , 23063 , 23395 , 23204 , 23224 , 22499 , 21049 , 18128},
			{18422 , 20964 , 22448 , 23137 , 23493 , 23525 , 23349 , 22679 , 21172 , 18312},
			{18388 , 21038 , 22690 , 23206 , 23269 , 23490 , 23464 , 22724 , 21264 , 18366},
			{17322 , 20486 , 22362 , 22791 , 22628 , 22636 , 22685 , 22038 , 20504 , 17519},
			{15329 , 18651 , 20397 , 20894 , 20803 , 21016 , 21223 , 20386 , 18576 , 15644},
			{11729 , 15431 , 17504 , 18247 , 18095 , 18145 , 18208 , 17321 , 15272 , 11792},
		},
		// siebter durchlauf mit 1.000.000
		{
			{117850 , 153364 , 174930 , 182337 , 182181 , 182511 , 182298 , 174805 , 154849 , 118481},
			{153658 , 185152 , 203753 , 210299 , 210455 , 209553 , 210727 , 204407 , 186203 , 154467},
			{174765 , 203806 , 221234 , 227499 , 226680 , 226409 , 226900 , 220380 , 203974 , 174995},
			{182195 , 210341 , 226976 , 233262 , 233090 , 232921 , 233185 , 226273 , 211355 , 182490},
			{181811 , 209952 , 226481 , 233426 , 232402 , 232818 , 233591 , 226356 , 209891 , 181342},
			{181842 , 210246 , 226433 , 233058 , 233209 , 232420 , 232922 , 225547 , 209809 , 181775},
			{182534 , 210563 , 227345 , 233317 , 232669 , 232982 , 233269 , 225960 , 210107 , 182144},
			{175035 , 204579 , 220876 , 227779 , 227043 , 227056 , 226770 , 219473 , 203534 , 175097},
			{154248 , 186106 , 203715 , 210718 , 210022 , 210262 , 210454 , 203945 , 186375 , 154941},
			{118349 , 153823 , 174813 , 182923 , 181566 , 182010 , 182697 , 175373 , 154645 , 118542},
		},
		//achter durchlauf 10000000
		//anzahl der durchl�ufe eingeben 100000000
		{
			{1182162, 1541237, 1748704, 1824830, 1819640, 1817989, 1825306, 1748357, 1543076, 1182904},
			{1544345, 1859233, 2041589, 2107600, 2101726, 2099690, 2106124, 2041543, 1861820, 1541574},
			{1746899, 2037426, 2208729, 2270121, 2267513, 2265803, 2270272, 2208505, 2040377, 1744268},
			{1825116, 2106899, 2270433, 2335588, 2327846, 2328944, 2335564, 2271390, 2107006, 1823741},
			{1818055, 2098300, 2266254, 2329351, 2323113, 2322393, 2326824, 2263502, 2099566, 1816021},
			{1818254, 2101949, 2266814, 2329536, 2324371, 2323726, 2329251, 2266140, 2103134, 1816775},
			{1825416, 2106660, 2268533, 2330693, 2327096, 2328949, 2334793, 2271192, 2108538, 1822858},
			{1749831, 2041673, 2210090, 2271334, 2267027, 2264553, 2270583, 2210272, 2041926, 1746808},
			{1543591, 1859008, 2039791, 2106956, 2101835, 2101431, 2107521, 2039479, 1859473, 1540343},
			{1182252, 1539950, 1746835, 1823991, 1819277, 1818069, 1824619, 1748010, 1542211, 1181315},
		},
		// neunter durchlauf mit 100.000.000
		{
			{11821769, 15415490, 17478940, 18244049, 18183764, 18191998, 18246587, 17475787, 15427521, 11816469},
			{15433647, 18598334, 20415727, 21060161, 21012804, 21002114, 21077455, 20401275, 18608482, 15413474},
			{17478525, 20404033, 22095880, 22710483, 22666224, 22660707, 22711706, 22092282, 20408689, 17463027},
			{18248000, 21070302, 22714752, 23339537, 23298887, 23284818, 23352032, 22714096, 21071955, 18235193},
			{18186154, 21002871, 22659814, 23281801, 23238538, 23228969, 23285391, 22652988, 21004326, 18168641},
			{18188442, 21002876, 22654391, 23278179, 23239617, 23232175, 23291124, 22653603, 21010444, 18177795},
			{18251395, 21057055, 22709210, 23323752, 23280615, 23282597, 23340612, 22713042, 21062259, 18239747},
			{17483577, 20401575, 22102476, 22718046, 22669358, 22655914, 22725592, 22094563, 20405830, 17472313},
			{15424917, 18599464, 20405386, 21064514, 21002614, 21004140, 21062880, 20392235, 18592577, 15411369},
			{11817872, 15421551, 17482625, 18242967, 18176405, 18174949, 18235666, 17477201, 15424552, 11811474},
		}

	};
	vector<vector<vector<double>>> wahrscheinlichkeiten = vector<vector<vector<double>>>(9, vector<vector<double>>(10, vector<double>(10, 0.0)));
	vector<int> zahlen = {1000, 100000, 1000000, 100000, 10000000, 100000, 1000000 , 10000000, 100000000};
	vector<vector<double>> endwahrscheinlichkeit = vector<vector<double>>(10, vector<double>(10, 0.0));
	for (int q = 0; q < 9; q++){
		for (int rows = 0; rows < 10; rows++){
			for (int cols = 0; cols < 10; cols++){
				wahrscheinlichkeiten[q][rows][cols] = (double)durchleaufe[q][rows][cols]/zahlen[q];
			}
		}
	}
	
		for (int rows2 = 0; rows2 < 10; rows2++) {
			for (int cols2 = 0; cols2 < 10; cols2++) {
				endwahrscheinlichkeit[rows2][cols2] = (wahrscheinlichkeiten[0][rows2][cols2] + wahrscheinlichkeiten[1][rows2][cols2] + wahrscheinlichkeiten[2][rows2][cols2] + wahrscheinlichkeiten[3][rows2][cols2] + wahrscheinlichkeiten[4][rows2][cols2] + wahrscheinlichkeiten[5][rows2][cols2] + wahrscheinlichkeiten[6][rows2][cols2] + wahrscheinlichkeiten[7][rows2][cols2] + wahrscheinlichkeiten[8][rows2][cols2])/ 9;
			}
		}
	
	for (int z2 = 0; z2 < 10; z2++) {
		for (int y2 = 0; y2 < 9; y2++) {
			cout << endwahrscheinlichkeit[z2][y2] << " , ";
		}
		cout << endwahrscheinlichkeit[z2][9] << "\n";
	}
	cout << "\n";
	for (int z3 = 0; z3 < 10; z3++) {
		for (int y3 = 0; y3 < 9; y3++) {
			cout << endwahrscheinlichkeit[z3][y3]*100 << "% , ";
		}
		cout << endwahrscheinlichkeit[z3][9]*100 << "%\n";
	}
	system("pause");

}

wstring s2ws(const string& s, bool isUtf8){
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(isUtf8 ? CP_UTF8 : CP_ACP, 0, s.c_str(), slength, 0, 0);
	std::wstring buf;
	buf.resize(len);
	MultiByteToWideChar(isUtf8 ? CP_UTF8 : CP_ACP, 0, s.c_str(), slength, const_cast<wchar_t*>(buf.c_str()), len);
	return buf;
}

void Draw::makemap(vector<vector<bool>>& ships_see, vector<vector<bool>>& ships, vector<vector<char*>>& charptrs, bool z, vector<vector<WORD>>& colorss ,vector<vector<bool>>& destroyedvec) {
	for (int i = 0; i < sizefield; i++) {
		for (int k = 0; k < sizefield; k++) {
			if (destroyedvec[i][k]){
				*charptrs[i][k] = destroyed;
				colorss[i][k] = hitc;
			}else if (ships_see[i][k] == 1 && ships[i][k] == 0) {
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
	if (x == 65) {
		smallToBig(a);
	}
	for (char k : a) {
		if ((int)k >= x && (int)k <= xy) {

			resultInt = ((int)k - x) + resultInt * 10;
		}
	}
	
	return resultInt;
}
template<typename _T, typename __T>
void Draw::isdestroyed(Draw& drawer, _T& p1, __T& p2){
	for (int i = 0; i < 10; i++){
		if(p1.shipsplacement[i].destroyed == 0) {
			bool checker = 0;
			for (int k = 0; k < p1.shipsplacement[i].length; k++) {
				if (p2.treffer[p1.shipsplacement[i].shipsplaces[k].Y][p1.shipsplacement[i].shipsplaces[k].X]) {
					checker = 1;
				}
				else{
					checker = 0;
				}
			}
			if (checker){
				p1.shipsplacement[i].destroyed = 1;
				for (int j = 0; j < p1.shipsplacement[i].length; j++){
					dest1[p1.shipsplacement[i].shipsplaces[j].Y][p1.shipsplacement[i].shipsplaces[j].X] = 1;
				}
			}
		}
		if(p2.shipsplacement[i].destroyed == 0){
			bool checker = 0;
			for (int k = 0; k < p2.shipsplacement[i].length; k++) {
				if (p1.treffer[p2.shipsplacement[i].shipsplaces[k].Y][p2.shipsplacement[i].shipsplaces[k].X]) {
					checker = 1;
				}
				else {
					checker = 0;
				}
			}
			if (checker) {
				p2.shipsplacement[i].destroyed = 1;
				for (int j = 0; j < p2.shipsplacement[i].length; j++) {
					dest2[p2.shipsplacement[i].shipsplaces[j].Y][p2.shipsplacement[i].shipsplaces[j].X] = 1;
				}
			}
		}
	}
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
	//	cout << "bitte die momentane font size �ndern";
	//	while (screen.dwSize.X < 170) {
	//
	//	}
	//}
	//lastsize = screen.dwSize.X;
}
