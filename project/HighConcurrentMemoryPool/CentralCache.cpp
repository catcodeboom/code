#include "CentralCache.h"
#include "PageCache.h"

CentralCache CentralCache::_sInst;
ObjectPool<Span> SpanList::_spanPool;

// 从特定的哈希桶中取出一定数量的内存
size_t CentralCache::FetchRangeObj(void *&start, void *&end, size_t n, size_t size) {
    size_t index = SizeClass::Index(size);
    _spanLists[index]._mtx.lock(); // 桶锁

    // 找到一个非空的span
    Span *span = GetOneSpan(_spanLists[index], size);
    assert(span);
    assert(span->_freeList); // 是一个有效的span

    // 从span中取内存块
    start = span->_freeList;
    end = span->_freeList;
    size_t actualNum = 1;
    while (NextObj(end) && n - 1) {
        end = NextObj(end);
        actualNum++;
        n--;
    }
    span->_freeList = NextObj(end);
    NextObj(end) = nullptr;
    span->_useCount += actualNum; // 更新_usecnt

    _spanLists[index]._mtx.unlock(); // 解锁
    return actualNum;
}

// 获取一个非空的span
Span *CentralCache::GetOneSpan(SpanList &spanList, size_t size) {
    // 遍历查找
    Span *it = spanList.Begin();
    while (it != spanList.End()) {
        if (it->_freeList != nullptr) {
            return it;
        } else {
            it = it->_next;
        }
    }
    // 可解锁，此时其他的thread cache可归还内存
    spanList._mtx.unlock();
    PageCache::GetInstance()->_pageMtx.lock();
    // 向pagecache申请一个span
    Span *span = PageCache::GetInstance()->NewSpan(SizeClass::NumMovePage(size));
    span->_isUse = true;
    span->_objSize = size; //
    PageCache::GetInstance()->_pageMtx.unlock();

    // 将span进行切分
    char *start = (char *)(span->_pageId << PAGE_SHIFT);
    size_t bytes = span->_n << PAGE_SHIFT;

    // 进行尾插，内存在物理上连续，提高CPU缓存命中率
    char *end = start + bytes;

    span->_freeList = start;
    start += size;
    void *tail = span->_freeList;

    while (start < end) {
        NextObj(tail) = start;
        tail = NextObj(tail);
        start += size;
    }
    NextObj(tail) = nullptr; // 将结尾置为空

    spanList._mtx.lock();
    spanList.PushFront(span);

    return span;
}

// 将小块内存归还给span
void CentralCache::ReleaseListToSpans(void *start, size_t size) {
    size_t index = SizeClass::Index(size);
    _spanLists[index]._mtx.lock(); // 加桶锁
    while (start) {
        void *next = NextObj(start); // 保存下一个内存块的地址
        Span *span = PageCache::GetInstance()->MapObjectToSpan(start);
        // 映射到span
        NextObj(start) = span->_freeList;
        span->_freeList = start;

        span->_useCount--;          // 更新_usecnt
        if (span->_useCount == 0) { // 还给PageCache

            _spanLists[index].Erase(span); // 移除span
            span->_freeList = nullptr;
            span->_next = nullptr;
            span->_prev = nullptr;
            // 可解锁，此时span已经不属于CentralCache
            _spanLists[index]._mtx.unlock();
            PageCache::GetInstance()->_pageMtx.lock();
            PageCache::GetInstance()->ReleaseSpanToPageCache(span);
            PageCache::GetInstance()->_pageMtx.unlock();
            _spanLists[index]._mtx.lock();
        }

        start = next;
    }

    _spanLists[index]._mtx.unlock(); // while循环结束解锁
}