#include "ConcurrentAlloc.h"
#include <vector>
#include <thread>
#include <atomic>
#include <string>
using std::string;
using std::atomic;
using std::vector;
using std::thread;
const int _round = 10;  // 轮数
const int _num = 10000; // 一轮的次数
void BenchMark(size_t threadnum, string flag) {
    atomic<size_t> apply_time = {0};
    atomic<size_t> delete_time = {0};
    auto f = [&] {
        vector<void *> v(_num);
        size_t begin = 0;
        size_t end = 0;
        for (size_t i = 0; i < _round; i++) {
            begin = clock();
            for (size_t j = 0; j < _num; j++) {
                v[j] = flag == "malloc" ? malloc(rand() % (256 * 8 * 1024) + 1) : ConcurrentAlloc(rand() % (256 * 8 * 1024) + 1);
            }
            end = clock();
            apply_time += end - begin;
            begin = clock();
            for (size_t j = 0; j < _num; j++) {
                flag == "malloc" ? free(v[j]) : ConcurrentFree(v[j]);
                cout << j << endl;
            }
            end = clock();
            delete_time += end - begin;
        }
    };
    vector<thread> vthread(threadnum);
    for (auto &t : vthread) {
        t = thread(f);
    }
    for (auto &t : vthread) {
        t.join();
    }
    cout << flag << " apply time is " << apply_time << endl;
    cout << flag << " delete time is " << delete_time << endl;
    cout << flag << " total time is " << apply_time + delete_time << endl;
}
int main() {
    srand((unsigned int)time(nullptr));
    const int n = 200000;
    vector<void *> v(n);
    // for (size_t i = 0; i < n; i++) {
    //     v[i] = ConcurrentAlloc(1024 + 1);
    //     // cout << i << endl;
    // }
    // for (size_t i = 0; i < n; i++) {
    //     ConcurrentFree(v[i]);
    //     // cout << i << endl;
    // }
    // cout << "success" << endl;
    // BenchMark(4, "malloc");
    BenchMark(1, "concurrentalloc");
    // BenchMarkMalloc(1000, 20, 5);
    /*try
    {
        BenchMarkConcurrentAlloc(100, 10, 200);
    }
    catch (...)
    {
        cout << "Unknown error" << endl;
    }
    const int x = 10000;*/
    /*vector<std::pair<void*, size_t>> v(x);
    ThreadCache t;
    for (size_t i = 0; i < x; i++)
    {
        int size = rand() % (256 * 1024) + 1;
        v[i] = { t.Alloc(size),size };
        cout << i << endl;
    }
    for (size_t i = 0; i < x; i++)
    {
        t.DeAlloc(v[i].first, v[i].second);
        cout << i << endl;
    }*/
    // 大于256KB
    // ThreadCache t;
    // void *p1 = ConcurrentAlloc(259 * 1024);
    // ConcurrentFree(p1);
    // void *p2 = ConcurrentAlloc(129 * 8 * 1024);
    // ConcurrentFree(p2);
    return 0;
}