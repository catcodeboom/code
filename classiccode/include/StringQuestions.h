#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<functional>
using std::unordered_map;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::function;
class Solution {
public:
	//leetcode�ַ�ƥ��
	static bool wordPattern(string pattern, string s) {
		//����
		unordered_map<char, string> charmap;
		unordered_map<string, char> strmap;
		int i = 0, j = 0, len = 0, patternlen = pattern.size(), slen = s.size();
		while (i < patternlen && j < slen) {
			char cur = pattern[i++];
			int prev = j;
			while (j < slen && isalpha(s[j])) {
				j++;
				len++;
			}
			if (j < slen) {
				j++;//������һ������
			}
			string str = s.substr(prev, len);
			len = 0;//������һ��
			if (charmap.count(cur)) {
				if (charmap[cur] != str) {
					return false;
				}
			}
			else {
				charmap[cur] = str;
			}
			if (strmap.count(str) == 0) {
				strmap[str] = cur;
			}
			else {
				if (strmap[str] != cur) {
					return false;
				}
			}
			if ((i == patternlen && j < slen) || (i < patternlen && j == slen)) {
				return false;
			}
		}
		return true;
	}
public:
	//��ӡһ���ַ���������"������"
	static void DisplaySubsequence(string str) {
		int n = str.size();
		//����ÿһ��λ�ã����ǿ�ѡ�ɲ�ѡ
		function<void(int)> f = [&](int cur) {
			//cur��ʾ��ǰ�����ߵ�λ��
			if (cur == n) {
				for (char c : str) {
					if (c) {
						cout << c;
					}
				}
				cout << endl;
				return;
			}
			char temp = str[cur];
			str[cur] = 0;//��ѡ��ǰλ��
			f(cur + 1);
			str[cur] = temp;
			f(cur + 1);//ѡ��ǰλ��
		};
		f(0);
	}
public:
	static int KMP(string str1,string str2) {
		int len1 = str1.size(), len2 = str2.size();
		if (len1 < len2) {
			return -1;
		}
		auto getNextArray = [](const string& str) {
			vector<int> next(str.size());
			next[0] = -1;
			if (next.size() == 1) {
				return next;
			}
			next[1] = 0;
			for (int i = 2; i < next.size(); i++) {
				char comp = str[i - 1];//��Ҫ�Ƚϵ��ַ�
				int pos = next[i - 1];//��ǰ�Ƚϵ�λ��
				while (pos != -1 && str[pos] != comp) {
					pos = next[pos];
				}
				if (pos == -1) {
					next[i] = 0;
				}
				else {
					next[i] = pos + 1;
				}
			}
			return next;
		};
		vector<int> next = getNextArray(str2);
		int i = 0, j = 0;
		while (i < len1 && j < len2) {
			if (str1[i] == str2[j]) {
				i++, j++;
			}
			else {
				j = next[j];
				if (j == -1) {
					i++, j++;
				}
			}
		}
		return j == len2 ? i - j : -1;
	}
};