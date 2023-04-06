#pragma once
#include "global.h"
#include "Draw.h"
//#include "computer.h"
//#include "player.h"
#include <map>
#include <unordered_map>
struct probs {
	int y;
	int x;
	double probability;
	bool operator<(const probs& other) const {
		return probability > other.probability;
	}
};
namespace std {
	template<>
	struct hash<probs> {
		size_t operator()(const probs& key) {
			return hash<double>()(key.probability);
		}
	};
}
class probabilityPc{
	std::map<probs, probs> probabilitys;
public:
	int zaehler = 0;
	bool foundhit = 0;
	int numberofrandhits = 0;
	Draw* dptr = nullptr;
	std::vector<std::vector<double>> probss = std::vector<std::vector<double>>(10, std::vector<double>(10, 1));
	std::vector<std::vector<char>> map = std::vector<std::vector<char>>(10, std::vector<char>(10, miss));
	std::vector<std::vector<bool>> boolmap = std::vector<std::vector<bool>>(10, std::vector<bool>(10, 0));
	template<typename _T, typename __T>
	void makemove(_T&, __T&, int&, int&);
	std::vector<std::vector<double>> initialize_grid();
	void update_probabilities(std::vector<std::vector<bool>>&);
	void select_next_guess(std::vector<std::vector<bool>>&, int&, int&);
	void change_probs(std::vector<std::vector<bool>>&, int& ,int& ,double, bool);
	probabilityPc(Draw&);
	probabilityPc();
	~probabilityPc();
};
//bool compareCandidates(const std::pair<double, std::pair<int, int>>&, const std::pair<double, std::pair<int, int>>& );
