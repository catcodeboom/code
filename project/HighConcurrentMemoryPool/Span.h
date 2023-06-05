#pragma once
#include "FreeList.h"
#include "ObjectPool.hpp"
#include <mutex>
using std::mutex;
// #include "ObjectPool.hpp"
#ifdef _WIN64
typedef unsigned long long PAGE_ID;
#elif _WIN32
typedef unsigned int PAGE_ID;
#elif __x86_64__
typedef unsigned long long PAGE_ID;
#elif __unix__
typedef unsigned int PAGE_ID;
#else
typedef unsigned long long PAGE_ID;
#endif
// 管理以页为单位的大块内存
struct Span {
    PAGE_ID _pageId = 0; // 大块内存起始页的页号
    size_t _n = 0;       // 页的数量

    Span *_next = nullptr; // 双链表结构
    Span *_prev = nullptr;

    size_t _objSize = 0;       // 切好的小对象的大小
    size_t _useCount = 0;      // 切好的小块内存，被分配给thread cache的计数
    void *_freeList = nullptr; // 切好的小块内存的自由链表

    bool _isUse = false; // 是否在被使用
};

// 带头双向循环链表
class SpanList {
public:
    SpanList() {
        //_head = new Span;
        _head = _spanPool.New();
        _head->_next = _head;
        _head->_prev = _head;
    }
    Span *Begin() {
        return _head->_next;
    }
    Span *End() {
        return _head;
    }
    bool Empty() {
        return _head == _head->_next;
    }
    void PushFront(Span *span) {
        Insert(Begin(), span);
    }
    Span *PopFront() {
        Span *front = _head->_next;
        Erase(front);
        return front;
    }
    void Insert(Span *pos, Span *newSpan) {
        assert(pos);
        assert(newSpan);

        Span *prev = pos->_prev;

        prev->_next = newSpan;
        newSpan->_prev = prev;

        newSpan->_next = pos;
        pos->_prev = newSpan;
    }
    void Erase(Span *pos) {
        assert(pos);
        assert(pos != _head); // 不能删除哨兵位的头结点

        // if (pos == _head)
        //{
        //	int x = 0;
        // }

        Span *prev = pos->_prev;
        Span *next = pos->_next;

        prev->_next = next;
        next->_prev = prev;
    }

private:
    Span *_head;
    static ObjectPool<Span> _spanPool;

public:
    std::mutex _mtx; // 桶锁
};