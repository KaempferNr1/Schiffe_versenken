#pragma once
#include "global.h"
#include "Draw.h"
#include "probabilityPc.h"
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
public:
	std::unique_ptr<probabilityPc> prob = nullptr;
	int schiffeuebrig = 5;
	std::array<int, 4> shipsleft = { 1,2,1,1 };
	std::vector<ships> shipsplacement;
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
	int trefferuebrig = 17;
	void shipmanager();
	bool validmove(int&, int&, std::vector<std::vector<bool>>&);
	static bool validplacement(int&, int&, int&, bool, std::vector<std::vector<bool>>&);
	void resettonormal(Draw&);
	int getshipsiz(int&, int&, int&, int&, Draw&);
	void test(Draw&);
	void shipsleftreset(Draw&);
	void change(int&, int, bool&, Draw&);
	void placeem(int&, int&, int, int, std::vector<std::vector<bool>>&);
	bool gameover(Draw&, bool&);
	int getsmallestshiplen(std::array<int,4>&);
	//void makemap(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&, std::vector<std::vector<char*>>&, bool);
	//void makemove(Draw&, int&, int&, HANDLE& console, _T p1, __T p2, std::string&, std::string&, std::vector<std::string>&);
};