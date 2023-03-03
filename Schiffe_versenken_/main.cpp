#include <iostream>
#include <vector>
#include <string>
//#include <Windows.h>

#include "global.h"
#include "computer.h"
#include "Draw.h"
#include "player.h"

using namespace std;

int main() {
	//char kk = '0';
	//for (int i = 0; i < 14; i++,(int)kk++)
	//{
	//	if (i == 0 || i==13) {
	//		kk = '0';
	//		cout << "{' ',";
	//		cout << "'|',";
	//		for (int j = 1; j < 11; j++, (int)kk++)
	//		{
	//			cout << "' ', ";
	//			cout << "'" << kk << "',";
	//			cout << "' ', ";
	//			cout << "'|',";
	//			
	//		}
	//		//cout << "'|',";
	//		cout << "' '},";
	//		kk = 64;
	//	}
	//	else if (i == 1|| i ==12){
	//		kk = '-';
	//		cout << "{'-',";
	//		cout << "'|',";
	//		for (int j = 2; j < 12; j++)
	//		{
	//			cout << "' ', ";
	//			cout << "'" << kk << "',";
	//			cout << "' ', ";
	//			cout << "'|',";
	//		}
	//		//cout << "'|',";
	//		cout << "'-'},";
	//		kk = 64;
	//	}
	//	else
	//	{
	//		cout << "{'"<< kk <<"',";
	//		cout << "'|',";
	//		for (int j = 1; j < 11; j++)
	//		{
	//			cout << "' ', ";
	//			cout << "'=',";
	//			cout << "' ', ";
	//			cout << "'|',";
	//		}
	//		//cout << "'|',";
	//		cout << "'" << kk << "'},";
	//	}
	//	cout << "\n{'-',";
	//	cout << "'-',";
	//	for (int j = 2; j < 12; j++)
	//	{
	//		cout << "'-',";
	//		cout << "'-',";
	//	}
	//	//cout << "'|',";
	//	cout << "'-'},";
	//	cout << endl;
	//}
	Draw drawer;
	//const int width = 80;
	//const int height = 25;

	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_CURSOR_INFO cursorInfo;
	//GetConsoleCursorInfo(hConsole, &cursorInfo);
	//cursorInfo.bVisible = false;
	//SetConsoleCursorInfo(hConsole, &cursorInfo);

	//vector<vector<char>> screen(height, vector<char>(width, ' '));
	//vector<vector<char>> buffer(height, vector<char>(width, ' '));

	bool windowopen = true;
	string auswahl_temp = "-";
	int auswahl = 0;
	vector<vector<char>> m_arr_p1(sizefield,vector<char>(sizefield+1,0));
	vector<vector<char>> m_arr_p2(sizefield, vector<char>(sizefield + 1, 0));
	drawer.ptr_setterr();
	while (windowopen)
	{

		drawer.wahlget(auswahl, auswahl_temp, 1);
		switch (auswahl)
		{
		case 1:

			drawer.drawPvP(/*console*/);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			cout << "okay dann tschau";
			windowopen = false;
			break;
		}
	}

	return 0;
}
