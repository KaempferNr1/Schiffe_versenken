//for main.cpp hab ich gemacht
/*#else
	while (windowopen) {
		//player.resettonormal(drawer);
		drawer.wahlget(auswahl, auswahl_temp, 1);
		switch (auswahl)
		{
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
		default:
			cout << "okay dann tschau";
			windowopen = false;
			break;
		}
}
	#endif*/
//for draw.h hab hier tatsächlich auch die handles rausgemacht
/*#else

0.11785 , 0.153364 , 0.17493 , 0.182337 , 0.182181 , 0.182511 , 0.182298 , 0.174805 , 0.154849 , 0.118481
0.153658 , 0.185152 , 0.203753 , 0.210299 , 0.210455 , 0.209553 , 0.210727 , 0.204407 , 0.186203 , 0.154467
0.174765 , 0.203806 , 0.221234 , 0.227499 , 0.22668 , 0.226409 , 0.2269 , 0.22038 , 0.203974 , 0.174995
0.182195 , 0.210341 , 0.226976 , 0.233262 , 0.23309 , 0.232921 , 0.233185 , 0.226273 , 0.211355 , 0.18249
0.181811 , 0.209952 , 0.226481 , 0.233426 , 0.232402 , 0.232818 , 0.233591 , 0.226356 , 0.209891 , 0.181342
0.181842 , 0.210246 , 0.226433 , 0.233058 , 0.233209 , 0.23242 , 0.232922 , 0.225547 , 0.209809 , 0.181775
0.182534 , 0.210563 , 0.227345 , 0.233317 , 0.232669 , 0.232982 , 0.233269 , 0.22596 , 0.210107 , 0.182144
0.175035 , 0.204579 , 0.220876 , 0.227779 , 0.227043 , 0.227056 , 0.22677 , 0.219473 , 0.203534 , 0.175097
0.154248 , 0.186106 , 0.203715 , 0.210718 , 0.210022 , 0.210262 , 0.210454 , 0.203945 , 0.186375 , 0.154941
0.118349 , 0.153823 , 0.174813 , 0.182923 , 0.181566 , 0.18201 , 0.182697 , 0.175373 , 0.154645 , 0.118542

11.785% , 15.3364% , 17.493% , 18.2337% , 18.2181% , 18.2511% , 18.2298% , 17.4805% , 15.4849% , 11.8481%
15.3658% , 18.5152% , 20.3753% , 21.0299% , 21.0455% , 20.9553% , 21.0727% , 20.4407% , 18.6203% , 15.4467%
17.4765% , 20.3806% , 22.1234% , 22.7499% , 22.668% , 22.6409% , 22.69% , 22.038% , 20.3974% , 17.4995%
18.2195% , 21.0341% , 22.6976% , 23.3262% , 23.309% , 23.2921% , 23.3185% , 22.6273% , 21.1355% , 18.249%
18.1811% , 20.9952% , 22.6481% , 23.3426% , 23.2402% , 23.2818% , 23.3591% , 22.6356% , 20.9891% , 18.1342%
18.1842% , 21.0246% , 22.6433% , 23.3058% , 23.3209% , 23.242% , 23.2922% , 22.5547% , 20.9809% , 18.1775%
18.2534% , 21.0563% , 22.7345% , 23.3317% , 23.2669% , 23.2982% , 23.3269% , 22.596% , 21.0107% , 18.2144%
17.5035% , 20.4579% , 22.0876% , 22.7779% , 22.7043% , 22.7056% , 22.677% , 21.9473% , 20.3534% , 17.5097%
15.4248% , 18.6106% , 20.3715% , 21.0718% , 21.0022% , 21.0262% , 21.0454% , 20.3945% , 18.6375% , 15.4941%
11.8349% , 15.3823% , 17.4813% , 18.2923% , 18.1566% , 18.201% , 18.2697% , 17.5373% , 15.4645% , 11.8542%

void drawMap(int, std::vector<std::string>&);
void drawPvP(Draw&);
void drawPv(Draw&);
void drawPvC(Draw&);
void drawCvC(Draw&);
void setmap(std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&, std::string&);
void cursPosSet(int, int, COORD&);
template<typename _T, typename __T>
void setmakedrawmap(std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&, std::string&, _T&, __T&, bool, bool, int);
#endif // defined(_WIN32) || defined(_WIN64)*/
// for draw.cpp
/*#else
void Draw::drawMap(vector<string>& map) {
	system("clear");
	int height = map.size();
	for (int y = 0; y < height; y++) {
		cout << map[y];
	}
	initscr();
	start_color();
	//Define color pairs
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	for (int i = 0; i < map.size(); i++) {
		const std::string& line = map[i];
		for (int j = 0; j < line.size(); j++) {
			char c = line[j];
			int color_pair = 0;
			//Set color pair based on character
			if (c == 'X') {
				color_pair = 1; // red
			}
			else if (c == 'O') {
				color_pair = 2; // green
			}
			else if (c == '*') {
				color_pair = 3; // blue
			}
			//Print character with color
			attron(COLOR_PAIR(color_pair));
			mvprintw(i, j, "%c", c);
			attroff(COLOR_PAIR(color_pair));
		}
	}
	refresh();
	endwin();

}


template<typename _T, typename __T>
void Draw::setmakedrawmap( vector<string>& res, vector<string>& m1, vector<string>& m2, vector<string>& m3, string& x, _T& pc1, __T& pc2, bool z, bool u, int x2) {
	makemap(pc1.treffer, pc2.eigeneschiffe, charptrs, z);
	makemap(pc2.treffer, pc1.eigeneschiffe, charptrs2, u);
	setmap(res, m1, m2, m3, x);
	drawMap(x2, res);
}
void Draw::drawPvP(Draw& drawer) {
	game_end = false;
	array<Player, 2> players;
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
	string temp = "Waehlen sie die Reihe: ";
	string temp2 = "Waehlen sie die Spalte: ";
	string temp3 = "Druecken sie enter";
	while (!game_end) {
		cout << "hallo";
		string waiter;
		if (zaehler % 2 == 0) {
			m = 1;
			n = 0;
		}
		else {
			m = 0;
			n = 1;
		}


		setmakedrawmap(mappp, mapp, mapp2, mapp3, nthing, players[m], players[n], true, false, 0);
		do {
			setmakedrawmap(mappp, mapp, mapp2, mapp3, temp, players[m], players[n], true, false, 0);
			wahlget(wahlR, wahl_temp, 0);
			setmakedrawmap(mappp, mapp, mapp2, mapp3, temp2, players[m], players[n], true, false, 0);
			wahlget(wahlS, wahl_temp, 2);
			//cout << wahlS;
		} while (!players[m].validmove(wahlR, wahlS, players[m].treffer));
		//players[m].movemaker(wahlR, wahlS, zaehler % 2, drawer);
		//cper.movemaker(wahlR,wahlS,drawer,players[m],players[n]);
		players[m].treffer[wahlR][wahlS] = 1;
		setmakedrawmap(mappp, mapp, mapp2, mapp3, nthing, players[m], players[n], true, false, 0);
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

}

void Draw::drawPv(HANDLE& console, Draw& drawer) {
	game_end = false;
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
		cursorPos.X = 24; cursorPos.Y = 25;
		makemap(pc.treffer, pc.eigeneschiffe, charptrs, 1);
		setmakedrawmap(console, mappp, mapp, emptyvec, mapp3, temp, pc, pc, 0, 0, 0);
		do {
			//SetConsoleCursorPosition(console, cursorPos);
			//setmap(console, mappp, mapp, emptyvec, mapp3, temp);
			//drawMap(console, 0, mappp);
			setmakedrawmap(console, mappp, mapp, emptyvec, mapp3, temp, pc, pc, 0, 0, 0);
			cursPosSet(console, 24, 25, cursorPos);
			wahlget(wahlR, wahl_temp, 0);
			//setmap(console, mappp, mapp, emptyvec, mapp3, temp2);
			//drawMap(console, 0, mappp);
			setmakedrawmap(console, mappp, mapp, emptyvec, mapp3, temp2, pc, pc, 0, 0, 0);
			cursPosSet(console, 24, 25, cursorPos);
			wahlget(wahlS, wahl_temp, 2);
			cursPosSet(console, 24, 25, cursorPos);
		} while (!pc.validmove(wahlR, wahlS, pc.treffer));
		pc.treffer[wahlR][wahlS] = 1;
		setmakedrawmap(console, mappp, mapp, emptyvec, mapp3, nthing, pc, pc, 0, 0, 0);
		cursPosSet(console, 24, 25, cursorPos);
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
void Draw::setmap(std::vector<std::string>& result, std::vector<std::string>& mp1, std::vector<std::string>& mp2, std::vector<std::string>& mp3, std::string& x) {

	for (size_t i = 0; i < mp1.size(); i++) {
		result[i] = "";
		result[i] = map1 + mp1[i] + mp2[i] + mp3[i];

	}
	result[25] = x;
}
void Draw::drawCvC(Draw& drawer) {
	game_end = false;
	array<Computer, 2> pcs;
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
		setmakedrawmap(mappp, mapp, mapp2, mapp3, nthing, pcs[0], pcs[1], true, true, 0);
		//makemap(pcs[0].treffer, pcs[1].eigeneschiffe, charptrs, 1);
		//makemap(pcs[1].treffer, pcs[0].eigeneschiffe, charptrs2, 1);
		//setmap(console, mappp, mapp, mapp2, mapp3, nthing);
		//drawMap(console, 0, mappp);
		do {
			wahlR = rand() % 10;
			wahlS = rand() % 10;
		} while (!pcs[m].validmove(wahlR, wahlS, pcs[m].treffer));
		//players[m].movemaker(wahlR, wahlS, zaehler % 2, drawer);
		//cper.movemaker(wahlR,wahlS,drawer,players[m],players[n]);
		pcs[m].treffer[wahlR][wahlS] = 1;
		setmakedrawmap(mappp, mapp, mapp2, mapp3, nthing, pcs[0], pcs[1], true, true, 0);
		//makemap(pcs[0].treffer, pcs[1].eigeneschiffe, charptrs, 1);
		//makemap(pcs[1].treffer, pcs[0].eigeneschiffe, charptrs2, 1);
		//setmap(console, mappp, mapp, mapp2, mapp3, nthing);
		//drawMap(console, 0, mappp);
		//cursPosSet(console, 0, 25, cursorPos);
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
	cout << zahl;
	system("pause");
}
#endif // defined(_WIN32) || defined(_WIN64) */
