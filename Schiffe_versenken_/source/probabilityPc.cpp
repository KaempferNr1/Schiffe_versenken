#include "headers/probabilityPc.h"
#include <queue>
#include "headers/player.h"
#include "headers/computer.h"
#include "headers/Draw.h"
//template<typename _T, typename __T>
//void probabilityPc::makemove(_T& p1, __T& p2, int& y, int& x) {
//	dptr->makemap(p1.eigeneschiffe, p2.treffer, dptr->charptrs, 0, dptr->colors, dptr->dest1);
//	for (int i = 0; i < 10; i++) {
//		for (int j = 0; j < 10; j++) {
//			map[i][j] = *dptr->charptrs[i][j];
//		}
//	}
//	update_probabilities();
//	select_next_guess(,y, x);
//}

probabilityPc::probabilityPc(Draw& drawer) {
	randomengine = std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count());
	dptr = &drawer;
	this->fptr = &probabilityPc::hard_version;
}
probabilityPc::probabilityPc(Draw& drawer, int x) {
	randomengine = std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count());
	dptr = &drawer;
	switch (x) {
	case 1:
		this->fptr = &probabilityPc::easy_version;
		break;
	case 2:
		this->fptr = &probabilityPc::medium_version;
		break;
	case 3:
		this->fptr = &probabilityPc::hard_version;
		break;
	case 4:
		this->fptr = &probabilityPc::impossible_version;
		break;
	default:
		this->fptr = &probabilityPc::hard_version;
		break;
	}
}
probabilityPc::probabilityPc() {
	randomengine = std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count());
	this->fptr = &probabilityPc::hard_version;
}

probabilityPc::~probabilityPc() {
}

void weir() {
	probabilityPc p;
}

std::vector<std::vector<double>> probabilityPc::initialize_grid() {
	std::vector<std::vector<double>> grid(10, std::vector<double>(10, 1));
	return grid;
}
void probabilityPc::update_probabilities(std::vector<std::vector<bool>>& hits) {
}

void probabilityPc::select_next_guess(std::vector<std::vector<bool>>& x, int& next_row, int& next_col) {
	(this->*fptr)(x, next_row, next_col);
	
}

void probabilityPc::easy_version(std::vector<std::vector<bool>>& x, int& next_row, int& next_col) {
	foundhit = false;
	for (int row = 0; row < 10; ++row) {
		for (int col = 0; col < 10; ++col) {
			char cell = map[row][col];
			if (cell == hit) {
				change_probs(x, col, row, 3, 0);
				foundhit = true;
			}
			else if (cell == destroyed) {
				change_probs(x, col, row, 3, 0);
			}
		}
	}
	if (get_probs) {
		std::cout << "\n";
		for (int i = 0; i < 10; i++) {
			for (int k = 0; k < 9; k++) {
				std::cout << probss[i][k] << " , ";
			}
			std::cout << probss[i][9] << "\n";
		}
		std::cin.get();
	}
	if (!foundhit) {
		do {
			next_row = rand() % 10;
			next_col = rand() % 10;
		} while (!((x[next_row][next_col] == 0) ? 1 : 0));
		return;
	}
	double max_prob = -1.0;
	std::unordered_map<double, std::pair<int, int>> candidates;
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (!x[r][c]) {
				if (probss[r][c] > max_prob) {
					max_prob = probss[r][c];
				}
				candidates[probss[r][c]] = std::make_pair(r, c);
			}
		}
	}
	next_row = candidates[max_prob].first;
	next_col = candidates[max_prob].second;
}

