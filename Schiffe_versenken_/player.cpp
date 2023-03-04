#include "player.h"
#define valid(v1,x,y) (((v1)[(x)][(y)] == 0) ? 1 : 0)
void Player::placeships() {
	Draw drawer;
	bool is_horizontal = 0;
	string temp = "";
	int wahlS = 0, wahlR = 0, wahl = 0;
	for (int i = 0; i < 2; i++) {
		system("cls");
		cout << "Player" << i + 1 << "\n";
		for (int k = 0; k < 10; k++) {
			cout << "soll das schiff horizontal(1) oder vertikal(0) sein?";
			cin >> temp;
			is_horizontal = drawer.stoii((temp), 48);
			wahl = (i == 0) ? getshipsiz(shiff1left1, shiff2left1, shiff3left1, shiff4left1) : getshipsiz(shiff1left2, shiff2left2, shiff3left2, shiff4left2);
			cout << "wo soll das schiff platziert werden(oberster/linkster Ort vom Schiff)\n zuerst reihe dann spalte und mit enter trennen";
			do
			{
				cout << "W\x84hlen sie die Reihe ";
				drawer.wahlget(wahlR, temp, 0);
				cout << wahlR;
				cout << "W\x84hlen sie die Spalte ";
				drawer.wahlget(wahlS, temp, 2);
				cout << wahlS;
			} while (!validplacement(wahlR, wahlS, wahl, is_horizontal));
			if (is_horizontal) {

			}
			else {

			}
		}
	}
}
int Player::getshipsiz(int& s1, int& s2, int& s3, int& s4) {
	Draw drawer;
	string temp;
	int wahl = 0;
	bool check = 1;
	do {
		cout << "welches schiff soll platziert werden?\n";
		cout << drawer.mapp3[17] << "\n";
		cout << drawer.mapp3[18] << "\n";
		cout << drawer.mapp3[19] << "\n";
		cout << drawer.mapp3[20] << "\n";
		cin >> temp;
		wahl = drawer.stoii((temp), 48);
		switch (wahl) {
		case 1:
			if (s1 != 0) {
				s2--;
				check = false;
			}
			break;
		case 2:
			if (s2 != 0) {
				s2--;
				check = false;
			}
			break;
		case 3:
			if (s3 != 0) {
				s3--;
				check = false;
			}
			break;
		case 4:
			if (s4 != 0){
				s4--;
				check = false;
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
void Player::movemaker(int& x, int& y, int player1) {
	Draw drawer;
	hitmanager(x, y, player1);
	if (player1 == 1) {// player 1 == 1 wenn spieler 2 drann ist
		makemap(ships2forp1, ships2, drawer.charptrs, 1);

	}
	else {
		makemap(ships1forp2, ships1, drawer.charptrs, 1);

	}
}
void Player::hitmanager(int& x, int& y, int player1) {
	Draw drawer;
	if (player1 == 1) {
		ships1forp2[x][y] = 1;
		makemap(ships1forp2, ships1, drawer.charptrs2, 0);
	}
	else {
		ships2forp1[x][y] = 1;
		makemap(ships2forp1, ships2, drawer.charptrs2, 0);
	}

}
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
void Player::makemap(vector<vector<bool>>& ships_see, vector<vector<bool>>& ships, vector<vector<char*>>& charptrs, bool z) {
	for (int i = 0; i < sizefield; i++) {
		for (int k = 0; k < sizefield; k++) {
			if (ships_see[i][k] == 0 && ships[i][k] == 0) {
				charptrs[i][k][0] = unused;
			}
			else if ((ships_see[i][k] == 0 && ships[i][k] == 1) && z) {
				charptrs[i][k][0] = ship;
			}
			else if (ships_see[i][k] == 1 && ships[i][k] == 1) {
				charptrs[i][k][0] = hit;
			}
			else {
				charptrs[i][k][0] = miss;
			}
		}
	}


}

bool Player::validmove(int& x, int& y, int player1) {
	if (!((x >= 0 && x <= 9) && (y >= 0 && y <= 9)))
	{
		return false;
	}
	bool returnval = (player1 == 1) ? valid(ships1forp2, x, y) : valid(ships2forp1, x, y);
	return returnval;
}
bool Player::validplacement(int& x, int& y, int& leng, bool& is_horizontal) {

	return true;
}

void Player::resettonormal() {
	Draw drawer;
	numbershipleft1 = 10;
	numberhitsleft1 = 20;
	shiff1left1 = 4; drawer.charptrs3[0][0][0] = shiff1left1;
	shiff2left1 = 3; drawer.charptrs3[1][0][0] = shiff2left1;
	shiff3left1 = 2; drawer.charptrs3[2][0][0] = shiff3left1;
	shiff4left1 = 1; drawer.charptrs3[3][0][0] = shiff4left1;
	numbershipleft2 = 10;
	numberhitsleft2 = 20;
	shiff1left2 = 4; drawer.charptrs3[0][0][0] = shiff1left2;
	shiff2left2 = 3; drawer.charptrs3[1][1][0] = shiff2left2;
	shiff3left2 = 2; drawer.charptrs3[2][1][0] = shiff3left2;
	shiff4left2 = 1; drawer.charptrs3[3][1][0] = shiff4left2;
	for (int i = 0; i < sizefield; i++) {
		for (int k = 0; k < sizefield; k++) {
			drawer.charptrs[i][k][0] = unused;
			drawer.charptrs2[i][k][0] = unused;
			ships1[i][k] = 0;
			ships1forp2[i][k] = 0;
			ships2[i][k] = 0;
			ships2forp1[i][k] = 0;

		}
	}

}
