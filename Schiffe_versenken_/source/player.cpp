#include "headers\player.h"
#define valid(v1,x,y) (((v1)[(x)][(y)] == 0) ? 1 : 0)
using namespace std;
void Player::placeships(Draw& drawer) {
	bool is_horizontal = 0;
	string temp = "";
	int wahlS = 0, wahlR = 0, wahl = 0;
	
		system("cls");
		for (int k = 0; k < 10; k++) {
			cout << "soll das schiff horizontal(1) oder vertikal(0) sein?";
			cin >> temp;
			is_horizontal = stoii((temp), 48);
			wahl = getshipsiz(shiff1left1, shiff2left1, shiff3left1, shiff4left1, drawer);

			cout << "wo soll das schiff platziert werden(oberster/linkster Ort vom Schiff)\n zuerst reihe dann spalte und mit enter trennen\n";
			do {
				cout << "W\x84hlen sie die Reihe ";
				drawer.wahlget(wahlR, temp, 2);
				//cout << wahlR;
				cout << "W\x84hlen sie die Spalte ";
				drawer.wahlget(wahlS, temp, 2);
				//cout << wahlS;
			} while (!validplacement(wahlR, wahlS, wahl, is_horizontal,eigeneschiffe ));
			//if (is_horizontal) {
			//	for (int j = 0; j < wahl; j++) {
			//		(i == 0) ? (ships1[wahlR][wahlS+j] = 1) : (ships2[wahlR][wahlS+j] = 1);
			//	}
			//}
			//else {
			//	for (int j = 0; j < wahl; j++) {
			//		(i == 0) ? (ships1[wahlR+j][wahlS] = 1) : (ships2[wahlR+j][wahlS] = 1);
			//	}
			//}
			if (is_horizontal)
			{
				placeem(wahlR, wahlS, wahl, 1, eigeneschiffe);
			}
			else {
				placeem(wahlR, wahlS, 1, wahl,eigeneschiffe);
			}
			//(placeem(wahlR, wahlS, ((is_horizontal) ? wahl : 1), ((is_horizontal) ? 1 : wahl));
		}
	system("cls");
	shipsleftreset(drawer);
}
void Player::placeem(int& x, int& y, int j, int z, std::vector<std::vector<bool>>&ships) {
	for (int o = 0; o < j; o++) {
		for (int k = 0; k < z; k++) {
			ships[x + o][y + k] = 1;
		}
	}
}

bool Player::gameover(Draw&, bool&)
{

	return false;
}


