#pragma once
#include "global.h"
#include "Draw.h"

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
public:
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
	//void makemap(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&, std::vector<std::vector<char*>>&, bool);
	//void makemove(Draw&, int&, int&, HANDLE& console, _T p1, __T p2, std::string&, std::string&, std::vector<std::string>&);
};