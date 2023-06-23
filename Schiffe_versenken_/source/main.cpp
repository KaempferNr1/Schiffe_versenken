#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

#include "headers\global.h"
#include "headers\computer.h"
#include "headers\Draw.h"
#include "headers\player.h"
#include "headers\highscore.h"
#include "headers\Compare.h"

void clearscreen(battleships::Draw&);

// min size damit es funktioniert 170
int main() 
{
	battleships::Draw drawer;
	bool windowopen = true;
	std::string auswahl_temp = "";
	int auswahl = 4;
	srand((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
	while (windowopen) 
	{
		reset(drawer);
		system("pause");
		clearscreen(drawer);
		drawer.wahlget(auswahl, auswahl_temp, 1);
		switch (auswahl)	
		{
		case 1:
			drawer.drawPvP(drawer);
			break;
		case 2:
			drawer.drawPv(drawer);
			break;
		case 3:
			drawer.drawPvC(drawer);
			break;
		case 4:
			drawer.drawCvC(drawer);
			break;
		case 5:
			break;
		case 6:
			drawer.mostlikelysq(drawer);
			break;
		default:
			std::cout << "okay dann tschau";
			windowopen = false;
			break;
		}
	}
	return 0;
}
void clearscreen(battleships::Draw& drawer) 
{
	system("cls");
}
namespace battleships 
{
	void reset(Draw& drawer) 
	{
		drawer.zaehler = 0;
		*drawer.charptrs3[3][0] = '1';
		*drawer.charptrs3[2][0] = '2';
		*drawer.charptrs3[1][0] = '1';
		*drawer.charptrs3[0][0] = '1';
		*drawer.charptrs3[3][1] = '1';
		*drawer.charptrs3[2][1] = '2';
		*drawer.charptrs3[1][1] = '1';
		*drawer.charptrs3[0][1] = '1';
		for (int i = 0; i < global::sizefield; i++) 
		{
			for (int k = 0; k < global::sizefield; k++)
			{
				drawer.charptrs[i][k][0] = global::unused;
				drawer.charptrs2[i][k][0] = global::unused;
				drawer.dest1[i][k] = 0;
				drawer.dest2[i][k] = 0;
			}
		}
	}
}