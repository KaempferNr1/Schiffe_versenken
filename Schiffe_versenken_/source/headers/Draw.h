#pragma once
#include "global.h"

namespace battleships 
{
	class Player1;

	class Draw
	{

		//friend int main();
	public:
		Draw();


		void drawMap(int, std::vector<std::string>&, bool);
		void drawPvP(Draw&);
		void drawPv(Draw&);
		void drawPvC(Draw&);
		void drawCvC(Draw&);
		void setmap(std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&, std::vector<std::string>&, std::string&);
		void cursPosSet(int, int);
		void setmakedrawmap(std::vector<std::string>&, std::string&, Player1&, Player1&, bool, bool, int, bool);
		void wahlget(int&, std::string&, int);
		void makemap(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&, std::vector<std::vector<char*>>&, bool, std::vector<std::vector<WORD>>& colors, std::vector<std::vector<bool>>&);
		void mostlikelysq(Draw&);
		void isdestroyed(Draw&, Player1&, Player1&, std::vector<std::vector<bool>>&);
		void playermove(Player1&, Player1&, int&, int&, bool, bool, bool);
		int gameloop(Draw&, Player1&, Player1&, bool, bool, bool, bool, bool);
		int gamecheck(Player1&, Player1&, int&, int&);

	public:
		int zaehler = 0;	// diese Variable 'zaehler' wird genutzt um zu gucken welcher spieler gerade drann ist. Wenn diese gerade ist dann ist Spieler 1 drann wenn sie ungerade ist ist Spieler 2 drann
		int currentsize = 0;
		int lastsize = 0;
		HANDLE console = nullptr; // ein HANDLE ist ein void pointer der in der Win api durch typedef definiert wurde also so: typedef void* HANDLE;
		std::vector<std::vector<bool>> dest1 = std::vector<std::vector<bool>>(10, std::vector<bool>(10, 0));
		std::vector<std::vector<bool>> dest2 = std::vector<std::vector<bool>>(10, std::vector<bool>(10, 0));
		std::vector<std::vector<char*>> charptrs = std::vector<std::vector<char*>>(10, std::vector<char*>(10, nullptr));
		std::vector<std::vector<char*>> charptrs2 = std::vector<std::vector<char*>>(10, std::vector<char*>(10, nullptr));
		std::vector<std::vector<char*>> charptrs3 = std::vector<std::vector<char*>>(4, std::vector<char*>(2, nullptr));
		std::vector<std::vector<COORD>> coords = std::vector<std::vector<COORD>>(10, std::vector<COORD>(10, { 0,0 }));
		std::vector<std::vector<COORD>> coords2 = std::vector<std::vector<COORD>>(10, std::vector<COORD>(10, { 0,0 }));
		std::vector<std::vector<WORD>> colors = std::vector<std::vector<WORD>>(10, std::vector<WORD>(10, 7));
		std::vector<std::vector<WORD>> colors2 = std::vector<std::vector<WORD>>(10, std::vector<WORD>(10, 7));
		std::vector<WORD> colors3 = { global::unusedc,global::hitc,global::shipc,global::missedc,global::destroyedc };
		std::vector<COORD> coords3 = std::vector<COORD>(5, { 0,0 });


	private:
		std::vector<std::string> moeglichkeiten =
		{
			"Player vs Player\n",
			"Single Player(random placement von schiffen mit highscore)\n",
			"Player vs Computer\n",
			"Computer vs Computer\n",
		};
		std::string temp = "Waehlen sie die Reihe: ";
		std::string temp2 = "Waehlen sie die Spalte: ";
		std::string temp3 = "Druecken sie enter";

		std::string map1;
		std::vector<std::string> mapp = std::vector<std::string>(24, "");
		std::vector<std::string> mapp2 = std::vector<std::string>(24, "");
		std::vector<std::string> mapp3 = std::vector<std::string>(24, "");
		std::vector<std::string> mappp = std::vector<std::string>(48, "");
		std::vector<std::string> emptyvec = std::vector<std::string>(24, "");
		std::string nthing;
		bool game_end = 0;

		//{22, 3}
		// 1. 16
		// 2. 16
	private:
		friend class Computer;
		friend class Player1;
		friend class Player;
		friend class Compare;
	};

	void reset(Draw&);
}
