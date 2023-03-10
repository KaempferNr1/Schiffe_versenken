#include "headers\computer.h"
#define valid(v1,x,y) (((v1)[(x)][(y)] == 0) ? 1 : 0)
void Computer::placeships(Draw& drawer) {
	int wahlR = 0;
	int wahlS = 0;
	int wahl[10] = { 1,1,1,1,2,2,2,3,3,4 };
	bool is_horizontal = 0;
	std::string waiter;
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	//std::mt19937_64 randomengine(std::chrono::system_clock::now().time_since_epoch().count());
	for (int i = 0; i < 10; i++) {
		is_horizontal = (rand() % 2 == 0);
		do {
			wahlR = rand() % 10;
			std::cout << wahlR;
			wahlS = rand() % 10;
			std::cout << wahlS;
		} while (!(validplacement(wahlR, wahlS, wahl[i], is_horizontal, eigeneschiffe)));
		if (is_horizontal) {
			placeem(wahlR, wahlS, wahl[i], 1,eigeneschiffe);
		}
		else {
			placeem(wahlR, wahlS, 1, wahl[i],eigeneschiffe);
		}

	}
	std::cout << std::endl;
	for (int k = 0; k < 10; k++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << eigeneschiffe[k][j] << ", ";
		}
		std::cout << std::endl;
	}
	std::cin >> waiter;
}

//void Computer::movemaker(int& x,int& y,int,Draw& drawer) {
//
//}