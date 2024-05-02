#include "headers\player.h"

namespace battleships 
{
	void Player::make_move(Draw& drawer, Player1& p2, int& wahlR, int& wahlS, bool see_ships_left, bool see_ships_right, bool map2_true, std::vector<std::vector<bool>>& dest_vec) 
	{
		drawer.playermove(*this, p2, wahlR, wahlS, see_ships_left, see_ships_right, map2_true);
	}
	void Player::placeships(Draw& drawer, HANDLE& console)
	{
		int wahlS = 0, wahlR = 0;
		COORD cursorPos = { 0,0 };
		system("cls");
		for (int k = 0; k < 5; k++)
		{
			std::string temp;
			cursorPos.X = 0; cursorPos.Y = 0;
			SetConsoleCursorPosition(drawer.console, cursorPos);
			drawer.makemap(treffer, eigeneschiffe, drawer.charptrs, 1, drawer.colors, drawer.dest1);
			drawer.setmap(drawer.mappp, drawer.mapp, drawer.mapp3, drawer.emptyvec, drawer.nthing);
			drawer.drawMap(50, drawer.mappp, 0);
			std::cout << "soll das schiff horizontal(1) oder vertikal(0) sein?";
			std::getline(std::cin >> std::ws, temp);
			const bool is_horizontal = stoii((temp), 48);
			const int wahl = getshipsiz(shipsleft[0], shipsleft[1], shipsleft[2], shipsleft[3], drawer);
			std::cout << "wo soll das schiff platziert werden\n(oberster/linkster Ort vom Schiff)\n zuerst reihe dann spalte und mit enter trennen\n";
			int zahl = 0;
			do 
			{
				std::string temp2;
				std::string temp3;
				std::cout << "W\x84hlen sie die Reihe ";
				drawer.wahlget(wahlR, temp2, 0);
				std::cout << "W\x84hlen sie die Spalte ";
				drawer.wahlget(wahlS, temp3, 2);
			} while (!validplacement(wahlR, wahlS, wahl, is_horizontal, eigeneschiffe));
			if (is_horizontal)
			{
				placeem(wahlR, wahlS, 1, wahl, eigeneschiffe);
			}
			else 
			{
				placeem(wahlR, wahlS, wahl, 1, eigeneschiffe);
			}
			ships ship = { wahlR, wahlS, wahl, is_horizontal };
			shipsplacement.push_back(ship);
			system("cls");
		}
		shipsleftreset(drawer);
		trefferuebrig = 17;
		system("color F");
	}

	void Player::pc_placeships(Draw&, HANDLE&)
	{
		prob->numberofrandhits = 0;
		shipsplacement.clear();
		prob->probss = std::vector<std::vector<double>>(10, std::vector<double>(10, 1));
		for (unsigned char r = 0; r < treffer.size(); ++r)
		{
			for (unsigned char c = 0; c < treffer.size(); ++c)
			{
				eigeneschiffe[r][c] = false;
				treffer[r][c] = false;
				prob->probss[r][c] = 1;
			}
		}

		int wahlR = 0;
		int wahlS = 0;
		const std::array<int, 5> wahl = { 2,3,3,4,5 };
		std::string waiter;
		std::bernoulli_distribution distr1(0.5);
		std::uniform_int_distribution distr2(0, 9);
		for (int i = 0; i < 5; i++)
		{
			const bool is_horizontal = distr1(prob->randomengine);
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

	Player::Player(Draw& drawer) 
	{
		prob = std::make_unique<probabilityPc>(drawer);
	}

	Player::Player(Draw& drawer, int diff) 
	{
		prob = std::make_unique<probabilityPc>(drawer, diff);
	}
}