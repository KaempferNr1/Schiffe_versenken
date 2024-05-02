#include "headers/probabilityPc.h"
#include <queue>
#include "headers/player.h"
#include "headers/computer.h"
#include "headers/Draw.h"
namespace battleships 
{
	probabilityPc::probabilityPc(Draw& drawer) 
	{
		randomengine = std::mt19937_64(std::random_device()());
		dptr = &drawer;
		std::uniform_real_distribution<double> for_weight_destroyed_missed(-5, 5);
		std::uniform_real_distribution<double> for_weight_hit_unused(0, 10);
		hit_weight = for_weight_hit_unused(randomengine);
		destroyed_weight = for_weight_destroyed_missed(randomengine);
		missed_weight = for_weight_destroyed_missed(randomengine);
		unused_weight = for_weight_hit_unused(randomengine);
		this->fptr = &probabilityPc::hard_version;
	}
	probabilityPc::probabilityPc(Draw& drawer, int x)
	{
		
		randomengine = std::mt19937_64(std::random_device()());
		dptr = &drawer;
		std::uniform_real_distribution<double> for_weight_destroyed_missed(-5, -0.001);
		std::uniform_real_distribution<double> for_weight_hit(1, 10);
		std::uniform_real_distribution<double> for_weight_unused(1, 10);
		switch (x)
		{
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
	probabilityPc::probabilityPc()
	{
		randomengine = std::mt19937_64(std::random_device()());
		std::uniform_real_distribution<double> for_weight_destroyed_missed(-5, 5);
		destroyed_weight = for_weight_destroyed_missed(randomengine);
		missed_weight = for_weight_destroyed_missed(randomengine);

		std::uniform_real_distribution<double> for_weight_hit_unused(0, 10);
		hit_weight = for_weight_hit_unused(randomengine);
		unused_weight = for_weight_hit_unused(randomengine);
		this->fptr = &probabilityPc::hard_version;
	}

	std::vector<std::vector<double>> probabilityPc::initialize_grid() 
	{
		std::vector<std::vector<double>> grid(10, std::vector<double>(10, 1.0));
		return grid;
	}
	void probabilityPc::update_probabilities(std::vector<std::vector<bool>>& hits)
	{
	}

	void probabilityPc::select_next_guess(std::vector<std::vector<bool>>& x, int& next_row, int& next_col)
	{
		(this->*fptr)(x, next_row, next_col);

	}

	void probabilityPc::easy_version(std::vector<std::vector<bool>>& hit_vec, int& next_row, int& next_col)
	{
		foundhit = false;
		for (int row = 0; row < global::sizefield; ++row) 
		{
			for (int col = 0; col < global::sizefield; ++col)
			{
				const char cell = map[row][col];
				if (cell == global::hit)
				{
					probss[row][col] = 0.0;
					change_probs(hit_vec, col, row, hit_weight, false);
					foundhit = true;
				}
				else if (cell == global::destroyed) 
				{
					probss[row][col] = 0.0;
					change_probs(hit_vec, col, row, destroyed_weight, false);
				}
			}
		}
		if (get_probs) 
		{
			std::cout << "\n";
			for (int i = 0; i < global::sizefield; i++)
			{
				for (int k = 0; k < global::sizefield-1; k++) 
				{
					std::cout << probss[i][k] << " , ";
				}
				std::cout << probss[i][9] << "\n";
			}
			std::cin.get();
		}
		if (!foundhit)
		{
			std::uniform_int_distribution distr(0, global::sizefield - 1);
			do {
				next_row = distr(randomengine);
				next_col = distr(randomengine);
			} while (!((hit_vec[next_row][next_col] == 0) ? 1 : 0));
			numberofrandhits++;
			return;
		}
		double max_prob = -1.0;
		std::unordered_map<double, std::pair<int, int>> candidates;
		for (int r = 0; r < global::sizefield; r++)
		{
			for (int c = 0; c < global::sizefield; c++) 
			{
				if (!hit_vec[r][c])
				{
					if (probss[r][c] > max_prob)
					{
						max_prob = probss[r][c];
					}
					candidates[probss[r][c]] = std::make_pair(r, c);
				}
			}
		}
		next_row = candidates[max_prob].first;
		next_col = candidates[max_prob].second;
	}

	void probabilityPc::medium_version(std::vector<std::vector<bool>>& hit_vec, int& next_row, int& next_col)
	{
		for (int row2 = 0; row2 < global::sizefield; row2++)
		{
			for (int col2 = 0; col2 < global::sizefield; col2++)
			{
				if (!hit_vec[row2][col2] && probss[row2][col2] != 0.0)
				{
					probss[row2][col2] = 1;
				}
			}
		}
		bool early_return = false;
		std::uniform_int_distribution distr(0, global::randnumbermax - 1);
		int rowrand = distr(randomengine);
		int colrand = distr(randomengine);
		if ((colrand < global::sizefield && colrand >= 0) && (rowrand < global::sizefield && colrand >= 0))
		{
			char randcell = map[rowrand][colrand];
			if (randcell == global::ship)
			{
				next_row = rowrand;
				next_col = colrand;
				numberofrandhits++;
				early_return = true;
			}
		}
		foundhit = false;
		for (int row = 0; row < global::sizefield; ++row)
		{
			for (int col = 0; col < global::sizefield; ++col)
			{
				const char cell = map[row][col];
				if (cell == global::miss)
				{
					probss[row][col] = 0.0;
					change_probs(hit_vec, col, row, missed_weight, false);
				}
				else if (cell == global::hit)
				{
					probss[row][col] = 0.0;
					change_probs(hit_vec, col, row, hit_weight, true);
					foundhit = true;
				}
				else if (cell == global::destroyed) 
				{
					probss[row][col] = 0.0;
					change_probs(hit_vec, col, row, destroyed_weight, false);
				}
			}
		}
		if (get_probs)
		{
			std::cout << "\n";
			for (int i = 0; i < global::sizefield; i++) 
			{
				for (int k = 0; k < global::sizefield-1; k++)
				{
					std::cout << probss[i][k] << " , ";
				}
				std::cout << probss[i][9] << "\n";
			}
			std::cin.get();
		}
		if (early_return)
		{
			return;
		}
		double max_prob = -1.0;
		std::unordered_map<double, std::pair<int, int>> candidates;
		for (int r = 0; r < global::sizefield; r++)
		{
			for (int c = 0; c < global::sizefield; c++) 
			{
				if (!hit_vec[r][c])
				{
					if (probss[r][c] > max_prob) 
					{
						max_prob = probss[r][c];
					}
					candidates[probss[r][c]] = std::make_pair(r, c);
				}
			}
		}
		next_row = candidates[max_prob].first;
		next_col = candidates[max_prob].second;
		if (!foundhit)
		{
			if (zaehler == 2) 
			{
				double max_prob2 = -1.0;
				std::unordered_map<double, std::pair<int, int>> candidates2;
				for (int r = 9; r >= 0; r--)
				{
					for (int c = 9; c >= 0; c--) 
					{
						if (!hit_vec[r][c])
						{
							if (probss[r][c] > max_prob2)
							{
								max_prob2 = probss[r][c];
							}
							candidates2[probss[r][c]] = std::make_pair(r, c);
						}
					}
				}
				next_row = candidates2[max_prob2].first;
				next_col = candidates2[max_prob2].second;
			}
			else if (zaehler == 3)
			{
				double max_prob2 = -1.0;
				std::unordered_map<double, std::pair<int, int>> candidates2;
				for (int r = 0; r < 5; r++)
				{
					for (int c = 9; c > 4; c--)
					{
						if (!hit_vec[r][c]) 
						{
							if (probss[r][c] > max_prob2)
							{
								max_prob2 = probss[r][c];
							}
							candidates2[probss[r][c]] = std::make_pair(r, c);
						}
					}
					for (int c = 0; c < 5; c++)
					{
						if (!hit_vec[r][c])
						{
							if (probss[r][c] > max_prob2)
							{
								max_prob2 = probss[r][c];
							}
							candidates2[probss[r][c]] = std::make_pair(r, c);
						}
					}
				}
				for (int r = 9; r > 4; r--) 
				{
					for (int c = 0; c < 5; c++) 
					{
						if (!hit_vec[r][c])
						{
							if (probss[r][c] > max_prob2)
							{
								max_prob2 = probss[r][c];
							}
							candidates2[probss[r][c]] = std::make_pair(r, c);
						}
					}
					for (int c = 9; c > 4; c--)
					{
						if (!hit_vec[r][c]) 
						{
							if (probss[r][c] > max_prob2)
							{
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
		if (zaehler > 3) 
		{
			zaehler = 1;
		}
	}

	void probabilityPc::hard_version(std::vector<std::vector<bool>>& hit_vec, int& next_row, int& next_col)
	{
		for (int row = 0; row < global::sizefield; row++)
		{
			for (int col = 0; col < global::sizefield; col++)
			{
				if (!hit_vec[row][col] && probss[row][col] != 0.0)
				{
					probss[row][col] = 1;
				}
			}
		}
		bool early_return = false;

		foundhit = false;
		for (int row = 0; row < global::sizefield; row++)
		{
			for (int col = 0; col < global::sizefield; col++)
			{
				const char cell = map[row][col];
				if (cell == global::hit)
				{
					change_probs(hit_vec, col, row, hit_weight, true);
					foundhit = true;
				}
			}
		}
		if (!foundhit) 
		{
			std::unordered_map<int, int> shipps;
			for (int i = 0; i < 4; i++) 
			{
				shipps[i+2] = shipsleft[i];
			}
			for (int row = 0; row < global::sizefield; row++) 
			{
				for (int col = 0; col < global::sizefield; col++) 
				{
					if (!hit_vec[row][col])
					{
						for (auto& [shiplen, shipleft] : shipps) 
						{
							if (shipleft) 
							{
								if (Player1::validplacement(row, col, shiplen, true, hit_vec))
								{
									for (int j = 0; j < shiplen; j++) 
									{
										probss[row][col + j] += (shiplen + j) * unused_weight;
									}
								}
								else 
								{
									for (int j = 0; j < shiplen; j++) 
									{
										if (!(col + j >= 0 && col + j <= 9))
										{
											break;
										}
										probss[row][col + j] -= ((shiplen - j) * unused_weight) / hit_weight;
									}
								}
								if (Player1::validplacement(row, col, shiplen, false, hit_vec))
								{
									for (int j = 0; j < shiplen; j++) 
									{
										probss[row + j][col] += (shiplen + j) * unused_weight;
									}
								}
								else
								{
									for (int j = 0; j < shiplen; j++)
									{
										if (!(row + j >= 0 && row + j <= 9)) 
										{
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
		if (get_probs) 
		{
			std::cout << "\n";
			for (int i = 0; i < global::sizefield; i++)
			{
				for (int k = 0; k < global::sizefield-1; k++) 
				{
					std::cout << probss[i][k] << " , ";
				}
				std::cout << probss[i][9] << "\n";
			}
			std::cin.get();
		}
		if (early_return)
		{
			return;
		}
		double max_prob = std::numeric_limits<double>::lowest();
		std::unordered_map<double, std::pair<int, int>> candidates;
		bool tie = false;
		std::vector<std::pair<int, int>> tie_candidates;
		tie_candidates.reserve(10);
		for (int r = 0; r < global::sizefield; r++)
		{
			for (int c = 0; c < global::sizefield; c++)
			{
				if (!hit_vec[r][c])
				{
					if (probss[r][c] > max_prob) 
					{
						max_prob = probss[r][c];
						tie = false;
						tie_candidates.clear();
					}
					else if (probss[r][c] == max_prob)
					{
						tie = true;
						tie_candidates.emplace_back(r, c);
					}
					candidates[probss[r][c]] = std::make_pair(r, c);
				}
			}
		}
		if (tie) 
		{
			std::uniform_int_distribution distro(0, (int)tie_candidates.size() - 1);
			const std::pair<int, int> res = tie_candidates[distro(randomengine)];
			next_row = res.first;
			next_col = res.second;
		}
		else {
			next_row = candidates[max_prob].first;
			next_col = candidates[max_prob].second;
		}

		zaehler++;
		if (zaehler > 3) 
		{
			zaehler = 1;
		}
	}

	void probabilityPc::impossible_version(std::vector<std::vector<bool>>& hit_vec, int& next_row, int& next_col)
	{
		std::bernoulli_distribution event(0.5);
		if (event(randomengine))
		{
			for (int row = 0; row < global::sizefield; ++row) 
			{
				for (int col = 0; col < global::sizefield; ++col)
				{
					const char cell = map[row][col];
					if (cell == global::ship)
					{
						next_row = row;
						next_col = col;
						return;
					}
				}
			}
		}
		else 
		{
			hard_version(hit_vec, next_row, next_col);
		}
	}

	constexpr double smart_change = 8;

	void probabilityPc::change_probs(std::vector<std::vector<bool>>& x, int& col, int& row, double change, bool do_smarter_check)
	{

		probss[row][col] = 0;
		if (row != global::sizefield-1) 
		{
			if (!x[(long long)row + 1][(long long)col]) 
			{
				probss[(long long)row + 1][(long long)col] += change;
			}
			if (map[(long long)row + 1][(long long)col] == global::hit && do_smarter_check)
			{
				if (row != 0 && !x[(long long)row - 1][(long long)col]) 
				{
					probss[(long long)row - 1][(long long)col] += smart_change;
				}
			}
		}
		if (col != global::sizefield-1) 
		{
			if (!x[(long long)row][(long long)col + 1])
			{
				probss[(long long)row][(long long)col + 1] += change;
			}
			if (map[(long long)row][(long long)col + 1] == global::hit && do_smarter_check)
			{
				if (col != 0 && !x[(long long)row][(long long)col - 1])
				{
					probss[(long long)row][(long long)col - 1] += smart_change;
				}
			}
		}
		if (row != 0)
		{
			if (!x[(long long)row - 1][(long long)col])
			{
				probss[(long long)row - 1][(long long)col] += change;
			}
			if (map[(long long)row - 1][(long long)col] == global::hit && do_smarter_check)
			{
				if (row != global::sizefield-1 && !x[(long long)row + 1][(long long)col])
				{
					probss[(long long)row + 1][(long long)col] += smart_change;
				}
			}

		}
		if (col != 0) 
		{
			if (!x[(long long)row][(long long)col - 1])
			{
				probss[(long long)row][(long long)col - 1] += change;
			}
			if (map[(long long)row][(long long)col - 1] == global::hit && do_smarter_check)
			{
				if (col != global::sizefield-1 && !x[(long long)row][(long long)col + 1])
				{
					probss[(long long)row][(long long)col + 1] += smart_change;
				}
			}
		}
		
	}
}