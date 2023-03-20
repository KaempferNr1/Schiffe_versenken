#pragma once
//#include <vector>
//#include <iostream>
//#include <string>
//#include <Windows.h>
//#include "computer.h"
#include "Compare.h"
#include "global.h"

class Draw
{
	//std::vector< std::vector < std::vector < std::vector <bool>>>> boole;
	std::vector<std::string> moeglichkeiten = {
	"Player vs Player\n",
	"Single Player(random placement von schiffen mit highscore)\n",
	"Player vs Computer\n",
	"Computer vs Computer\n"
	};
	std::string map1;
	std::vector<std::string> mapp = std::vector<std::string>(24, "");
	std::vector<std::string> mapp2 = std::vector<std::string>(24, "");
	std::vector<std::string> mapp3 = std::vector<std::string>(24, "");
	std::vector<std::string> mappp = std::vector<std::string>(48, "");
	std::vector<std::string> emptyvec = std::vector<std::string>(24, "");
	std::string nthing = "";
	std::string importante = "";
	bool game_end = 0;
	//{22, 3}
	// 1. 16
	// 2. 16
	friend class Computer;
	friend class Player1;
	friend class Player;
	friend class Compare;
	std::string temp = "Waehlen sie die Reihe: ";
	std::string temp2 = "Waehlen sie die Spalte: ";
	std::string temp3 = "Druecken sie enter";
	HANDLE console = nullptr;
public:
	std::vector<std::vector<char*>> charptrs = std::vector<std::vector<char*>>(10, std::vector<char*>(10, nullptr));
	std::vector<std::vector<char*>> charptrs2 = std::vector<std::vector<char*>>(10, std::vector<char*>(10, nullptr));
	std::vector<std::vector<char*>> charptrs3 = std::vector<std::vector<char*>>(4, std::vector<char*>(2, nullptr));
	int zaehler = 0;	// diese Variable 'zaehler' wird genutzt um zu gucken welcher spieler gerade drann ist. Wenn diese gerade ist dann ist Spieler 1 drann wenn sie ungerade ist ist Spieler 2 drann
	std::vector<WORD> colors3 = { unusedc,hitc,shipc,missedc,hitc };
	//std::vector<COORD> coords3 = { { 138 ,3},{138 ,5},{138 ,7},{138 ,9},{138, 11} };
	std::vector<COORD> coords3 = std::vector<COORD>(5, { 0,0 });
	std::vector<std::vector<COORD>> coords = std::vector<std::vector<COORD>>(10, std::vector<COORD>(10, { 0,0 }));
	std::vector<std::vector<COORD>> coords2 = std::vector<std::vector<COORD>>(10, std::vector<COORD>(10, { 0,0 }));
	std::vector<std::vector<WORD>> colors = std::vector<std::vector<WORD>>(10, std::vector<WORD>(10, 7));
	std::vector<std::vector<WORD>> colors2 = std::vector<std::vector<WORD>>(10, std::vector<WORD>(10, 7));
	void drawMap(int, std::vector<std::string>&, bool);
	void drawPvP(Draw&);
	void drawPv(Draw&);
	void drawPvC(Draw&);
	void drawCvC(Draw&);
	void setmap(std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&, std::string&);
	void cursPosSet(int, int);
	template<typename _T, typename __T>
	void setmakedrawmap(std::vector<std::string>&, std::string&, _T&, __T&, bool, bool, int, bool);
	void setansig(std::string&);
	void makemap(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&, std::vector<std::vector<char*>>&, bool, std::vector<std::vector<WORD>>& colors);
	void wahlget(int&, std::string&, int);

	template<typename _T, typename __T>
	void pcmove(Draw&, _T&, __T&, int&, int&);

	template<typename _T, typename __T>
	void playermove(_T&, __T&, int&, int&, bool, bool, bool);

	template<typename _T, typename __T>
	int gameloop(Draw&, _T&, __T&, bool, bool, bool, bool);

	template<typename _T, typename __T>
	int gamecheck(_T&, __T&, int&, int&);

	Draw();
};