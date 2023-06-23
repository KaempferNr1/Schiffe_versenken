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
		constexpr  int  sizefield = 10;
		constexpr  char hit = '*';
		constexpr  char destroyed = 'x'; // nur für Pv und CvC jetzt mach ich es doch für jeden modus3
		constexpr  char miss = 'o';
		constexpr  char unused = '~';
		constexpr  char ship = '#';
		inline int		randnumbermax = 15;
		constexpr  WORD hitc = 4;		
		constexpr  WORD missedc = 6;	
		constexpr  WORD unusedc = 3;	
		constexpr  WORD shipc = 2;		
		constexpr  WORD destroyedc = 79;
	}

	//enum class state : char
	//{
	//	hit = '*',
	//	destroyed = 'x',
	//	miss = 'o',
	//	unused = '~',
	//	ship = '#',
	//};
	//enum class state_color : WORD
	//{
	//	hit = 4,
	//	destroyed = 79,
	//	miss = 6,
	//	unused = 3,
	//	ship = 2,
	//};
	//
	//class states
	//{
	//	state status;
	//	state_color status_color;
	//public:
	//	void set_states(state_color sc, state s)
	//	{
	//		
	//	}
	//	void set_color(state_color s)
	//	{
	//		status_color = s;
	//	}
	//	WORD get_color()
	//	{
	//		return static_cast<WORD>(status_color);
	//	}
	//	WORD& get_color_r()
	//	{
	//		return reinterpret_cast<WORD&>(status_color);
	//	}
	//	void set_state(state s)
	//	{
	//		status = s;
	//	}
	//	char get_state()
	//	{
	//		return static_cast<char>(status);
	//	}
	//	char& get_state_r()
	//	{
	//		return reinterpret_cast<char&>(status);
	//	}
	//};
	//class test
	//{
	//public:
	//	static void init()
	//	{
	//		HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//
	//		state_color color = state_color::hit;
	//		states s;
	//		s.set_color(state_color::hit);
	//		s.set_state(state::hit);
	//		// Convert state_color value to WORD
	//		WORD attributeValue = static_cast<WORD>(color);
	//
	//		COORD pos = { 0, 0 };
	//		DWORD bytesWritten;
	//
	//		// Pass the individual WORD value to WriteConsoleOutputAttribute
	//		//WriteConsoleOutputAttribute(hConsoleOutput, &color, 1, pos, &bytesWritten);
	//
	//	}
	//};
	//inline state s = state::hit;
	std::wstring s2ws(const std::string&, bool);
	int stoii(std::string&, int);
	void smallToBig(std::string&);
}



//constexpr const int height = 24;
//constexpr const int width = 170;

