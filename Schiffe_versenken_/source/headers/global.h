#pragma once
#include <iostream>
#include <array>
#include <functional>
#include <chrono>
#include <string>
#include <random>
#include <fstream>


#include <Windows.h>

namespace battleships 
{
	namespace global 
	{
		constexpr const int sizefield = 10;
		constexpr const char hit = '*';
		constexpr const char destroyed = 'x'; // nur für Pv und CvC jetzt mach ich es doch für jeden modus3
		constexpr const char miss = 'o';
		constexpr const char unused = '~';
		constexpr const char ship = '#';
		inline int randnumbermax = 15; // muss mindestens auf 10 sein
		constexpr const WORD hitc = 4;		//
		constexpr const WORD missedc = 6;	//
		constexpr const WORD unusedc = 3;	//
		constexpr const WORD shipc = 2;		//
		constexpr const WORD destroyedc = 79;//
	}
	std::wstring s2ws(const std::string&, bool);
	int stoii(std::string&, int);
	void smallToBig(std::string&);
}
//constexpr const int sizefield = 10;
//constexpr const char hit = '*';
//constexpr const char destroyed = 'x'; // nur für Pv und CvC jetzt mach ich es doch für jeden modus3
//constexpr const char miss = 'o';
//constexpr const char unused = '~';
//constexpr const char ship = '#';
//inline int randnumbermax = 15; // muss mindestens auf 10 sein
//constexpr const WORD hitc = 4;		//
//constexpr const WORD missedc = 6;	//
//constexpr const WORD unusedc = 3;	//
//constexpr const WORD shipc = 2;		//
//constexpr const WORD destroyedc = 79 ;//


//constexpr const int height = 24;
//constexpr const int width = 170;

