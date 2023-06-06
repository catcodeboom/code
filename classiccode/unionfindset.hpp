#pragma once
#include<unordered_map>
#include<list>
#include<initializer_list>
using std::initializer_list;
using std::unordered_map;
template<class T>
class UnionFindSet {
public:
	template<class Iter>
	UnionFindSet(Iter begin, Iter end) {
		while (begin != end) {
			fathermap[*begin] = *begin;
			sizemap[*begin] = 1;
			begin++;
		}
	}
	UnionFindSet(initializer_list<T> elems) {
		for (auto elem : elems) {
			fathermap[elem] = elem;
			sizemap[elem] = 1;
		}
	}
	void Union(const T& left, const T& right) {
		if (IsExist(left) && IsExist(right)) {
			auto big = FindTop(left);
			auto small= FindTop(right);
			if (big!=small) {
				if (sizemap[big] < sizemap[small]) {
					std::swap(big, small);
				}
				fathermap[small] = big;
				sizemap[big] += sizemap[small];
				sizemap.erase(small);
			}
		}
	}
	bool IsSameSet(const T& left, const T& right) {
		if (IsExist(left) && IsExist(right)) {
			return FindTop(left) == FindTop(right);
		}
		return false;
	}
	int getSetSize(const T& elem) {
		if (!IsExist(elem)) {
			return 0;
		}
		return sizemap[FindTop(elem)];
	}
private:
	bool IsExist(const T& elem) {
		return fathermap.count(elem);
	}
	T FindTop(T elem) {
		std::list<T> elems;
		while (elem != fathermap[elem]) {
			elems.push_back(elem);
			elem = fathermap[elem];
		}
		while (!elems.empty()) {
			fathermap[elems.back()] = elem;
			elems.pop_back();
		}
		return elem;
	}
private:
	unordered_map<T, T> fathermap;
	unordered_map<T, int> sizemap;//记录每一个集合中元素的个数
};