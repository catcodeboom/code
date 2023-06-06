#pragma once
#include<random>
#include<assert.h>
#include<vector>
using std::vector;
class RandomNum {
public:
	static int getrandnum(int left, int right) {
		//�������Ҫ1��λ��
		assert(left > 0 && right > 0 && left < right);
		int cnt = 1;
		int base = 1;
		while (base < right) {
			base = base * 2 + 1;
			cnt++;
		}
		int num = 0;
		do {
			num = 0;
			for (int i = 0; i < cnt; i++) {
				num += ZeroOneRandom() << i;
			}
		} while (num<left || num>right);
		return num;
	}
	static vector<int> getRandomVector(int size) {
		vector<int> nums(size);
		for (int i = 0; i < size; i++) {
			nums[i] = getrandnum(1, 5000000);
		}
		return nums;
	}
	static int ZeroOneRandom() {
		//��main�е���srand((unsigned int)time(nullptr));
		int x = 0;
		do {
			x = rand();
		} while (x > 10000);
		//0~4999 5000 10000
		return x >= 5000 ? 1 : 0;
	}
};