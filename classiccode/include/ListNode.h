#pragma once
#include<iostream>
using std::cout;
using std::endl;
struct ListNode {
	ListNode* next=nullptr;
	int val=0;
	ListNode(int v = 0) :val(v) {}
};
class Solution {
public:
	static void DisplayList(ListNode* head) {
		while (head) {
			cout << head->val << ' ';
			head = head->next;
		}
		cout << endl;
		cout << "==========================" << endl;
		fflush(stdout);
	}
	static ListNode* InsertSort(ListNode* head) {
		//������в�������
		if (head == nullptr || head->next == nullptr) {
			return head;
		}
		ListNode* start = head, * end = head;//�Ѿ����������
		ListNode* insertnode = head->next;//������Ľڵ�
		while (insertnode) {
			ListNode* next = insertnode->next;//������һ��������Ľڵ�
			//���в������
			if (insertnode->val <= start->val) {
				insertnode->next = start;
				start = insertnode;
			}
			else {//insertnode->val > start->val				
				ListNode* index = start, * prev = start;
				while (index != end && insertnode->val > index->val) {
					prev = index;
					index = index->next;
				}
				if (index == end && insertnode->val > end->val) {
					end->next = insertnode;
					end = insertnode;
				}
				else {
					prev->next = insertnode;
					insertnode->next = index;
				}
			}
			//����
			insertnode = next;
		}
		end->next = nullptr;
		return start;
	}
};