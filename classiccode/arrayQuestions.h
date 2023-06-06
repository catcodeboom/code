#pragma once
#include<iostream>
#include<vector>
using std::cout;
using std::endl;
using std::pair;
using std::vector;
class Solution {
public:
	//��һ������array��array��ֻ��һ�����ֳ����������Σ������������ֶ�������ż���Σ��ҵ������������ε�����
	//[1,1,2,2,3,3,3]->3
	static int SearchTheOnlyOddNumber(const vector<int>& nums) {
		//���
		int ans = 0;
		for (int i : nums) {
			ans ^= i;
		}
		return ans;
	}
public:
	//��һ������array��array����2�����ֳ����������Σ������������ֶ�������ż���Σ��ҵ���2�������������ε�����
	//[1,1,2,2,3,3,4,5]->4,5
	static pair<int,int> SearchTheTwoOddNumber(const vector<int>& nums) {
		//����������������x,y
		int ans = 0;
		for (int i : nums) {
			ans ^= i;
		}
		//ans=x^y���ҵ�ans�����������ĵ�һ��Ϊ��1���ı���λ
		ans = ans & (~ans + 1);//x,y����һλһ����ͬ
		int x = 0, y = 0;
		for (int i : nums) {
			if (ans & i) {//��ʾ��һλ�ǡ�1��
				x ^= i;
			}
			else {
				y ^= i;
			}
		}
		return { x,y };
	}
};