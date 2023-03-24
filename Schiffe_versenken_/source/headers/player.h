#pragma once
//#include <iostream>
//#include <vector>
//#include <string>
//#include <vector>
//#include <random>
#include "global.h"
#include "Draw.h"
#include "computer.h"
#include "Player1.h"
class Player : public Player1{
private:
	std::vector<std::vector<bool>> eigeneschiffe = {
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
	int schiffeuebrig = 10;
	//int shiff1left1 = 4;
	//int shiff2left1 = 3;
	//int shiff3left1 = 2;
	//int shiff4left1 = 1;
	std::array<int, 4> shipsleft = {1,2,3,4};
	friend class Draw;
	friend class Compare;


public:
	std::vector<ships> shipsplacement;
	int trefferuebrig = 20;
	std::vector<std::vector<bool>> treffer = {
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
	void placeships(Draw&, HANDLE&);
	//void movemaker(int&, int&, int, Draw&);
	//void hitmanager(int&, int&, int, Draw&);
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