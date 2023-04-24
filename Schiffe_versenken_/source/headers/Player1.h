#pragma once
#include "global.h"
#include "probabilityPc.h"
class Draw;
class Computer;
class Player;

class ships {
private:
	int x = 0;
	int y = 0;
	bool horizontal = 0;
	int segsleft = 0;
	std::vector<COORD> shipsplaces;
	friend class Draw;
public:
	int length = 0;
	bool destroyed = 0;
	ships(int,int,int,bool);
};


class Player1 {
protected:
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
	friend class Draw;
	friend class Player;
	friend class Computer;
public:
	std::unique_ptr<probabilityPc> prob = nullptr;
	int schiffeuebrig = 5;
	std::array<int, 4> shipsleft = { 1,2,1,1 };
	std::vector<ships> shipsplacement;
	std::vector<std::vector<bool>> treffer = { /*wohin habe ich geschossen */
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
	virtual void make_move(Draw&, Player1&, int&, int&, bool, bool, bool, std::vector<std::vector<bool>>&) = 0;
	virtual void placeships(Draw&, HANDLE&) = 0;
	int trefferuebrig = 17;
	void shipmanager();
	bool validmove(int&, int&, std::vector<std::vector<bool>>&);
	static bool validplacement(int&, int&, int, bool, std::vector<std::vector<bool>>&);
	void resettonormal(Draw&);
	int getshipsiz(int&, int&, int&, int&, Draw&);
	void test(Draw&);
	void shipsleftreset(Draw&);
	void change(int&, int, bool&, Draw&);
	void placeem(int&, int&, int, int, std::vector<std::vector<bool>>&);
	bool gameover(Draw&, bool&);
	int getsmallestshiplen(std::array<int,4>&, bool);
};