void probabilityPc::medium_version(std::vector<std::vector<bool>>& x, int& next_row, int& next_col) {
	for (int row2 = 0; row2 < 10; row2++) {
		for (int col2 = 0; col2 < 10; col2++) {
			if (!x[row2][col2] && probss[row2][col2] != 0) {
				probss[row2][col2] = 1;
			}
		}
	}
	bool early_return = 0;
	std::uniform_int_distribution distr(0, randnumbermax - 1);
	int rowrand = distr(randomengine);
	int colrand = distr(randomengine);
	if ((colrand <= 9 && colrand >= 0) && (rowrand <= 9 && colrand >= 0)) {
		char randcell = map[rowrand][colrand];
		if (randcell == ship) {
			next_row = rowrand;
			next_col = colrand;
			numberofrandhits++;
			early_return = 1;
		}
	}
	foundhit = false;
	for (int row = 0; row < 10; ++row) {
		for (int col = 0; col < 10; ++col) {
			char cell = map[row][col];
			if (cell == miss) {
				change_probs(x, col, row, -0.01, 0);
			}
			else if (cell == ship) {
			}
			else if (cell == hit) {
				change_probs(x, col, row, 3, 1);
				foundhit = true;
			}
			else if (cell == destroyed) {
				change_probs(x, col, row, -0.001, 0);
			}
		}
	}
	if (get_probs) {
		std::cout << "\n";
		for (int i = 0; i < 10; i++) {
			for (int k = 0; k < 9; k++) {
				std::cout << probss[i][k] << " , ";
			}
			std::cout << probss[i][9] << "\n";
		}
		std::cin.get();
	}
	if (early_return) {
		return;
	}
	double max_prob = -1.0;
	std::unordered_map<double, std::pair<int, int>> candidates;
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (!x[r][c]) {
				if (probss[r][c] > max_prob) {
					max_prob = probss[r][c];
				}
				candidates[probss[r][c]] = std::make_pair(r, c);
			}
		}
	}
	next_row = candidates[max_prob].first;
	next_col = candidates[max_prob].second;
	if (!foundhit) {
		if (zaehler == 2) {
			double max_prob2 = -1.0;
			std::unordered_map<double, std::pair<int, int>> candidates2;
			for (int r = 9; r >= 0; r--) {
				for (int c = 9; c >= 0; c--) {
					if (!x[r][c]) {
						if (probss[r][c] > max_prob2) {
							max_prob2 = probss[r][c];
						}
						candidates2[probss[r][c]] = std::make_pair(r, c);
					}
				}
			}
			next_row = candidates2[max_prob2].first;
			next_col = candidates2[max_prob2].second;
		}
		else if (zaehler == 3) {
			double max_prob2 = -1.0;
			std::unordered_map<double, std::pair<int, int>> candidates2;
			for (int r = 0; r < 5; r++) {
				for (int c = 0; c < 5; c++) {
					if (!x[r][c]) {
						if (probss[r][c] > max_prob2) {
							max_prob2 = probss[r][c];
						}
						candidates2[probss[r][c]] = std::make_pair(r, c);
					}
				}
			}
			for (int r = 9; r > 4; r--) {
				for (int c = 9; c > 4; c--) {
					if (!x[r][c]) {
						if (probss[r][c] > max_prob2) {
							max_prob2 = probss[r][c];
						}
						candidates2[probss[r][c]] = std::make_pair(r, c);
					}
				}
			}
			next_row = candidates2[max_prob2].first;
			next_col = candidates2[max_prob2].second;
		}
	}
	zaehler++;
	if (zaehler > 3) {
		zaehler = 1;
	}
}

