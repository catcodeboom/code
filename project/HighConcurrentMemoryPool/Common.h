#pragma once
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#ifdef __unix__
#include <pthread.h>
#endif
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::mutex;
using std::thread;
using std::bad_alloc;
static const size_t MAX_BYTES = 256 * 1024; // 可向线程缓存申请的最大内存
static const size_t NFREELISTS = 208;       // threadcache和centralcache中哈希桶的个数
static const size_t NPAGES = 129;           // pagecache中哈希桶的大小
static const size_t PAGE_SHIFT = 13;        // 2^13=8KB
