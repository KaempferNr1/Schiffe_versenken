#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <random>
#include "global.h"
#include "Draw.h"
using namespace std;
class Player
{
private:

	vector<vector<bool>> ships1 = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};
	vector<vector<bool>> ships2forp1 = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};
	int numbershipleft1 = 10;
	int numberhitsleft1 = 20;
	int shiff1left1 = 4;
	int shiff2left1 = 3;
	int shiff3left1 = 2;
	int shiff4left1 = 1;

	vector<vector<bool>> ships2 = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};
	vector<vector<bool>> ships1forp2 = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};
	int numbershipleft2 = 10;
	int numberhitsleft2 = 20;
	int shiff1left2 = 4;
	int shiff2left2 = 3;
	int shiff3left2 = 2;
	int shiff4left2 = 1;
	friend class Draw;
public:
	void placeships();
	void shipmanager();
	void movemaker(int&, int&, int);
	void hitmanager(int&, int&, int);
	void makemap(vector<vector<bool>>&, vector<vector<bool>>&, vector<vector<char*>>&, bool);
	bool validmove(int&, int&, int);
	bool validplacement(int&, int&, int&,bool&);
	void resettonormal();
	int getshipsiz(int&, int&, int&, int&);
};

/*
	#include <chrono>
	long long GetCurrentTimeMillis() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
			).count();
	}

	// A sample function to simulate the time spent on deciding a move
	void DoSomething() {
		for (int i = 1; i <= 1000000000; ++i) {
				// do nothing
		}
	}


	Get the start time

	// Do something
	DoSomething();

	// Get the end time
	long long start = GetCurrentTimeMillis();
	long long end = GetCurrentTimeMillis();

	// Calculate the time spent
	long long timeSpent = end - start;

	// Output the time spent
	std::cout << "Time spent: " << timeSpent << " ms\n";

	return 0;
*/