#pragma once
#include "global.h"
#include "player.h"
class Computer : public Player{
private:
	std::vector<std::vector<bool>> eigeneschiffe = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};

	int schiffeuebrig = 10;
	int shiff1left = 4;
	int shiff2left = 3;
	int shiff3left = 2;
	int shiff4left = 1;
	friend class Draw;
	friend class Compare;
	//friend class Player;
public:
	std::vector<std::vector<bool>> treffer = { //wohin habe ich geschossen
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	};
	int trefferuebrig = 20;
//#if defined(_WIN32) || defined(_WIN64)
	void placeships(Draw&, HANDLE&);
/*#else
	void placeships(Draw&);
#endif // */

	//void movemaker(int&, int&, int, Draw&);
};
