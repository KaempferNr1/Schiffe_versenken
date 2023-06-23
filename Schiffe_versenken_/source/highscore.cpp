#include "headers\highscore.h"
//void Highscore::higherscore() {
//
//}ge

void battleships::Highscore::higherscore(const int zahl)
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
