#pragma once
#include <cassert>
#include <cstdio>
#include <stdlib.h>
static inline void *&NextObj(void *obj) {
    return *(void **)obj;
}
// 管理切分好的小对象的自由链表
class FreeList {
public:
    // 将释放的对象头插到自由链表
    void Push(void *obj) {
        assert(obj);

        // 头插
        NextObj(obj) = _freeList;
        _freeList = obj;
        _size++;
    }
    // 从自由链表头部获取一个对象
    void *Pop() {
        assert(_freeList);

        // 头删
        void *obj = _freeList;
        _freeList = NextObj(_freeList);
        _size--;

        return obj;
    }
    // 插入一段范围的对象到自由链表
    void PushRange(void *start, void *end, size_t n) {
        assert(start);
        assert(end);

        // 头插
        NextObj(end) = _freeList;
        _freeList = start;
        _size += n;
    }
    // 从自由链表获取一段范围的对象
    void PopRange(void *&start, void *&end, size_t n) {
        assert(n <= _size);

        // 头删
        start = _freeList;
        end = start;
        for (size_t i = 0; i < n - 1; i++) {
            end = NextObj(end);
        }
        _freeList = NextObj(end); // 自由链表指向end的下一个对象
        NextObj(end) = nullptr;   // 取出的一段链表的表尾置空
        _size -= n;
    }
    bool Empty() {
        return _freeList == nullptr;
    }

    size_t &MaxSize() {
        return _maxSize;
    }

    size_t Size() {
        return _size;
    }

private:
    void *_freeList = nullptr; // 自由链表
    size_t _maxSize = 1;
    size_t _size = 0;
};