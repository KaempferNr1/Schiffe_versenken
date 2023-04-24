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

#define if_schleife(a,c) if(a){while((c)){
#define else_schleife(a) else{ while((a)){
#define else_if_schleife(a,c){{ else if((a)){while((c)){
probabilityPc::probabilityPc(Draw & drawer) {
	randomengine = std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count());
	dptr = &drawer;
	std::uniform_real_distribution<double> for_weight_destroyed_missed(-5, 5);
	std::uniform_real_distribution<double> for_weight_hit_unused(0, 10);
	hit_weight = for_weight_hit_unused(randomengine);
	destroyed_weight = for_weight_destroyed_missed(randomengine);
	missed_weight = for_weight_destroyed_missed(randomengine);
	unused_weight = for_weight_hit_unused(randomengine);
	this->fptr = &probabilityPc::hard_version;
}
probabilityPc::probabilityPc(Draw& drawer, int x) {
	randomengine = std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count());
	dptr = &drawer;
	std::uniform_real_distribution<double> for_weight_destroyed_missed(-5, -0.001);
	std::uniform_real_distribution<double> for_weight_hit(1, 10);
	std::uniform_real_distribution<double> for_weight_unused(1, 10);
	switch (x) {
	case 1:
		this->fptr = &probabilityPc::easy_version;
		hit_weight = 3;
		destroyed_weight = 3;
		missed_weight = 0;
		unused_weight = 0;
		break;
	case 2:
		this->fptr = &probabilityPc::medium_version;
		hit_weight = 3;
		destroyed_weight = -0.001;
		missed_weight = -0.01;
		unused_weight = 0;
		break;
	case 3:
		this->fptr = &probabilityPc::hard_version;
		hit_weight = for_weight_hit(randomengine);
		destroyed_weight = for_weight_destroyed_missed(randomengine);
		missed_weight = for_weight_destroyed_missed(randomengine);
		unused_weight = for_weight_unused(randomengine);
		break;
	case 4:
		this->fptr = &probabilityPc::impossible_version;
		hit_weight = for_weight_hit(randomengine);
		destroyed_weight = for_weight_destroyed_missed(randomengine);
		missed_weight = for_weight_destroyed_missed(randomengine);
		unused_weight = for_weight_unused(randomengine);
		break;
	default:
		this->fptr = &probabilityPc::hard_version;
		hit_weight = for_weight_hit(randomengine);
		destroyed_weight = for_weight_destroyed_missed(randomengine);
		missed_weight = for_weight_destroyed_missed(randomengine);
		unused_weight = for_weight_unused(randomengine);
		break;
	}
}
probabilityPc::probabilityPc() {
	randomengine = std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> for_weight_destroyed_missed(-5, 5);
	std::uniform_real_distribution<double> for_weight_hit_unused(0, 10);
	hit_weight = for_weight_hit_unused(randomengine);
	destroyed_weight = for_weight_destroyed_missed(randomengine);
	missed_weight = for_weight_destroyed_missed(randomengine);
	unused_weight = for_weight_hit_unused(randomengine);
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
				probss[row][col] = 0.0;
				change_probs(x, col, row, hit_weight, 0, 0);
				foundhit = true;
			}
			else if (cell == destroyed) {
				probss[row][col] = 0.0;
				change_probs(x, col, row, destroyed_weight, 0, 0);
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
		numberofrandhits++;
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
				probss[row][col] = 0.0;
				change_probs(x, col, row, missed_weight, 0, 0);
			}
			else if (cell == ship) {
			}
			else if (cell == hit) {
				probss[row][col] = 0.0;
				change_probs(x, col, row, hit_weight, 1, 0);
				foundhit = true;
			}
			else if (cell == destroyed) {
				probss[row][col] = 0.0;
				change_probs(x, col, row, destroyed_weight, 0, 0);
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
	std::vector<std::vector<bool>> x_copy = x;
	foundhit = false;
	for (int row = 0; row < 10; row++) {
		for (int col = 0; col < 10; col++) {
			char cell = map[row][col];
			if (cell == miss) {
				change_probs(x_copy, col, row, missed_weight, 0, 0);
			}
			else if (cell == hit) {
				x_copy[row][col] = 0;
				change_probs(x_copy, col, row, hit_weight, 1, 0);
				foundhit = true;
			}
			else if (cell == destroyed) {
				change_probs(x_copy, col, row, destroyed_weight, 0, 0);
			}
		}
	}
	if (!foundhit) {
		std::array<int, 4> ships_arr = { 2,3,4,5 };
		std::unordered_map<int, int> shipps;
		for (int i = 0; i < 4; i++) {
			shipps[ships_arr[i]] = shipsleft[i];
		}
		bool cont = 1;
		for (int row = 0; row < 10; row++) {
			for (int col = 0; col < 10; col++) {
				if (map[row][col] == unused) {
					for (auto& [shiplen, shipleft] : shipps) {
						if (shipleft) {
							if (Player1::validplacement(row, col, shiplen, 1, x_copy)) {
								for (int j = 0; j < shiplen; j++) {
									probss[row][col + j] += (shiplen - j) * unused_weight;
								}
							}
						else {
							for (int j = 0; j < shiplen; j++) {
								if (!(col + j >= 0 && col + j <= 9)) {
									break;
								}
								probss[row][col + j] -= ((shiplen - j) * unused_weight) / hit_weight;
							}
						}
						if (Player1::validplacement(row, col, shiplen, 0, x_copy)) {
							for (int j = 0; j < shiplen; j++) {
								probss[row + j][col] += (shiplen - j) * unused_weight;
							}
						}
						else {
							for (int j = 0; j < shiplen; j++) {
								if (!(row + j >= 0 && row + j <= 9)) {
									break;
								}
								probss[row + j][col] -= ((shiplen - j) * unused_weight) / hit_weight;
								}
							}
						}
					}
				}
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
	double max_prob = std::numeric_limits<double>::lowest();
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

	zaehler++;
	if (zaehler > 3) {
		zaehler = 1;
	}
}

void probabilityPc::impossible_version(std::vector<std::vector<bool>>& x, int& next_row, int& next_col) {
	std::bernoulli_distribution event(0.5);
	if (event(randomengine)) {
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
	else {
		hard_version(x, next_row, next_col);
	}
}





void probabilityPc::change_probs(std::vector<std::vector<bool>>& x, int& col, int& row, double change, bool do_thething, bool do_the_other_thing) {
	if (do_the_other_thing) {


	}
	else {
		probss[row][col] = 0;
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
