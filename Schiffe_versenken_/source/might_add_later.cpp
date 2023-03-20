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