void Player::change(int& s, int x, bool& check, Draw& drawer) {
	s--;
	check = false;
	*drawer.charptrs3[x][0] = (s + 48);
}
int Player::getshipsiz(int& s1, int& s2, int& s3, int& s4, Draw& drawer) {
	string temp;
	int wahl = 0;
	bool check = 1;
	vector<int> s = { 4,3,2,1 };
	do {
		cout << "welches schiff soll platziert werden?\n";

		for (int k = 17; k < 21; k++) {
			cout << s[(k - 17)] << ": ";
			for (int j = 0; j < 8; j++) {
				cout << drawer.mapp3[k][j];
			}
			cout << "\n";
		}
		cin >> temp;
		wahl = stoii((temp), 48);
		switch (wahl) {
		case 1:
			if (s1 != 0) {
				change(s1, 3, check, drawer);
			}
			break;
		case 2:
			//(s2 != 0) ? (change(s2,1,check)) : donthing();
			if (s2 != 0) {
				change(s2, 2, check, drawer);
			}
			break;
		case 3:
			if (s3 != 0) {
				change(s3, 1, check, drawer);
			}
			break;
		case 4:
			if (s4 != 0) {
				change(s4, 0, check, drawer);
			}
			break;
		default:
			break;
		}
	} while (check);
	return wahl;
}
void Player::shipmanager() {
	return;
}
//void Player::movemaker(int& x, int& y, int player1, Draw& drawer) {
//	hitmanager(x, y, player1, drawer);
//	// player1 == 1 wenn spieler 2 drann ist
//	(player1 == 1) ? (drawer.makemap(ships2forP1, ships2, drawer.charptrs, 1)) : (drawer.makemap(ships1forP2, ships1, drawer.charptrs, 1));
//}
//void Player::hitmanager(int& x, int& y, int player1, Draw& drawer) {
//	(player1 == 1) ? (ships1forP2[x][y] = 1, drawer.makemap(ships1forP2, ships1, drawer.charptrs2, 0)) : (ships2forP1[x][y] = 1, drawer.makemap(ships2forP1, ships2, drawer.charptrs2, 0));
//}
//void Player::make_enemy_map(vector<vector<bool>>&ships_see, vector<vector<bool>>&ships, vector<vector<char*>>& charptrs) {
//	for (int i = 0; i < sizefield; i++) {
//		for (int k = 0; k < sizefield; k++) {
//			if (ships_see[i][k] == 0) {
//				charptrs[i][k][0] = unused;
//			}
//			else if (ships_see[i][k] == ships[i][k]) {
//				charptrs[i][k][0] = hit;
//			}
//			else {
//				charptrs[i][k][0] = miss;
//			}
//		}
//	}
//
//}
//void Player::makemap(vector<vector<bool>>& ships_see, vector<vector<bool>>& ships, vector<vector<char*>>& charptrs, bool z) {
//	for (int i = 0; i < sizefield; i++) {
//		for (int k = 0; k < sizefield; k++) {
//			if (ships_see[i][k] == 0 && (ships[i][k] == 0 || !z)) {
//				charptrs[i][k][0] = unused;
//			}
//			else if ((ships_see[i][k] == 0 && ships[i][k] == 1) && z) {
//				charptrs[i][k][0] = ship;
//
//			}
//			else if (ships_see[i][k] == 1 && ships[i][k] == 1) {
//				charptrs[i][k][0] = hit;
//			}
//			else {
//				charptrs[i][k][0] = miss;
//			}
//		}
//	}
//
//}

bool Player::validmove(int& x, int& y){
	if (!((x >= 0 && x <= 9) && (y >= 0 && y <= 9)))
	{
		return false;
	}
	bool returnval = valid(treffer, x, y) ;
	return returnval;
}
bool Player::validplacement(int& x, int& y, int& leng, bool& is_horizontal, vector<vector<bool>>& shipss) {
	bool checker = 1;
	if (is_horizontal) {
		for (int i = 0; (i < leng) && checker; i++) {
			if (!((x + i >= 0 && x + i <= 9) && (y >= 0 && y <= 9))) {
				return false;
			}
			checker = valid(shipss, x + i, y);
		}
	}
	else {
		for (int i = 0; (i < leng) && checker; i++) {
			if (!((x >= 0 && x <= 9) && (y + i >= 0 && y + i <= 9))) {
				return false;
			}
			checker = valid(shipss, x, y + i);
		}
	}
	return checker;
}

void Player::resettonormal(Draw& drawer) {
	shipsleftreset(drawer);
	for (int i = 0; i < sizefield; i++) {
		for (int k = 0; k < sizefield; k++) {
			drawer.charptrs[i][k][0] = unused;
			drawer.charptrs2[i][k][0] = unused;
		}
	}

}
void Player::test(Draw& drawer) {
	cout << *drawer.charptrs3[0][0];
	cout << "\n";
	*drawer.charptrs3[0][0] = shiff1left1 + 48;
	cout << drawer.mapp3[17];
}

void Player::shipsleftreset(Draw& drawer) {
	shiff1left1 = 4; 
	shiff2left1 = 3; 
	shiff3left1 = 2; 
	shiff4left1 = 1; 
	*drawer.charptrs3[3][0] = '4';
	*drawer.charptrs3[2][0] = '3';
	*drawer.charptrs3[1][0] = '2';
	*drawer.charptrs3[0][0] = '1';
	*drawer.charptrs3[3][1] = '4';
	*drawer.charptrs3[2][1] = '3';
	*drawer.charptrs3[1][1] = '2';
	*drawer.charptrs3[0][1] = '1';
					 
}
