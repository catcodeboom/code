#pragma once
#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
#include<cassert>
#include<string>
using std::string;
using std::function;
using std::cout;
using std::endl;
using std::pair;
using std::vector;
class Solution {
public:
	static int EightQueensProblem(int n) {//八皇后问题
		vector<int> pos(n, -1);//pos记录已经选择过的点
		auto legal = [&](int row, int col) {
			for (int i = 0; i < n; i++) {
				if (pos[i] != -1) {
					if (col == pos[i] || std::abs(row - i) == std::abs(pos[i] - col)) {
						return false;
					}
				}
			}
			return true;
		};
		//auto print = [&]() {
		//	for (int i = 0; i < n; i++) {
		//		for (int j = 0; j < n; j++) {
		//			if (j == pos[i]) {
		//				cout << '#' << ' '<<' ';//表示皇后
		//			}
		//			else {
		//				cout << '*' << ' '<<' ';//表示空格
		//			}
		//		}
		//		cout << endl << endl;;
		//	}
		//	cout << "===============================" << endl;
		//};
		function<int(int)> f = [&](int cur) {//cur表示当前来到第几行,able表示可选的列
			if (cur == n) {
				//print();
				return 1;//表示找到了一种方案
			}
			int ans = 0;
			for (int i = 0; i < n; i++) {
				if (legal(cur, i)) {//若当前位置合法，可以使用
					pos[cur] = i;
					ans += f(cur + 1);
					pos[cur] = -1;
				}
			}
			return ans;
		};
		return f(0);
	}
public:
	//使用位运算优化八皇后问题
	static int EightQueensProblemBit(int n) {
		if (n < 1 || n>64) {
			cout << "参数不合法" << endl;
			return -1;
		}
		size_t limits = (1 << n) - 1;
		function<size_t(size_t, size_t, size_t)> f = [&](size_t collim, size_t leftlim, size_t rightlim)->size_t {
			if (limits == collim) {//表示没有位置可选
				return 1;
			}
			size_t ans = 0;
			size_t pos = limits & (~(collim | leftlim | rightlim));//pos表示实际可用位置
			while (pos) {
				size_t mostrightone = pos & (~pos + 1);//取到从右往左第一个“1”
				pos = pos - mostrightone;//剩余可用位置
				ans += f(collim | mostrightone, (leftlim | mostrightone) << 1, (rightlim | mostrightone) >> 1);
			}
			return ans;
		};
		return f(0, 0, 0);
	}
public:
	static void Hannot_tower(int n) {
		//n层汉诺塔的移动问题
		//1~n的盘子从左移动到右，可借助的柱子为中间柱子
		function<void(int, const string&, const string&, const string&)> f = [&](int i,const string& from, const string& dst, const string& help) {
			if (i == 0) {
				return;
			}
			f(i - 1, from, help, dst);//1~i-1从左移动到中间
			cout << i << "号盘子从" << from << "移动到" << dst << endl;
			f(i - 1, help, dst, from);//1~i-1从中间移动到右
		};
		f(n, "\"左边\"", "\"右边\"", "\"中间\"");
	}
};