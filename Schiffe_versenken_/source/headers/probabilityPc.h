#pragma once
#include <map>
#include <unordered_map>

#include "global.h"



struct probs 
{
	int y;
	int x;
	double probability;
	bool operator<(const probs& other) const 
	{
		return probability > other.probability;
	}
};
namespace std 
{
	template<>
	struct hash<probs> 
	{
		size_t operator()(const probs& key) 
		{
			return hash<double>()(key.probability);
		}
	};
}
namespace battleships 
{
	class Draw;
	class probabilityPc
	{
		//std::map<probs, probs> probabilitys;
	public:
		probabilityPc(Draw&);
		probabilityPc(Draw&, int);
		probabilityPc();
		~probabilityPc();
		std::array<int, 4> shipsleft = { 0 };
		std::mt19937_64 randomengine;
		double unused_weight;
		double hit_weight;
		double destroyed_weight;
		double missed_weight;
		bool get_probs = 0;
		std::vector<std::vector<bool>> boolmap = std::vector<std::vector<bool>>(10, std::vector<bool>(10, 0));
		void (probabilityPc::* fptr)(std::vector<std::vector<bool>>&, int&, int&) = nullptr; // das ist ein funktionspointer
		int maxlength = 5;
		int minlength = 2;
		int zaehler = 1;
		bool foundhit = 0;
		int numberofrandhits = 0;
		Draw* dptr = nullptr;
		std::vector<std::vector<double>> probss = std::vector<std::vector<double>>(10, std::vector<double>(10, 1));
		std::vector<std::vector<char>> map = std::vector<std::vector<char>>(10, std::vector<char>(10, global::miss));
		std::vector<std::vector<double>> initialize_grid();
		void update_probabilities(std::vector<std::vector<bool>>&);

		void select_next_guess(std::vector<std::vector<bool>>&, int&, int&);
		void easy_version(std::vector<std::vector<bool>>&, int&, int&);
		void medium_version(std::vector<std::vector<bool>>&, int&, int&);
		void hard_version(std::vector<std::vector<bool>>&, int&, int&);
		void impossible_version(std::vector<std::vector<bool>>&, int&, int&);

		void change_probs(std::vector<std::vector<bool>>&, int&, int&, double, bool, bool);
		

	};
}
