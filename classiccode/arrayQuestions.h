#pragma once
#include<iostream>
#include<vector>
using std::cout;
using std::endl;
using std::pair;
using std::vector;
class Solution {
public:
	//给一个数组array，array中只有一个数字出现了奇数次，其它所有数字都出现了偶数次，找到出现了奇数次的数字
	//[1,1,2,2,3,3,3]->3
	static int SearchTheOnlyOddNumber(const vector<int>& nums) {
		//异或
		int ans = 0;
		for (int i : nums) {
			ans ^= i;
		}
		return ans;
	}
public:
	//给一个数组array，array中有2个数字出现了奇数次，其它所有数字都出现了偶数次，找到这2个出现了奇数次的数字
	//[1,1,2,2,3,3,4,5]->4,5
	static pair<int,int> SearchTheTwoOddNumber(const vector<int>& nums) {
		//假设这两个数字是x,y
		int ans = 0;
		for (int i : nums) {
			ans ^= i;
		}
		//ans=x^y，找到ans从右往左数的第一个为“1”的比特位
		ans = ans & (~ans + 1);//x,y的这一位一定不同
		int x = 0, y = 0;
		for (int i : nums) {
			if (ans & i) {//表示这一位是“1”
				x ^= i;
			}
			else {
				y ^= i;
			}
		}
		return { x,y };
	}
};