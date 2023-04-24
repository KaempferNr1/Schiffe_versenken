#pragma once
#include "global.h"
#include <ranges>
#include <algorithm>
namespace battleships {
	class User {
	private:

	public:
		User() {};
		~User() {};
	};
	class Highscore {
	public:
		void higherscore(int zahl) {
			int score = 0;
			std::ofstream fout("score.txt");
			std::ifstream fin("score.txt");
			fin >> score;
			if (score < zahl) {
				fout << zahl;
				std::cout << "neuer highscore: " << zahl;
			}
			fout.close();
			fin.close();
		}
		// wenn noch zeit dann mach ich nen timer der zeigt wieviel der  letzte zug gedauert hat
	};
}

