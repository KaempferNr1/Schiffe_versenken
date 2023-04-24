#include "headers/Player1.h"
#define valid(v1,x,y) (((v1)[(x)][(y)] == 0) ? 1 : 0)
// funktionen die sowohl Computer als auch Player brauchen
#include "headers/Draw.h"

void Player1::placeem(int& y, int& x, int j, int z, std::vector<std::vector<bool>>& ships) {
	for (int o = 0; o < j; o++) {
		for (int k = 0; k < z; k++) {
			ships[(long long)y + o][(long long)x + k] = 1;
		}
	}
}

bool Player1::gameover(Draw&, bool&){

	return false;
}

int Player1::getsmallestshiplen(std::array<int, 4>& ships,bool max_true){
	if (max_true){
		for (int i = 3; i >= 0; i--) {
			if (ships[i] != 0) {
				return i + 2;
			}
		}
	}
	else{
		for (int i = 0; i < 4; i++) {
			if (ships[i] != 0) {
				return i + 2;
			}
		}
	}
	return -1;
}


void Player1::change(int& s, int x, bool& check, Draw& drawer) {
	s--;
	check = false;
	*drawer.charptrs3[x][0] = (s + 48);
	
}
int Player1::getshipsiz(int& s1, int& s2, int& s3, int& s4, Draw& drawer) {
	int wahl = 0;
	bool check = 1;
	std::vector<int> s = { 5,4,3,2 };
	do {
		std::string temp;
		std::cout << "welches schiff soll platziert werden?\n";

		for (int k = 17; k < 21; k++) {
			std::cout << s[((long long)k - 17)] << ": ";
			for (int j = 0; j < 10; j++) {
				std::cout << drawer.mapp3[k][j];
			}
			std::cout << "\n";
		}
		std::getline(std::cin, temp);
		wahl = stoii((temp), 48);
		switch (wahl) {
		case 2:
			if (s1 != 0) {
				change(s1, 3, check, drawer);
			}
			break;
		case 3:
			if (s2 != 0) {
				change(s2, 2, check, drawer);
			}
			break;
		case 4:
			if (s3 != 0) {
				change(s3, 1, check, drawer);
			}
			break;
		case 5:
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
void Player1::shipmanager() {
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

bool Player1::validmove(int& x, int& y, std::vector<std::vector<bool>>& ships) {
	if (!((x >= 0 && x <= 9) && (y >= 0 && y <= 9)))
	{
		return false;
	}
	return valid(ships, x, y);
}
bool Player1::validplacement(int& y, int& x, int leng, bool is_horizontal, std::vector<std::vector<bool>>& shipss) {
	bool checker = 1;
	int z = 0;
	int t = 0;
	if (is_horizontal) {
		t = leng;
		z = 1;
	}
	else {
		t = 1;
		z = leng;
	}
	for (int i = 0; i < z && checker; i++) {
		for (int k = 0; k < t && checker; k++) {
			if (!((y + i >= 0 && y + i <= 9) && (x + k >= 0 && x + k <= 9))) {
				return false;
			}
			checker = valid(shipss, y + i, x + k);
		}
	}
	return checker;
}

void Player1::resettonormal(Draw& drawer) {
	shipsleftreset(drawer);
	//for (int i = 0; i < sizefield; i++) {
	//	for (int k = 0; k < sizefield; k++) {
	//		drawer.charptrs[i][k][0] = unused;
	//		drawer.charptrs2[i][k][0] = unused;
	//	}
	//}

}
void Player1::test(Draw& drawer) {
	std::cout << *drawer.charptrs3[0][0];
	std::cout << "\n";
	//*drawer.charptrs3[0][0] = shiff1left1 + 48;
	std::cout << drawer.mapp3[17];
}

void Player1::shipsleftreset(Draw& drawer) {
	*drawer.charptrs3[3][0] = '1';
	*drawer.charptrs3[2][0] = '2';
	*drawer.charptrs3[1][0] = '1';
	*drawer.charptrs3[0][0] = '1';
	*drawer.charptrs3[3][1] = '1';
	*drawer.charptrs3[2][1] = '2';
	*drawer.charptrs3[1][1] = '1';
	*drawer.charptrs3[0][1] = '1';
}

ships::ships(int yval, int xval, int len, bool is_horizontal){
	//shipsplaces.reserve(len);
	x = xval;
	y = yval;
	length = len;
	horizontal = is_horizontal;
	segsleft = len;
	int z = 0;
	int t = 0;
	if (is_horizontal) {
		z = 1;
		t = len;
	}
	else {
		z = len;
		t = 1;
	}

	COORD res = { 0,0 };

	for (int j = 0; j < z; j++) {
		for (int k = 0; k < t; k++) {
			res.Y = yval + j;
			res.X= xval + k;
			shipsplaces.push_back(res);
		}
	}
	

}

//ships::ships(ships& other){
//	this->destroyed		= other.destroyed;
//	this->horizontal	= other.horizontal;
//	this->length		= other.length;
//	this->segsleft		= other.segsleft;
//	this->shipsplaces	= other.shipsplaces;
//	this->x				= other.x;
//	this->y				= other.y;
//}
