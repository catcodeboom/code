#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<cassert>
#include<list>
#include<functional>
using std::cout;
using std::endl;
using std::function;
using std::unordered_map;
using std::string;
//ǰ׺��
struct TrieNode {
	int pass = 0;//�����ڵ���ַ�������
	int end = 0;//�Ըýڵ�Ϊ��β���ַ���������
	unordered_map<char, TrieNode*> hashmap;//��¼��һ��
};
class Trie {
public:
	Trie() {
		root = new TrieNode;
	}
	~Trie() {
		if (!root) {
			return;
		}
		Delete(root);
		root = nullptr;
	}
	void insert(string word) {
		int n = word.size();
		root->pass++;
		if (n == 0) {
			root->end++;
			return;//��ʾword�ǿմ�
		}
		int index = 0;
		TrieNode* node = root;
		while (index < n) {
			char cur = word[index++];
			if (node->hashmap.count(cur) == 0) {
				node->hashmap[cur] = new TrieNode;
			}
			node = node->hashmap[cur];
			node->pass++;
		}
		node->end++;
	}
	bool search(string word) {
		TrieNode* node = root;
		int n = word.size();
		int index = 0;
		while (index < n) {
			char cur = word[index++];
			if (node->hashmap.count(cur) == 0) {
				return false;
			}
			node = node->hashmap[cur];
		}
		return node->end;
	}
	bool startsWith(string prefix) {
		TrieNode* node = root;
		int n = prefix.size();
		int index = 0;
		while (index < n) {
			char cur = prefix[index++];
			if (node->hashmap.count(cur) == 0) {
				return false;
			}
			node = node->hashmap[cur];
		}
		return true;
	}
	bool erase(string str) {
		if (search(str) == false) {
			return false;
		}
		int n = str.size();
		int index = 0;
		TrieNode* node = root;
		node->pass--;
		if (node->pass == 0) {
			Delete(node);//���ҽ���һ��·
			return true;
		}
		while (index < n) {
			char cur = str[index++];
			assert(node->hashmap.count(cur) != 0);
			node = node->hashmap[cur];
			node->pass--;
			if (node->pass == 0) {
				Delete(node);//���ҽ���һ��·
				return true;
			}
		}
		node->end--;
		return true;
	}
private:
	//ctrl + shift + F9 ������жϵ�
	void Delete(TrieNode* node) {//��node�������µ����нڵ㶼ɾ��
		if (node == nullptr) {
			return;
		}
		if (node->hashmap.size() == 0) {
			delete node;
			node = nullptr;
			return;
		}
		for (auto [c, n] : node->hashmap) {
			Delete(n);
		}
		delete node;
		node = nullptr;
	}
private:
	TrieNode* root = nullptr;
};
class Solution {
public:
	static void TestInsert() {
		Trie prefix;
		std::list<std::string> strs{"abcd", "abc", "abcde", "bcedf"};
		for (const string& s : strs) {
			prefix.insert(s);
		}
		for (const string& s : strs) {
			cout << (prefix.search(s) ? "true" : "false") << endl;
		}
	}
	static void TestErase() {
		Trie prefix;
		std::list<std::string> strs{"abcd", "abc", "abcde", "bcedf"};
		for (const string& s : strs) {
			prefix.insert(s);
		}
		prefix.erase("abc");
		for (const string& s : strs) {
			cout << (prefix.search(s) ? "true" : "false") << endl;
		}
		cout << (prefix.startsWith("abcd") ? "true" : "false") << endl;		
	}
};