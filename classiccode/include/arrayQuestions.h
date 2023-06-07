#pragma once
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::pair;
using std::vector;
class Solution {
public:
    // 1个数字出现了奇数次,其余都出现了偶数次,找到奇数次的
    //[1,1,2,2,3,3,3]->3
    static int SearchTheOnlyOddNumber(const vector<int> &nums) {
        int ans = 0;
        for (int i : nums) {
            ans ^= i;
        }
        return ans;
    }

public:
    // 2个数字出现了奇数次,其余数字出现了偶数次，找到出现奇数次的2个数字
    //[1,1,2,2,3,3,4,5]->4,5
    static pair<int, int> SearchTheTwoOddNumber(const vector<int> &nums) {
        // ����������������x,y
        int ans = 0;
        for (int i : nums) {
            ans ^= i;
        }
        // ans=x^y���ҵ�ans�����������ĵ�һ��Ϊ��1���ı���λ
        ans = ans & (~ans + 1); // x,y����һλһ����ͬ
        int x = 0, y = 0;
        for (int i : nums) {
            if (ans & i) { // ��ʾ��һλ�ǡ�1��
                x ^= i;
            } else {
                y ^= i;
            }
        }
        return {x, y};
    }
};