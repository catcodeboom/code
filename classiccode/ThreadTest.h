#pragma once
#include<iostream>
#include<thread>
#include<mutex>
using std::thread;
using std::cout;
using std::endl;
using std::mutex;
static thread_local int t_num=0;
static int num=0;
static mutex mtx;
class ThreadTest {
public:
	static void TestThreadLocal() {
		auto f = [] {
			mtx.lock();
			t_num++;
			cout << "t_num=" << t_num << endl;
			cout << "&t_num=" << &t_num << endl;
			num++;
			cout << "num=" << num << endl;
			cout << "&num=" << &num << endl;
			cout << "==================================" << endl;
			mtx.unlock();
		};
		thread t[10];
		for (int i = 0; i < 10; i++) {
			t[i] = thread(f);
		}
		for (int i = 0; i < 10; i++) {
			t[i].join();
		}
	}
};