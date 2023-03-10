#pragma once
#include <iostream>
//#include <vector>
#include <array>
#include <functional>
#include <chrono>
#include <string>
#include <random>
#include <fstream>
#include <Windows.h>

//#include "global.h"
//#include "computer.h"
//#include "Draw.h"
//#include "player.h"
//#include "highscore.h"
//#include "Compare.h"
//std::vector<bool> int64 = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


constexpr const int sizefield = 10;
constexpr const char hit = '*';
constexpr const char destroyed = 'x'; // only for Pv und CvC
constexpr const char miss = 'o';
constexpr const char unused = '~';
constexpr const char ship = '#';

std::wstring s2ws(const std::string&, bool);
int stoii(std::string&, int);

//constexpr const int ROWS = 20;
//constexpr const int COLS = 40;
//constexpr const int height = 50;
//constexpr const int width = 100;
// 4 * 1 block groﬂe dinger 
// 3 * 2 block lange dinger
// 2 * 3 block lange dinger
// 1 * 4 block langes ding
//struct Map {
//	static std::vector<std::string> mapp;
//	static std::string map1;
//	static std::vector<std::string> mapp2;
//	static std::vector<std::string> mapp3;
//
//	static std::vector<std::string> mappp;
//	static char* playptr1;
//	static char* playptr2;
//	static std::vector<std::vector<char*>> charptrs;
//	static std::vector<std::vector<char*>> charptrs2;
//	static std::vector<std::vector<char*>> charptrs3;
//	static std::string nthing;
//	//static std::string importante = "";
//	static void mapsetter();
//} map