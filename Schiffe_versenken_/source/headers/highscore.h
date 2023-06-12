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
		static void higherscore(int zahl) 
		{
			int score = 0;
			std::ofstream fout("score.txt");
			std::ifstream fin("score.txt");
			fin >> score;
			int highscore = score;
			if (score < zahl)
			{
				highscore = zahl;
				fout << zahl;
			}
			std::cout << "High score: " << highscore << '\n';
			std::cout << "Your score: " << zahl << '\n';
			fout.close();
			fin.close();
		}
		// wenn noch zeit dann mach ich nen timer der zeigt wieviel der  letzte zug gedauert hat
	};
}

