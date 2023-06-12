#pragma once
#include "global.h"
#include "Draw.h"
#include "Player1.h"

namespace battleships 
{
	class Player : public Player1 
	{
	private:
		friend class Draw;
	public:
		void make_move(Draw&, Player1&, int&, int&, bool, bool, bool, std::vector<std::vector<bool>>&) override;
		void placeships(Draw&, HANDLE&) override;
		void pc_placeships(Draw&, HANDLE&);
		Player(Draw&);
		Player(Draw&, int);
	};
}