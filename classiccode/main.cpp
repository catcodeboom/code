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
		cout << "排序结果正确" << endl;
	}
	else {
		cout << "排序结果错误" << endl;
	}
	Solution::TimeHeapSort(nums);
	if (nums == nums3) {
		cout << "排序结果正确" << endl;
	}
	else {
		cout << "排序结果错误" << endl;
	}
	return 0;
}