void probabilityPc::hard_version(std::vector<std::vector<bool>>& x, int& next_row, int& next_col) {
	for (int row2 = 0; row2 < 10; row2++) {
		for (int col2 = 0; col2 < 10; col2++) {
			if (!x[row2][col2] && probss[row2][col2] != 0) {
				probss[row2][col2] = 1;
			}
		}
	}
	bool early_return = 0;
	std::uniform_int_distribution distr(0, randnumbermax - 1);
	int rowrand = distr(randomengine);
	int colrand = distr(randomengine);
	if ((colrand <= 9 && colrand >= 0) && (rowrand <= 9 && colrand >= 0)) {
		char randcell = map[rowrand][colrand];
		if (randcell == ship) {
			next_row = rowrand;
			next_col = colrand;
			numberofrandhits++;
			early_return = 1;
		}
	}
	foundhit = false;
	for (int row = 0; row < 10; ++row) {
		for (int col = 0; col < 10; ++col) {
			char cell = map[row][col];
			if (cell == miss) {
				change_probs(x, col, row, -0.01, 0);
			}
			else if (cell == ship) {
			}
			else if (cell == hit) {
				change_probs(x, col, row, 3, 1);
				foundhit = true;
			}
			else if (cell == destroyed) {
				change_probs(x, col, row, -0.001, 0);
			}
		}
	}
	if (get_probs) {
		std::cout << "\n";
		for (int i = 0; i < 10; i++) {
			for (int k = 0; k < 9; k++) {
				std::cout << probss[i][k] << " , ";
			}
			std::cout << probss[i][9] << "\n";
		}
		std::cin.get();
	}
	double max_prob = -1.0;
	std::unordered_map<double, std::pair<int, int>> candidates;
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (!x[r][c]) {
				if (probss[r][c] > max_prob) {
					max_prob = probss[r][c];
				}
				candidates[probss[r][c]] = std::make_pair(r, c);
			}
		}
	}
	if (early_return) {
		return;
	}
	next_row = candidates[max_prob].first;
	next_col = candidates[max_prob].second;
	if (!foundhit) {
		if (zaehler == 2) {
			double max_prob2 = -1.0;
			std::unordered_map<double, std::pair<int, int>> candidates2;
			for (int r = 9; r >= 0; r--) {
				for (int c = 9; c >= 0; c--) {
					if (!x[r][c]) {
						if (probss[r][c] > max_prob2) {
							max_prob2 = probss[r][c];
						}
						candidates2[probss[r][c]] = std::make_pair(r, c);
					}
				}
			}
			next_row = candidates2[max_prob2].first;
			next_col = candidates2[max_prob2].second;
		}
		else if (zaehler == 3) {
			double max_prob2 = -1.0;
			std::unordered_map<double, std::pair<int, int>> candidates2;
			for (int r = 0; r < 5; r++) {
				for (int c = 0; c < 5; c++) {
					if (!x[r][c]) {
						if (probss[r][c] > max_prob2) {
							max_prob2 = probss[r][c];
						}
						candidates2[probss[r][c]] = std::make_pair(r, c);
					}
				}
			}
			for (int r = 9; r > 4; r--) {
				for (int c = 0; c < 5; c++) {
					if (!x[r][c]) {
						if (probss[r][c] > max_prob2) {
							max_prob2 = probss[r][c];
						}
						candidates2[probss[r][c]] = std::make_pair(r, c);
					}
				}
			}
			for (int r = 0; r < 5; r++) {
				for (int c = 9; c > 4; c--) {
					if (!x[r][c]) {
						if (probss[r][c] > max_prob2) {
							max_prob2 = probss[r][c];
						}
						candidates2[probss[r][c]] = std::make_pair(r, c);
					}
				}
			}
			for (int r = 9; r > 4; r--) {
				for (int c = 9; c > 4; c--) {
					if (!x[r][c]) {
						if (probss[r][c] > max_prob2) {
							max_prob2 = probss[r][c];
						}
						candidates2[probss[r][c]] = std::make_pair(r, c);
					}
				}
			}
			next_row = candidates2[max_prob2].first;
			next_col = candidates2[max_prob2].second;
		}
	}
	zaehler++;
	if (zaehler > 3) {
		zaehler = 1;
	}
}

void probabilityPc::impossible_version(std::vector<std::vector<bool>>& x, int& next_row, int&next_col){
	std::bernoulli_distribution event(0.5);
	if (event(randomengine)){
		for (int row = 0; row < 10; ++row) {
			for (int col = 0; col < 10; ++col) {
				char cell = map[row][col];
				if (cell == ship) {
					next_row = row;
					next_col = col;
					return;
				}
			}
		}
	}
	else{
		hard_version(x, next_row, next_col);
	}
}





