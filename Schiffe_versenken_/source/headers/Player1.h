#pragma once
#include "global.h"
#include "probabilityPc.h"
namespace battleships 
{
	class Draw;
	class Computer;
	class Player;

	class ships 
	{
	public:
		int length = 0;
		bool destroyed = 0;
		ships(int, int, int, bool);
	private:
		int x = 0;
		int y = 0;
		bool horizontal = 0;
		int segsleft = 0;
		std::vector<COORD> shipsplaces;
		friend class Draw;
	};


	class Player1 
	{
	public:
		virtual ~Player1(){}
		virtual void make_move(Draw&, Player1&, int&, int&, bool, bool, bool, std::vector<std::vector<bool>>&) = 0;
		virtual void placeships(Draw&, HANDLE&) = 0;

		bool validmove(int&, int&, std::vector<std::vector<bool>>&);
		void resettonormal(Draw&);
		int getshipsiz(int&, int&, int&, int&, Draw&);
		void test(Draw&);
		void shipsleftreset(Draw&);
		int getsmallestshiplen(std::array<int, 4>&, bool);
		static bool validplacement(int&, int&, int, bool, std::vector<std::vector<bool>>&);
		static void change(int&, int, bool&, Draw&);
	public:
		int trefferuebrig = 17;
		int schiffeuebrig = 5;
		std::unique_ptr<probabilityPc> prob = nullptr;
		std::array<int, 4> shipsleft = { 1,2,1,1 };
		std::vector<ships> shipsplacement;
		std::vector<std::vector<bool>> treffer = 
		{ /*wohin habe ich geschossen */
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
	protected:
		void placeem(int&, int&, int, int, std::vector<std::vector<bool>>&);
		std::vector<std::vector<bool>> eigeneschiffe = 
		{
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
		friend class Draw;
		friend class Player;
		friend class Computer;
	};
}