#include "headers/probabilityPc.h"
#include <queue>
#include "headers/player.h"
#include "headers/computer.h"
using namespace std;
template<typename _T, typename __T>
void probabilityPc::makemove(_T& p1, __T&p2,int&y,int&x) {
    dptr->makemap(p1.eigeneschiffe, p2.treffer, dptr->charptrs, 0, dptr->colors, dptr->dest1);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            map[i][j] = *dptr->charptrs[i][j];
        }
    }
    update_probabilities();
    select_next_guess(y, x);
}

probabilityPc::probabilityPc(Draw& drawer){
    dptr = &drawer;
}
probabilityPc::probabilityPc(){
  
}



probabilityPc::~probabilityPc(){
}
vector<vector<double>> probabilityPc::initialize_grid() {
    array<int, 5> SHIP_SIZES = { 5,4,3,3,2 };
    vector<vector<double>> grid(10, vector<double>(10, 0.0));
    for (int size : SHIP_SIZES) {
        for (int row = 0; row < 10; ++row) {
            for (int col = 0; col < 10; ++col) {
                grid[row][col] = 1;
            }
        }
    }
    return grid;
}
void probabilityPc::update_probabilities(vector<vector<bool>>& hits) {
}

void probabilityPc::select_next_guess(vector<vector<bool>>& x,int& next_row, int& next_col) {
    //for (int row2 = 0; row2 < 10; row2++){
    //    for (int col2 = 0; col2 < 10; col2++){
    //        if (probss[row2][col2] != 0.0){
    //            probss[row2][col2] = 1;
    //        }
    //    }           
    //}
    std::mt19937_64 randomengine(std::chrono::system_clock::now().time_since_epoch().count());
    if (randnumbermax <= 9){
        randnumbermax = 10;
    }
    std::uniform_int_distribution distr(0,randnumbermax-1);
    int rowrand = distr(randomengine);
    int colrand = distr(randomengine);
    if ((colrand <= 9 && colrand >= 0 )&& (rowrand <=9 && colrand >=0)){
        char randcell = map[rowrand][colrand];
        if (randcell == ship) {
            next_row = rowrand;
            next_col = colrand;
            numberofrandhits++;
            return;
        }
    }
    foundhit = false;
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            char cell = map[row][col];
            if (cell == miss) {
                //probss[row][col] = 0.0;
                change_probs(x, col, row, -0.01 , 0);
                //if (row != 9) {
                //    if (!x[(long long)row + 1][(long long)col]) {
                //        probss[(long long)row + 1][(long long)col] -= 0.01;
                //    }
                //}
                //if (col != 9) {
                //    if (!x[(long long)row][(long long)col + 1]) {
                //        probss[(long long)row][(long long)col + 1] -= 0.01;
                //    }
                //}
                //if (row != 0) {
                //    if (!x[(long long)row - 1][(long long)col]) {
                //        probss[(long long)row - 1][(long long)col] -= 0.01;
                //    }
                //}
                //if (col != 0) {
                //    if (!x[(long long)row][(long long)col - 1]) {
                //        probss[(long long)row][(long long)col - 1] -= 0.01;
                //    }
                //}
            }
            else if (cell == ship) {
               //probss[row][col] += 0.000000001;
               //next_row = row;
               //next_col = col;
               //return;
            }
            else if (cell == hit) {
                //probss[row][col] = 0.0;
                change_probs(x, col, row, 2, 1);
                //if (row != 9) {
                //    if (!x[(long long)row + 1][(long long)col]) {
                //        probss[(long long)row + 1][(long long)col] += 3;
                //        foundhit = true;    
                //        //next_row = row+1;
                //        //next_col = col;
                //        //return;
                //    }
                //    if (map[(long long)row + 1][(long long)col] == hit) {
                //        if (row != 0 && !x[(long long)row - 1][(long long)col]) {
                //            probss[(long long)row - 1][(long long)col] += 8;
                //            foundhit = true;
                //        }
                //    }
                //}
                //if (col != 9) {
                //    if (!x[(long long)row][(long long)col + 1]) {
                //        probss[(long long)row][(long long)col + 1] += 3;
                //        foundhit = true;
                //        //next_row = row;
                //        //next_col = col+1;
                //        //return;
                //    }
                //    if (map[(long long)row][(long long)col + 1] == hit) {
                //        if (col != 0 && !x[(long long)row][(long long)col - 1]) {
                //            probss[(long long)row][(long long)col - 1] += 8;
                //            foundhit = true;
                //        }
                //    }
                //}
                //if (row != 0) {
                //    if (!x[(long long)row - 1][(long long)col]) {
                //        probss[(long long)row - 1][(long long)col] += 3;
                //        foundhit = true;
                //        //next_row = row-1;
                //        //next_col = col;
                //        //return;
                //    }
                //    if (map[(long long)row - 1][(long long)col] == hit) {
                //        if (row != 9 && !x[(long long)row + 1][(long long)col]) {
                //            probss[(long long)row + 1][(long long)col] += 8;
                //            foundhit = true;
                //        }
                //    }
                //}
                //if (col != 0) {
                //    if (!x[(long long)row][(long long)col - 1]) {
                //        probss[(long long)row][(long long)col - 1] += 3;
                //        foundhit = true;
                //        //next_row = row;
                //        //next_col = col-1;
                //        //return;
                //    }
                //    if (map[(long long)row][(long long)col - 1] == hit) {
                //        if (col != 9 && !x[(long long)row][(long long)col + 1]) {
                //            probss[(long long)row][(long long)col + 1] += 8;
                //            foundhit = true;
                //        }
                //    }
                //}
            }
            else if (cell == destroyed) {
                //probss[row][col] = 0.0;
                change_probs(x, col, row, -0.001, 0);
                /*if (row != 9) {
                    if (!x[(long long)row + 1][(long long)col]) {
                        probss[(long long)row + 1][(long long)col] -= 0.001;
                    }
                }
                if (col != 9) {
                    if (!x[(long long)row][(long long)col + 1]) {
                        probss[(long long)row][(long long)col + 1] -= 0.001;
                    }
                }
                if (row != 0) {
                    if (!x[(long long)row - 1][(long long)col]) {
                        probss[(long long)row - 1][(long long)col] -= 0.001;
                    }
                }
                if (col != 0) {
                    if (!x[(long long)row][(long long)col - 1]) {
                        probss[(long long)row][(long long)col - 1] -= 0.001;
                    }
                }*/
                //if (row != 9) {
                //    if (!x[(long long)row + 1][(long long)col]) {
                //        probss[(long long)row + 1][(long long)col] ++;
                //        foundhit = true;
                //        //next_row = row+1;
                //        //next_col = col;
                //        //return;
                //    }
                //}
                //if (col != 9) {
                //    if (!x[(long long)row][(long long)col + 1]) {
                //        probss[(long long)row][(long long)col + 1] ++;
                //        foundhit = true;
                //        //next_row = row;
                //        //next_col = col+1;
                //        //return;
                //    }
                //}
                //if (row != 0) {
                //    if (!x[(long long)row - 1][(long long)col]) {
                //        probss[(long long)row - 1][(long long)col] ++;
                //        foundhit = true;
                //        //next_row = row-1;
                //        //next_col = col;
                //        //return;
                //    }
                //}
                //if (col != 0) {
                //    if (!x[(long long)row][(long long)col - 1]) {
                //        probss[(long long)row][(long long)col - 1]++;
                //        foundhit = true;
                //        //next_row = row;
                //        //next_col = col-1;
                //        //return;
                //    }
                //}
            }
        }
    }
    //std::cout << "\n";
    //for (int i = 0; i < 10; i++){
    //   for (int k = 0; k < 9; k++){
    //       std::cout << probss[i][k] << " , ";
    //    } 
    //    std::cout << probss[i][9] << "\n";
    //}
    //system("pause");
    //if(!foundhit){
    //    do{
    //        next_row = rand() % 10;
    //        next_col = rand() % 10;
    //    } while (!((x[next_row][next_col] == 0) ? 1 : 0));
    //    return;
    //}
    double max_prob = -1.0;
    unordered_map<double, pair<int, int>> candidates;
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            if (!x[r][c]) {
                if (probss[r][c] > max_prob) {
                    max_prob = probss[r][c];
                }
                candidates[probss[r][c]]= make_pair(r, c) ;
            }
        }
    }
    if (max_prob <= 1) {
        do {
            next_row = rand() % 10;
            next_col = rand() % 10;
        } while (!((x[next_row][next_col] == 0) ? 1 : 0));
        candidates[2] = make_pair(next_row, next_col);
        max_prob = 2;
    }
    next_row = candidates[max_prob].first;
    next_col = candidates[max_prob].second;

}