void probabilityPc::change_probs(std::vector<std::vector<bool>>& x, int& col, int& row, double change, bool do_thething) {
	probss[row][col] = 0.0;
	if (row != 9) {
		if (!x[(long long)row + 1][(long long)col]) {
			probss[(long long)row + 1][(long long)col] += change;
		}
		if (map[(long long)row + 1][(long long)col] == hit && do_thething) {
			if (row != 0 && !x[(long long)row - 1][(long long)col]) {
				probss[(long long)row - 1][(long long)col] += 8;
			}
		}
	}
	if (col != 9) {
		if (!x[(long long)row][(long long)col + 1]) {
			probss[(long long)row][(long long)col + 1] += change;
		}
		if (map[(long long)row][(long long)col + 1] == hit && do_thething) {
			if (col != 0 && !x[(long long)row][(long long)col - 1]) {
				probss[(long long)row][(long long)col - 1] += 8;
			}
		}
	}
	if (row != 0) {
		if (!x[(long long)row - 1][(long long)col]) {
			probss[(long long)row - 1][(long long)col] += change;
		}
		if (map[(long long)row - 1][(long long)col] == hit && do_thething) {
			if (row != 9 && !x[(long long)row + 1][(long long)col]) {
				probss[(long long)row + 1][(long long)col] += 8;
			}
		}
	}
	if (col != 0) {
		if (!x[(long long)row][(long long)col - 1]) {
			probss[(long long)row][(long long)col - 1] += change;
		}
		if (map[(long long)row][(long long)col - 1] == hit && do_thething) {
			if (col != 9 && !x[(long long)row][(long long)col + 1]) {
				probss[(long long)row][(long long)col + 1] += 8;
			}
		}
	}
}
// Pc1:                                                        Pc2:
//  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
//---------------------------------------------               ---------------------------------------------
//A | o | o | o | o | o | o | o | o | # | o | A               A | o | o | o | o | o | o | o | o | x | o | A
//---------------------------------------------               ---------------------------------------------
//B | o | o | o | o | o | o | o | o | # | o | B               B | o | o | o | o | o | o | o | o | x | o | B
//---------------------------------------------               ---------------------------------------------
//C | o | o | x | o | o | o | o | o | # | o | C               C | o | o | o | o | o | o | o | o | x | o | C
//---------------------------------------------               ---------------------------------------------
//D | o | o | x | x | x | o | o | o | # | o | D               D | o | x | x | x | x | o | o | o | x | o | D
//---------------------------------------------               ---------------------------------------------
//E | o | o | x | o | x | x | x | o | # | o | E               E | o | o | o | o | o | o | o | o | x | o | E
//---------------------------------------------               ---------------------------------------------
//F | o | o | x | o | o | o | o | o | o | o | F               F | o | o | o | x | o | o | o | o | o | o | F
//---------------------------------------------               ---------------------------------------------
//G | o | o | o | o | o | o | o | o | o | o | G               G | o | o | o | x | o | o | o | o | o | o | G
//---------------------------------------------               ---------------------------------------------
//H | o | o | o | o | o | o | o | o | o | o | H               H | x | x | x | x | o | o | o | o | o | o | H
//---------------------------------------------               ---------------------------------------------
//I | o | o | o | x | x | x | o | o | o | o | I               I | o | o | o | o | o | o | o | o | o | o | I
//---------------------------------------------               ---------------------------------------------
//J | o | o | o | o | o | o | o | o | o | o | J               J | o | o | x | x | o | o | o | o | o | o | J
//---------------------------------------------               ---------------------------------------------
//  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |                   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |


