#pragma once
#include <iostream>
//#include <vector>
#include <array>
#include <functional>
#include <chrono>
#include <string>
#include <random>
#include <fstream>

#if defined(_WIN32) || defined(_WIN64) 
#include <Windows.h>
#else
#include <ncurses.h>
#endif // defined(_WIN32) || defined(_WIN64) */



constexpr const int sizefield = 10;
constexpr const char hit = '*';
constexpr const char destroyed = 'x'; // only for Pv und CvC jetzt mach ich es doch für jeden modus3
constexpr const char miss = 'o';
constexpr const char unused = '~';
constexpr const char ship = '#';

constexpr const WORD hitc = 4;		//
constexpr const WORD missedc = 6;	//
constexpr const WORD unusedc = 3;	//
constexpr const WORD shipc = 2;		//
constexpr const WORD destroyedc = 245;//

std::wstring s2ws(const std::string&, bool);
int stoii(std::string&, int);
void smallToBig(std::string&);
//constexpr const int height = 24;
//constexpr const int width = 170;
// 4 * 1 block große dinger 
// 3 * 2 block lange dinger
// 2 * 3 block lange dinger
// 1 * 4 block langes ding

