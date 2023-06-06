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
	static int EightQueensProblem(int n) {//�˻ʺ�����
		vector<int> pos(n, -1);//pos��¼�Ѿ�ѡ����ĵ�
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
		//				cout << '#' << ' '<<' ';//��ʾ�ʺ�
		//			}
		//			else {
		//				cout << '*' << ' '<<' ';//��ʾ�ո�
		//			}
		//		}
		//		cout << endl << endl;;
		//	}
		//	cout << "===============================" << endl;
		//};
		function<int(int)> f = [&](int cur) {//cur��ʾ��ǰ�����ڼ���,able��ʾ��ѡ����
			if (cur == n) {
				//print();
				return 1;//��ʾ�ҵ���һ�ַ���
			}
			int ans = 0;
			for (int i = 0; i < n; i++) {
				if (legal(cur, i)) {//����ǰλ�úϷ�������ʹ��
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
	//ʹ��λ�����Ż��˻ʺ�����
	static int EightQueensProblemBit(int n) {
		if (n < 1 || n>64) {
			cout << "�������Ϸ�" << endl;
			return -1;
		}
		size_t limits = (1 << n) - 1;
		function<size_t(size_t, size_t, size_t)> f = [&](size_t collim, size_t leftlim, size_t rightlim)->size_t {
			if (limits == collim) {//��ʾû��λ�ÿ�ѡ
				return 1;
			}
			size_t ans = 0;
			size_t pos = limits & (~(collim | leftlim | rightlim));//pos��ʾʵ�ʿ���λ��
			while (pos) {
				size_t mostrightone = pos & (~pos + 1);//ȡ�����������һ����1��
				pos = pos - mostrightone;//ʣ�����λ��
				ans += f(collim | mostrightone, (leftlim | mostrightone) << 1, (rightlim | mostrightone) >> 1);
			}
			return ans;
		};
		return f(0, 0, 0);
	}
public:
	static void Hannot_tower(int n) {
		//n�㺺ŵ�����ƶ�����
		//1~n�����Ӵ����ƶ����ң��ɽ���������Ϊ�м�����
		function<void(int, const string&, const string&, const string&)> f = [&](int i,const string& from, const string& dst, const string& help) {
			if (i == 0) {
				return;
			}
			f(i - 1, from, help, dst);//1~i-1�����ƶ����м�
			cout << i << "�����Ӵ�" << from << "�ƶ���" << dst << endl;
			f(i - 1, help, dst, from);//1~i-1���м��ƶ�����
		};
		f(n, "\"���\"", "\"�ұ�\"", "\"�м�\"");
	}
};