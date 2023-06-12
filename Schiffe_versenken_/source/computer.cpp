#include "headers\computer.h"
#include "headers\player.h"
#define valid(v1,x,y) (((v1)[(x)][(y)] == 0) ? 1 : 0)
namespace battleships 
{
	void Computer::make_move(battleships::Draw& drawer, Player1& p2, int& wahlR, int& wahlS, bool see_ships_left, bool see_ships_right, bool map2_true, std::vector<std::vector<bool>>& dest_vec) 
	{
		//if (!map2_true) 
		//{
		//	drawer.playermove(*this, p2, wahlR, wahlS, see_ships_left, see_ships_right, map2_true);
		//}
		//else 
		{
			prob->shipsleft = this->shipsleft;
			drawer.makemap(this->treffer, p2.eigeneschiffe, drawer.charptrs, 1, drawer.colors, dest_vec);
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					this->prob->map[i][j] = *drawer.charptrs[i][j];
				}
			}
			this->prob->select_next_guess(treffer, wahlR, wahlS);
		}

	}
	void Computer::placeships(Draw& drawer, HANDLE& console) 
	{
		prob->numberofrandhits = 0;
		shipsplacement.clear();
		prob->probss = std::vector<std::vector<double>>(10, std::vector<double>(10, 1));
		for (unsigned char r = 0; r < treffer.size(); ++r)
		{
			for (unsigned char c = 0; c < treffer.size(); ++c) 
			{
				eigeneschiffe[r][c] = 0;
				treffer[r][c] = 0;
				prob->probss[r][c] = 1;
			}
		}
		
		int wahlR = 0;
		int wahlS = 0;
		std::array<int,5> wahl = { 2,3,3,4,5 };
		bool is_horizontal = 0;
		std::string waiter;
		std::bernoulli_distribution distr1(0.5);
		std::uniform_int_distribution distr2(0,9);
		for (int i = 0; i < 5; i++)
		{
			is_horizontal = distr1(prob->randomengine);
			do 
			{
				wahlR = distr2(prob->randomengine);
				wahlS = distr2(prob->randomengine);
			} while (!(validplacement(wahlR, wahlS, wahl[i], is_horizontal, eigeneschiffe)));
			if (is_horizontal)
			{
				placeem(wahlR, wahlS, 1, wahl[i], eigeneschiffe);
			}
			else 
			{
				placeem(wahlR, wahlS, wahl[i], 1, eigeneschiffe);
			}
			ships ship = { wahlR, wahlS, wahl[i], is_horizontal };
			shipsplacement.push_back(ship);
		}
		trefferuebrig = 17;
	}

	Computer::Computer(Draw& drawer) 
	{
		prob = std::make_unique<probabilityPc>(drawer);
	}

	Computer::Computer(Draw& drawer, int diff) 
	{
		prob = std::make_unique<probabilityPc>(drawer, diff);
	}
}