//for (int row2 = 0; row2 < 10; row2++) {
	//	for (int col2 = 0; col2 < 10; col2++) {
	//		if (!x[row2][col2] && probss[row2][col2] != 0) {
	//			probss[row2][col2] = 1;
	//		}
	//	}
	//}
	//std::mt19937_64 randomengine(std::chrono::system_clock::now().time_since_epoch().count());
	//std::uniform_int_distribution distr(0, randnumbermax - 1);
	//int rowrand = distr(randomengine);
	//int colrand = distr(randomengine);
	//if ((colrand <= 9 && colrand >= 0) && (rowrand <= 9 && colrand >= 0)) {
	//	char randcell = map[rowrand][colrand];
	//	if (randcell == ship) {
	//		next_row = rowrand;
	//		next_col = colrand;
	//		numberofrandhits++;
	//		return;
	//	}
	//}
	//foundhit = false;
	//for (int row = 0; row < 10; ++row) {
	//	for (int col = 0; col < 10; ++col) {
	//		char cell = map[row][col];
	//		if (cell == miss) {
	//			//probss[row][col] = 0.0;
	//			change_probs(x, col, row, -0.01, 0);
	//		}
	//		else if (cell == ship) {
	//		}
	//		else if (cell == hit) {
	//			//probss[row][col] = 0.0;
	//			change_probs(x, col, row, 3, 1);
	//			foundhit = true;
	//		}
	//		else if (cell == destroyed) {
	//			//probss[row][col] = 0.0;
	//			change_probs(x, col, row, -0.001, 0);
	//			//if (row != 9) {
	//			//    if (!x[(long long)row + 1][(long long)col]) {
	//			//        probss[(long long)row + 1][(long long)col] -= 0.001;
	//			//    }
	//			//}
	//			//if (col != 9) {
	//			//    if (!x[(long long)row][(long long)col + 1]) {
	//			//        probss[(long long)row][(long long)col + 1] -= 0.001;
	//			//    }
	//			//}
	//			//if (row != 0) {
	//			//    if (!x[(long long)row - 1][(long long)col]) {
	//			//        probss[(long long)row - 1][(long long)col] -= 0.001;
	//			//    }
	//			//}
	//			//if (col != 0) {
	//			//    if (!x[(long long)row][(long long)col - 1]) {
	//			//        probss[(long long)row][(long long)col - 1] -= 0.001;
	//			//    }
	//			//}
	//			//if (row != 9) {
	//			//    if (!x[(long long)row + 1][(long long)col]) {
	//			//        probss[(long long)row + 1][(long long)col] ++;
	//			//        foundhit = true;
	//			//        //next_row = row+1;
	//			//        //next_col = col;
	//			//        //return;
	//			//    }
	//			//}
	//			//if (col != 9) {
	//			//    if (!x[(long long)row][(long long)col + 1]) {
	//			//        probss[(long long)row][(long long)col + 1] ++;
	//			//        foundhit = true;
	//			//        //next_row = row;
	//			//        //next_col = col+1;
	//			//        //return;
	//			//    }
	//			//}
	//			//if (row != 0) {
	//			//    if (!x[(long long)row - 1][(long long)col]) {
	//			//        probss[(long long)row - 1][(long long)col] ++;
	//			//        foundhit = true;
	//			//        //next_row = row-1;
	//			//        //next_col = col;
	//			//        //return;
	//			//    }
	//			//}
	//			//if (col != 0) {
	//			//    if (!x[(long long)row][(long long)col - 1]) {
	//			//        probss[(long long)row][(long long)col - 1]++;
	//			//        foundhit = true;
	//			//        //next_row = row;
	//			//        //next_col = col-1;
	//			//        //return;
	//			//    }
	//			//}
	//		}
	//	}
	//}
	////std::cout << "\n";
	////for (int i = 0; i < 10; i++){
	////   for (int k = 0; k < 9; k++){
	////       std::cout << probss[i][k] << " , ";
	////    } 
	////    std::cout << probss[i][9] << "\n";
	////}
	////system("pause");
	//double max_prob = -1.0;
	//unordered_map<double, pair<int, int>> candidates;
	//for (int r = 0; r < 10; r++) {
	//	for (int c = 0; c < 10; c++) {
	//		if (!x[r][c]) {
	//			if (probss[r][c] > max_prob) {
	//				max_prob = probss[r][c];
	//			}
	//			candidates[probss[r][c]] = make_pair(r, c);
	//		}
	//	}
	//}
	//next_row = candidates[max_prob].first;
	//next_col = candidates[max_prob].second;
	//if (!foundhit) {
	//	if (zaehler == 2) {
	//		double max_prob2 = -1.0;
	//		unordered_map<double, pair<int, int>> candidates2;
	//		for (int r = 9; r >= 0; r--) {
	//			for (int c = 9; c >= 0; c--) {
	//				if (!x[r][c]) {
	//					if (probss[r][c] > max_prob2) {
	//						max_prob2 = probss[r][c];
	//					}
	//					candidates2[probss[r][c]] = make_pair(r, c);
	//				}
	//			}
	//		}
	//		next_row = candidates2[max_prob2].first;
	//		next_col = candidates2[max_prob2].second;
	//	}
	//	else if (zaehler == 3) {
	//		double max_prob2 = -1.0;
	//		unordered_map<double, pair<int, int>> candidates2;
	//		for (int r = 0; r < 5; r++) {
	//			for (int c = 0; c < 5; c++) {
	//				if (!x[r][c]) {
	//					if (probss[r][c] > max_prob2) {
	//						max_prob2 = probss[r][c];
	//					}
	//					candidates2[probss[r][c]] = make_pair(r, c);
	//				}
	//			}
	//		}
	//		for (int r = 9; r > 4; r--) {
	//			for (int c = 9; c > 4; c--) {
	//				if (!x[r][c]) {
	//					if (probss[r][c] > max_prob2) {
	//						max_prob2 = probss[r][c];
	//					}
	//					candidates2[probss[r][c]] = make_pair(r, c);
	//				}
	//			}
	//		}
	//		next_row = candidates2[max_prob2].first;
	//		next_col = candidates2[max_prob2].second;
	//	}
	//}
	//zaehler++;
	//if (zaehler > 3) {
	//	zaehler = 1;
	//}
