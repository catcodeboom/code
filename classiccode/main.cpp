#include"RandomNum.h"
#include"classicSort.h"
#include<iostream>
using std::cout;
using std::endl;
int main() {
	srand((unsigned int)time(nullptr));
	vector<int> nums = RandomNum::getRandomVector(500000);
	auto nums2 = nums;
	auto nums3 = nums;
	std::sort(nums3.begin(), nums3.end());
	Solution::TimeQuickSort(nums2);
	if (nums2 == nums3) {
		cout << "��������ȷ" << endl;
	}
	else {
		cout << "����������" << endl;
	}
	Solution::TimeHeapSort(nums);
	if (nums == nums3) {
		cout << "��������ȷ" << endl;
	}
	else {
		cout << "����������" << endl;
	}
	return 0;
}