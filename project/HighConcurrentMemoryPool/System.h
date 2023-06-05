#pragma once
#include "Common.h"
#ifdef __unix__
#include <sys/mman.h>
#include <unistd.h>
#endif
#ifdef _WIN32
#include <Windows.h>
#endif
inline static void *SystemAlloc(size_t kpage) {
    void *ptr = nullptr;
#ifdef _WIN32
    ptr = VirtualAlloc(0, kpage << PAGE_SHIFT, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (ptr == nullptr) {
        throw std::bad_alloc();
    }
#endif
#ifdef __unix__
    ptr = mmap(NULL, kpage << PAGE_SHIFT, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        throw bad_alloc();
    }
#endif
    return ptr;
}
inline static void SystemFree(void *ptr, size_t size) {
#ifdef _WIN32
    VirtualFree(ptr, 0, MEM_RELEASE); // windows下不需要大小
#endif
#ifdef __unix__
    munmap(ptr, size); // 使用munmap直接向OS释放内存
#endif
}
