#pragma once
#include "Common.h"
class SizeClass {
public:
    // 计算size对齐后的大小
    static size_t RoundUp(size_t size) {
        if (size <= 128) {
            return RoundUpSubFunc(size, 8); //[1,128]->8字节对齐
        } else if (size <= 1024) {
            return RoundUpSubFunc(size, 16);
        } else if (size <= 8 * 1024) {
            return RoundUpSubFunc(size, 128);
        } else if (size <= 64 * 1024) {
            return RoundUpSubFunc(size, 1024);
        } else {
            return RoundUpSubFunc(size, 1 << PAGE_SHIFT); // 大于64KB,按照页(8KB)对齐
        }
        return -1;
    }
    // 计算在哪一个桶
    static size_t Index(size_t size) {
        static size_t groupArray[4] = {16, 56, 56, 56}; // 保存每一个区间桶的数目
        if (size <= 128) {
            return IndexSubFunc(size, 3); // 2^3=8
        } else if (size <= 1024) {
            // 2^4=16,16字节对齐
            return IndexSubFunc(size - 128, 4) + groupArray[0];
        } else if (size <= 8 * 1024) {
            return IndexSubFunc(size - 1024, 7) + groupArray[0] + groupArray[1];
        } else if (size <= 64 * 1024) {
            return IndexSubFunc(size - 8 * 1024, 10) + groupArray[0] + groupArray[1] + groupArray[2];
        } else if (size <= 256 * 1024) {
            return IndexSubFunc(size - 64 * 1024, 13) + groupArray[0] + groupArray[1] + groupArray[2] + groupArray[3];
        } else {
            assert(false);
            return -1;
        }
        return -1;
    }
    // threadcache一次向centralcache要多少个,取min(NumMoveSize,maxSize)
    static size_t NumMoveSize(size_t size) {
        assert(size > 0);
        size_t num = MAX_BYTES / size; // 最大个数
        if (num < 2) {
            return 2;
        }
        if (num > 512) {
            return 512;
        }
        return num;
    }
    // centralcache找pagecache要几页
    static size_t NumMovePage(size_t size) {
        size_t num = NumMoveSize(size); // 最大个数
        size_t nPage = num * size;      // 最大总大小
        nPage >>= PAGE_SHIFT;           // 页数
        if (nPage == 0) {
            nPage = 1;
        }
        return nPage;
    }
    static size_t RoundUpSubFunc(size_t size, size_t alignnum) {
        // return size % alignnum == 0 ? size : (size / alignnum + 1) * alignnum;//一般写法
        return ((size + alignnum - 1) & ~(alignnum - 1)); // 位运算
    }
    static size_t IndexSubFunc(size_t size, size_t alignnum_shift) {
        // 2^alignnum_shift=对齐数
        // return size % (size_t(pow(2, alignnum_shift))) == 0 ? size / (size_t(pow(2, alignnum_shift))) - 1 : size / (size_t(pow(2, alignnum_shift)));//一般写法
        // 位运算
        return ((size + (1 << alignnum_shift) - 1) >> alignnum_shift) - 1;
    }
};