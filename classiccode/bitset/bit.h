#pragma once
#include <bitset>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
using std::cout;
using std::endl;
using std::string;
namespace mybit {

    template <size_t N>
    class bitset {
    public:
        bitset() :
            array(new char[N / 8 + 1]{0}) {
        }
        bitset(string one_zero) :
            bitset() {
            assert(one_zero.size() <= N);
            for (size_t i = 0; i < one_zero.size(); i++) {
                assert(one_zero[i] == '0' || one_zero[i] == '1');
                set(i, one_zero[i] - '0');
            }
        }
        bitset(size_t num) :
            bitset() {
            for (int i = 0; i < N; i++) {
                if (num & (1 << i)) {
                    set(i);
                }
            }
        }
        ~bitset() {
            delete[] array;
        }
        void set() const {
            for (int i = 0; i < N; i++) {
                set(i);
            }
        }
        void set(size_t pos, bool flag = true) const {
            assert(pos >= 0 && pos <= N);
            int index = pos / 8;
            int offset = pos % 8;
            if (flag) {
                array[index] |= (1 << offset);
            } else {
                array[index] &= (~(1 << offset));
            }
        }
        bool operator[](size_t pos) const {
            assert(pos >= 0 && pos <= N);
            int index = pos / 8;
            int offset = pos % 8;
            return array[index] & (1 << offset);
        }
        size_t size() const {
            return N;
        }
        bool test(size_t pos) const {
            return (*this)[pos];
        }
        bool any() const { // 是否存在一个比特位为1
            for (int i = 0; i < N; i++) {
                if (test(i)) {
                    return true;
                }
            }
            return false;
        }
        bool none() const { // 是否所有的比特位都没有被设置
            return !any();
        }
        bool all() const { // 是否所有的比特位都被设置
            for (int i = 0; i < N; i++) {
                if (!test(i)) {
                    return false;
                }
            }
            return true;
        }
        void reset() const { // 将所有的比特位置为0
            for (size_t i = 0; i < N; i++) {
                reset(i);
            }
        }
        size_t count() const { // 统计有多少个为1的比特位
            size_t ans = 0;
            for (size_t i = 0; i < N; i++) {
                if (test(i)) {
                    ans++;
                }
            }
            return ans;
        }
        void reset(size_t pos) const { // 将一个比特位置为0
            set(pos, false);
        }
        void flip(size_t pos) const {
            // 翻转一个比特位
            if (test(pos)) {
                set(pos, false);
            } else {
                set(pos);
            }
        }
        void flip() const {
            // 翻转所有比特位
            for (size_t i = 0; i < N; i++) {
                flip(i);
            }
        }
        string to_string() const {
            string ans;
            for (size_t i = 0; i < N; i++) {
                ans += test(i) ? '1' : '0';
            }
            return ans;
        }
        bitset(const bitset<N> &b) {
            cout << "调用了拷贝构造函数" << endl;
        }
        unsigned long to_ulong();
        unsigned long long to_ullong();

    private:
        char *array;
    };
    template <size_t N>
    std::ostream &operator<<(std::ostream &cout, const mybit::bitset<N> &b) {
        return cout << b.to_string();
    }
    class Solution {
    public:
        static void Testbitset() {
            std::unique_ptr<std::bitset<15>> ubit(new std::bitset<15>("100010101000111"));
            cout << "位图大小:" << ubit->size() << endl;
            ubit->set(7, true);
            cout << "位图的第7个比特位:" << ubit->test(7) << endl;
            cout << "位图中有" << ubit->count() << "个为1的比特位" << endl;
            if (ubit->any()) {
                cout << "位图中存在一个位被设置为1" << endl;
            }
            if (ubit->none()) {
                cout << "位图中的所有位均被设置为0" << endl;
            }
            if (ubit->all()) {
                cout << "位图中所有位均被设置为1" << endl;
            }
            cout << "位图的第10个比特位是" << (*ubit)[10] << endl;
            ubit->reset(1);               // 将第一个比特位置为0
            cout << *ubit << endl;
            ubit->reset();                // 将所有比特位置为0
            cout << *ubit << endl;
            ubit->flip();                 // 翻转所有比特位
            cout << *ubit << endl;
            ubit->flip(0);                // 翻转第0个比特位
            cout << *ubit << endl;
            auto str = ubit->to_string(); // 转化为字符串
            // to_ulong,to_ullong
        }
        static void TestMybitset() {
            std::unique_ptr<mybit::bitset<15>> ubit(new mybit::bitset<15>("100010101000111"));
            cout << "位图大小:" << ubit->size() << endl;
            ubit->set(7, true);
            cout << "位图的第7个比特位:" << ubit->test(7) << endl;
            cout << "位图中有" << ubit->count() << "个为1的比特位" << endl;
            if (ubit->any()) {
                cout << "位图中存在一个位被设置为1" << endl;
            }
            if (ubit->none()) {
                cout << "位图中的所有位均被设置为0" << endl;
            }
            if (ubit->all()) {
                cout << "位图中所有位均被设置为1" << endl;
            }
            cout << "位图的第10个比特位是" << (*ubit)[10] << endl;
            ubit->reset(1);               // 将第一个比特位置为0
            cout << *ubit << endl;
            ubit->reset();                // 将所有比特位置为0
            cout << *ubit << endl;
            ubit->flip();                 // 翻转所有比特位
            cout << *ubit << endl;
            ubit->flip(0);                // 翻转第0个比特位
            cout << *ubit << endl;
            auto str = ubit->to_string(); // 转化为字符串
            // to_ulong,to_ullong
        }
    };
} // namespace mybit
