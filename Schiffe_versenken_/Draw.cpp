#include "Draw.h"
using namespace std;
void Draw::ptr_setterr(){
    for (int i = 0; i < mapp.size(); i++)
    {
        for (int k = 0; k < mapp[i].size(); k++) {
            if (mapp[i][k] == '~')
            {
                charptrs[i].push_back(&mapp[i][k]);
            }
        }
    }
}
int Draw::stoii(string& a) {
    int supi = 0;
    for (char k : a) {
        if ((int)k >= 48 && (int)k <= 57) {

            supi = ((int)k - 48) + supi * 10;
        }
    }
    return supi;
} 
void Draw::wahlget(int& auswahl, string& as,int x) {
    //system("cls");
    if (x == 1) {
        for (int i = 0; i < moeglichkeiten.size(); i++)
        {
            cout <<"\t" << i + 1 << "\t" << moeglichkeiten[i];
        }
    }
    getline(cin, as);
    auswahl = stoii(as);
}
void Draw::drawPvP(/*HANDLE& console*/) {
    while (!game_end) {
        /* 
        COORD cursorPosition = { 0, 0 };
        DWORD charsWritten;
        FillConsoleOutputCharacter(console, ' ', ROWS * COLS, cursorPosition, &charsWritten);
        FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY, ROWS * COLS, cursorPosition, &charsWritten);
        */
        system("cls");
        for (int i = 0; i < mapp.size(); i++){
            cout << "\t";
            cout << mapp[i];
            cout << "\t\t";
            cout << mapp2[i];
            cout << "\n";
        }
        //for (int i = 0; i < ROWS; i++) {
        //        COORD cursorPosition = { 0, static_cast<SHORT>(i) };
        //        DWORD charsWritten;
        //        WriteConsoleOutputCharacter(console, board[i].c_str(), board[i].size(), cursorPosition, &charsWritten);
        //}

        //// Display the score
        //COORD scorePosition = { static_cast<SHORT>(COLS / 2), 0 };
        //SetConsoleCursorPosition(console, scorePosition);
        //std::cout << "Score: " << score;

        //// Sleep to control the frame rate
        //Sleep(50);
    }

}
