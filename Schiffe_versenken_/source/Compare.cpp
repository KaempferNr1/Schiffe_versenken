#include "headers/Compare.h"
template<typename Tx, typename Tx_, typename Tx__>
void Compare::movemaker(int& x, int& y, Tx& drawer, Tx_& p1, Tx__& p2) 
{
	p2.treffer[x][y] = 1;
	drawer.makemap(p2.treffer, p1.eigeneschiffe, drawer.charptrs2, 0);
	drawer.makemap(p1.treffer, p2.eigeneschiffe, drawer.charptrs, 1);
	std::array<std::vector<std::array<int, 10>>, 10> errors; //this willl not create errors i promise
}


//void dosomething(std::vector<std::vector<bool>>& eigenships, std::vector<std::vector<bool>>& wohingeschossen, int&x,int&y) {
//	wohingeschossen[x][y] = 1;
//
//}