#include "headers\player.h"
#define valid(v1,x,y) (((v1)[(x)][(y)] == 0) ? 1 : 0)
using namespace std;
void Player::placeships(Draw& drawer, HANDLE& console) {
	//bool is_horizontal = 0;
	//string temp = "";
	//int wahlS = 0, wahlR = 0, wahl = 0;
	//COORD cursorPos = { 0,0 };
	////system("cls");
	//for (int k = 0; k < 10; k++) {
	//	cursorPos.X = 0; cursorPos.Y = 0;
	//	SetConsoleCursorPosition(console, cursorPos);
	//	drawer.makemap(treffer, eigeneschiffe, drawer.charptrs, 1 ,drawer.colors);
	//	drawer.setmap( drawer.mappp, drawer.mapp, drawer.mapp3, drawer.emptyvec, drawer.nthing);
	//	drawer.drawMap( 50, drawer.mappp,0);
	//	cout << "soll das schiff horizontal(1) oder vertikal(0) sein?";
	//	cin >> temp;
	//	is_horizontal = stoii((temp), 48);
	//	wahl = getshipsiz(shiff1left1, shiff2left1, shiff3left1, shiff4left1, drawer);

	//	cout << "wo soll das schiff platziert werden\n(oberster/linkster Ort vom Schiff)\n zuerst reihe dann spalte und mit enter trennen\n";
	//	do {
	//		cout << "W\x84hlen sie die Reihe ";
	//		drawer.wahlget(wahlR, temp, 2);
	//		//cout << wahlR;
	//		cout << "W\x84hlen sie die Spalte ";
	//		drawer.wahlget(wahlS, temp, 2);
	//		//cout << wahlS;
	//	} while (!validplacement(wahlR, wahlS, wahl, is_horizontal, eigeneschiffe));
	//	if (is_horizontal)
	//	{
	//		placeem(wahlR, wahlS, 1, wahl, eigeneschiffe);
	//	}
	//	else {
	//		placeem(wahlR, wahlS, wahl, 1, eigeneschiffe);
	//	}
	//}
	// shipsleftreset(drawer);
	int wahlR = 0;
	int wahlS = 0;
	int wahl[10] = { 1,1,1,1,2,2,2,3,3,4 };
	bool is_horizontal = 0;
	std::string waiter;
	//std::mt19937_64 randomengine(std::chrono::system_clock::now().time_since_epoch().count());
	for (int i = 0; i < 11; i++) {
		is_horizontal = (rand() % 2 == 0);
		do {
			wahlR = rand() % 10;
			//std::cout << wahlR;
			wahlS = rand() % 10;
			//std::cout << wahlS;
		} while (!(validplacement(wahlR, wahlS, wahl[i], is_horizontal, eigeneschiffe)));
		if (is_horizontal) {
			placeem(wahlR, wahlS, 1, wahl[i], eigeneschiffe);
		}
		else {
			placeem(wahlR, wahlS, wahl[i], 1, eigeneschiffe);
		}
		ships ship = { wahlR, wahlS, wahl[i], is_horizontal };
		shipsplacement.push_back(ship); 

	}
	trefferuebrig = 20;
}




