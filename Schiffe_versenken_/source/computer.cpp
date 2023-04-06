#include "headers\computer.h"
#include "headers\player.h"
#define valid(v1,x,y) (((v1)[(x)][(y)] == 0) ? 1 : 0)
void Computer::placeships(Draw& drawer,HANDLE& console) {
	int wahlR = 0;
	int wahlS = 0;
	int wahl[10] = { 2,3,3,4,5 };
	bool is_horizontal = 0;
	std::string waiter;
	
	//shipsplacement.reserve(10);
	for (int i = 0; i < 5; i++) {
		is_horizontal = (rand() % 2 == 0);
		do {
			wahlR = rand() % 10;
			wahlS = rand() % 10;
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
	trefferuebrig = 17;
}
Computer::Computer(Draw& drawer){
	prob = std::make_unique<probabilityPc>(drawer);
}
//void Computer::movemaker(int& x,int& y,int,Draw& drawer) {
//
//}


//std::mt19937_64 randomengine(std::chrono::system_clock::now().time_since_epoch().count());