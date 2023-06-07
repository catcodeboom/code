#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <time.h>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
inline bool operator==(const vector<int> &left, const vector<int> &right) {
    if (left.size() == right.size()) {
        int n = left.size();
        for (int i = 0; i < n; i++) {
            if (left[i] != right[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}
class Solution {
public:
    static void DispalyArray(vector<int> &nums) {
        cout << "====================================" << endl;
        auto n = nums.size();
        for (int i = 0; i < n; i++) {
            cout << nums[i] << ' ';
        }
        cout << endl;
    }
    static void BubbleSort(vector<int> &nums) {
        auto n = nums.size();
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < i; j++) {
                if (nums[j] > nums[j + 1]) {
                    std::swap(nums[j], nums[j + 1]);
                }
            }
        }
    }
    static void TimeBubbleSort(vector<int> &nums) {
        int begin = clock();
        BubbleSort(nums);
        int end = clock();
        cout << "BubbleSort cost time:" << end - begin << "ms" << endl;
    }
    static void SelectSort(vector<int> &nums) {
        size_t n = nums.size();
        int start = 0, end = n - 1;
        while (start < end) {
            int maxindex = end, minindex = start;
            for (int i = start; i <= end; i++) {
                minindex = nums[minindex] > nums[i] ? i : minindex;
                maxindex = nums[maxindex] < nums[i] ? i : maxindex;
            }
            std::swap(nums[minindex], nums[start]); // start位置可能是最大值
            maxindex = maxindex == start ? minindex : maxindex;
            std::swap(nums[maxindex], nums[end]);
            start++, end--;
        }
    }
    static void TimeSelectSort(vector<int> &nums) {
        int begin = clock();
        SelectSort(nums);
        int end = clock();
        cout << "SelectSort cost time:" << end - begin << "ms" << endl;
    }
    static void InsertSort(vector<int> &nums) {
        size_t n = nums.size();
        for (int i = 1; i < n; i++) { // i位置为要插入的元素
            for (int j = i - 1; j >= 0 && nums[j + 1] < nums[j]; j--) {
                std::swap(nums[j + 1], nums[j]);
            }
        }
    }
    static void TimeInsertSort(vector<int> &nums) {
        int begin = clock();
        InsertSort(nums);
        int end = clock();
        cout << "InsertSort cost time:" << end - begin << "ms" << endl;
    }
    static void ShellSort(vector<int> &nums) {
        size_t n = nums.size();
        for (int gap = n / 2; gap >= 1; gap /= 2) {     // gap表示步长
            for (int start = 0; start < gap; start++) { // start为每一组的开始
                for (int i = start + gap; i < n; i += gap) {
                    for (int j = i - gap; j >= 0 && nums[j + gap] < nums[j]; j -= gap) {
                        std::swap(nums[j + gap], nums[j]);
                    }
                }
            }
        }
    }
    static void TimeShellSort(vector<int> &nums) {
        int begin = clock();
        ShellSort(nums);
        int end = clock();
        cout << "ShellSort cost time:" << end - begin << "ms" << endl;
    }
    static void QuickSort(vector<int> &nums) {
        size_t n = nums.size();
        auto partition = [&](int left, int right) {
            // 三数取中
            int mid = left + ((right - left) >> 1);
            if ((nums[mid] >= nums[left] && nums[mid] <= nums[right]) || (nums[mid] <= nums[left] && nums[mid] >= nums[right])) {
                std::swap(nums[mid], nums[left]);
            } else if ((nums[right] >= nums[left] && nums[right] <= nums[mid]) || (nums[right] <= nums[left] && nums[right] >= nums[mid])) {
                std::swap(nums[right], nums[left]);
            }
            int base = nums[left]; // 基准值
            int i = left, j = i + 1;
            while (j <= right) {
                if (nums[j] < base && ++i != j) {
                    std::swap(nums[i], nums[j]);
                }
                j++;
            }
            std::swap(nums[i], nums[left]);
            return i;
        };
        std::list<int> st;
        st.push_back(n - 1);
        st.push_back(0);
        while (!st.empty()) {
            int left = st.back();
            st.pop_back();
            int right = st.back();
            st.pop_back();
            int div = partition(left, right);
            if (div + 1 < right) {
                st.push_back(right);
                st.push_back(div + 1);
            }
            if (left < div - 1) {
                st.push_back(div - 1);
                st.push_back(left);
            }
        }
    }
    static void TimeQuickSort(vector<int> &nums) {
        int begin = clock();
        QuickSort(nums);
        int end = clock();
        cout << "QuickSort cost time:" << end - begin << "ms" << endl;
    }
    static void MergeSort(vector<int> &nums) {
        int n = nums.size();
        vector<int> help(n);
        auto merge = [&](int left, int mid, int right) {
            //[left,mid] [mid+1,right]
            int i = left, j = mid + 1, start = left;
            while (i <= mid && j <= right) {
                help[start++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
            }
            while (i <= mid) {
                help[start++] = nums[i++];
            }
            while (j <= right) {
                help[start++] = nums[j++];
            }
            for (int k = left; k <= right; k++) {
                nums[k] = help[k];
            }
        };
        for (int gap = 1; gap < n; gap *= 2) { // gap个与gap个进行归并
            for (int left = 0; left < n; left += 2 * gap) {
                merge(left, std::min(n - 1, left + gap), std::min(left + 2 * gap - 1, n - 1));
            }
        }
    }
    static void TimeMergeSort(vector<int> &nums) {
        int begin = clock();
        MergeSort(nums);
        int end = clock();
        cout << "MergeSort cost time:" << end - begin << "ms" << endl;
    }
    static void HeapSort(vector<int> &nums) {
        auto heapify = [&](int start, int size) {
            int left = start * 2 + 1, right = left + 1;
            while (left < size) {
                int index = right < size && nums[right] > nums[left] ? right : left;
                if (nums[index] <= nums[start]) {
                    break;
                }
                std::swap(nums[index], nums[start]);
                start = index;
                left = start * 2 + 1, right = left + 1;
            }
        };
        for (int i = nums.size() / 2 - 1; i >= 0; i--) {
            heapify(i, nums.size()); // 大堆
        }
        for (int size = nums.size() - 1; size > 0; size--) {
            std::swap(nums[0], nums[size]);
            heapify(0, size);
        }
    }
    static void TimeHeapSort(vector<int> &nums) {
        int begin = clock();
        HeapSort(nums);
        int end = clock();
        cout << "HeapSort cost time:" << end - begin << "ms" << endl;
    }
};