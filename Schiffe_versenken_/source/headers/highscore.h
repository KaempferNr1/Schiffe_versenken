#pragma once
#include "global.h"
#include <ranges>
#include <algorithm>
namespace battleships 
{
	class User 
	{
	private:
	
	public:
		std::string user_name;
		User() {};
		~User() {};
	};
	class Highscore
	{
	public:
		static void higherscore(const int zahl);
		// wenn noch zeit dann mach ich nen timer der zeigt wieviel der  letzte zug gedauert hat
	};
}

