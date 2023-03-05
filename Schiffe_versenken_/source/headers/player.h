#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <random>
#include "global.h"
#include "Draw.h"

class Player
{
private:
	std::vector<std::vector<bool>> ships1 = {
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
	std::vector<std::vector<bool>> ships2forP1 = {
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

	std::vector<std::vector<bool>> ships2 = {
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
	std::vector<std::vector<bool>> ships1forP2 = {
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
	void placeships(Draw&);
	void shipmanager();
	void movemaker(int&, int&, int, Draw&);
	void hitmanager(int&, int&, int, Draw&);
	void makemap(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&, std::vector<std::vector<char*>>&, bool);
	bool validmove(int&, int&, int);
	bool validplacement(int&, int&, int&, bool&, std::vector<std::vector<bool>>&);
	void resettonormal(Draw&);
	int getshipsiz(int&, int&, int&, int&, int&, Draw&);
	void test(Draw&);
	void shipsleftreset(Draw&);
	void change(int&, int, bool&, Draw&);
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