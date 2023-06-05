#pragma once
#include "Common.h"
#include "FreeList.h"
#include "System.h"
template <class T>
class ObjectPool {
public:
    T *New() {
        T *ans = nullptr;
        if (_freeList != nullptr) {
            ans = reinterpret_cast<T *>(_freeList);
            _freeList = NextObj(_freeList);
            new (ans) T; // 显示调用构造函数
            return ans;
        }
        size_t size = max(sizeof(void *), sizeof(T));
        if (_remainBytes < size) {
            _memory = static_cast<char *>(SystemAlloc(NPAGES - 1)); // 向OS申请128页
            _remainBytes = (NPAGES - 1) << PAGE_SHIFT;
        }
        ans = reinterpret_cast<T *>(_memory);
        _memory += size;
        _remainBytes -= size;
        new (ans) T;
        return ans;
    }
    void Delete(T *obj) {
        assert(obj);
        obj->~T(); // 析构函数
        NextObj(obj) = _freeList;
        _freeList = obj;
    }

private:
    void *_freeList = nullptr;
    char *_memory = nullptr;
    size_t _remainBytes = 0;
};