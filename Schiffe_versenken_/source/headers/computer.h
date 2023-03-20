#pragma once
#include "global.h"
#include "Player1.h"
#include "Draw.h"
class Computer : public Player1 {
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
	int shiff1left = 4;
	int shiff2left = 3;
	int shiff3left = 2;
	int shiff4left = 1;
	friend class Draw;
	friend class Compare;
	//friend class Player;
public:
	std::vector<std::vector<bool>> treffer = { //wohin habe ich geschossen
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
	int trefferuebrig = 20;
	void placeships(Draw&, HANDLE&);
	void doAiStuff(); //sehr guter name für eine funktion ich weiß 
	//void movemaker(int&, int&, int, Draw&);
};