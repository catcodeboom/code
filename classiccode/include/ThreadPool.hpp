#pragma once
#include <condition_variable>
#include <functional>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
namespace threadpool {
    template <class Task>
    class ThreadPool {
    public:
        ThreadPool(int cnt = 20) {
            for (int i = 0; i < 20; i++) {
                std::thread tmp(std::bind(&ThreadPool<Task>::Entrance, this, i + 1 /*线程编号*/)); // 通过std::bind让线程调用普通成员函数
                tmp.detach();
            }
        }
        void push_tack(Task *task) {
            std::unique_lock<std::mutex> ulock(mtx); // 加锁
            tasks.push_back(task);
            cv.notify_one();                         // 唤醒一个阻塞在条件变量上的线程,表示有任务
        }

    private:
        void Entrance(int num) {
            mapmtx.lock();
            namemap[pthread_self()] = string("线程") + std::to_string(num);
            mapmtx.unlock();
            while (1) {
                // 取任务
                std::unique_lock<std::mutex> ulock(mtx);             // 先进行加锁
                cv.wait(ulock, [this] { return tasks.size() > 0; }); // 一直等到条件成立
                Task *task = tasks.back();
                tasks.pop_back();
                cout << namemap[pthread_self()] << "拿到任务" << endl;
                ulock.unlock(); // 解锁,已经拿到任务了,直接执行
                (*task)();
                delete task;
            }
        }

    private:
        std::mutex mapmtx;                     // 专为namemap服务的锁
        unordered_map<size_t, string> namemap; // 记录线程的tid和线程名
        std::list<Task *> tasks;               // 存放任务
        std::mutex mtx;
        std::condition_variable cv;
    };

    class Solution {
        struct Task {
            void operator()() const {
                cout << "测试" << endl;
            }
        };

    public:
        static void TestThreadPool() {
            ThreadPool<Task> pool;
            int num = 1000;
            for (int i = 0; i < num; i++) {
                pool.push_tack(new Task);
            }
        }
    };
} // namespace threadpool