void probabilityPc::change_probs(std::vector<std::vector<bool>>& x, int& col, int& row, double change, bool do_thething){
    probss[row][col] = 0.0;
    if (row != 9) {
        if (!x[(long long)row + 1][(long long)col]) {
            probss[(long long)row + 1][(long long)col] += change;
            if (map[row][col] == hit){
                foundhit = true;
            }
        }
        if (map[(long long)row + 1][(long long)col] == hit && do_thething) {
            if (row != 0 && !x[(long long)row - 1][(long long)col]) {
                probss[(long long)row - 1][(long long)col] += 8;
                foundhit = true; 
            }
        }
    }
    if (col != 9) {
        if (!x[(long long)row][(long long)col + 1]) {
            probss[(long long)row][(long long)col + 1] += change;
            if (map[row][col] == hit) {
                foundhit = true;
            }
        }
        if (map[(long long)row][(long long)col + 1] == hit && do_thething) {
            if (col != 0 && !x[(long long)row][(long long)col - 1]) {
                probss[(long long)row][(long long)col - 1] += 8;
                foundhit = true;
            }
        }
    }
    if (row != 0) {
        if (!x[(long long)row - 1][(long long)col]) {
            probss[(long long)row - 1][(long long)col] += change;
            if (map[row][col] == hit) {
                foundhit = true;
            }
        }
        if (map[(long long)row - 1][(long long)col] == hit && do_thething) {
            if (row != 9 && !x[(long long)row + 1][(long long)col]) {
                probss[(long long)row + 1][(long long)col] += 8;
                foundhit = true;
            }
        }
    }
    if (col != 0) {
        if (!x[(long long)row][(long long)col - 1]) {
            probss[(long long)row][(long long)col - 1] += change;
            if (map[row][col] == hit) {
                foundhit = true;
            }
        }
        if (map[(long long)row][(long long)col - 1] == hit && do_thething) {
            if (col != 9 && !x[(long long)row][(long long)col + 1]) {
                probss[(long long)row][(long long)col + 1] += 8;
                foundhit = true;
            }
        }
    }
}
   // Pc1:                                                        Pc2:
   //  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
   //A | o | o | o | o | o | o | o | o | # | o | A               A | o | o | o | o | o | o | o | o | x | o | A
   //B | o | o | o | o | o | o | o | o | # | o | B               B | o | o | o | o | o | o | o | o | x | o | B
   //C | o | o | x | o | o | o | o | o | # | o | C               C | o | o | o | o | o | o | o | o | x | o | C
   //D | o | o | x | x | x | o | o | o | # | o | D               D | o | x | x | x | x | o | o | o | x | o | D
   //E | o | o | x | o | x | x | x | o | # | o | E               E | o | o | o | o | o | o | o | o | x | o | E
   //F | o | o | x | o | o | o | o | o | o | o | F               F | o | o | o | x | o | o | o | o | o | o | F
   //G | o | o | o | o | o | o | o | o | o | o | G               G | o | o | o | x | o | o | o | o | o | o | G
   //H | o | o | o | o | o | o | o | o | o | o | H               H | x | x | x | x | o | o | o | o | o | o | H
   //I | o | o | o | x | x | x | o | o | o | o | I               I | o | o | o | o | o | o | o | o | o | o | I
   //J | o | o | o | o | o | o | o | o | o | o | J               J | o | o | x | x | o | o | o | o | o | o | J
   //  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |


