#pragma once
#include "global.h"
#include "Player.h"
#include "Draw.h"
class Compare
{
std::vector<std::vector<bool>> x = std::vector<std::vector<bool>>(10, std::vector<bool>(10, 0));
	friend class Draw;
	friend class Player;
public:
	
	template<typename Tx,typename Tx_, typename Tx__>
	void movemaker(int& , int& , Tx&, Tx_&, Tx__&);
};

//#include <map>
//#include <compare>
//#include <functional>
//class Solution {
//public:
//	vector<int> twoSum(vector<int>& nums, int target) {
//		unordered_map<int, int> map;
//		for (int i = 0; i < nums.size(); i++) {
//			int complement = target - nums[i];
//			if (map.count(complement)) {
//				return { map[complement], i };
//			}
//			map[nums[i]] = i;
//		}
//		return {-1,-1};
//	}
//};
//void compare(std::vector<std::vector<bool>>&, std::vector<std::vector<bool>>&, int&, int&);