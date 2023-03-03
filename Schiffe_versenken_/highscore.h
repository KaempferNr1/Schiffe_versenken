#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
class highscore
{
public:
	void higherscore() {
		ofstream fout;
		fout.open("test.txt");
		fout << "Hello File";
		fout.close();
		ifstream fin;
		fin.open("highscore.h");
		if (fin.is_open()) {
			std::string line;
			while (getline(fin, line)) {
				cout << line;
			}
		}
		fin.close();
	}
	// wenn noch zeit dann mach ich nen timer der zeigt wieviel der  letzte zug gedauert hat
};

