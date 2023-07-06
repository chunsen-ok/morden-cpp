#ifndef MCPP_SORT_HPP
#define MCPP_SORT_HPP

#include <iostream>

namespace mcpp {

template<typename ForwardIt>
void swap(ForwardIt it1, ForwardIt it2)
{
    auto tmp = *it1;
    *it1 = *it2;
    *it2 = tmp;
}

// 插入排序：将待排序序列的第一个元素放到有序序列的适当位置。
// 稳定性：稳定
// 时间复杂度：O(n^2)
template <typename BidirectionIt>
void insertion_sort(BidirectionIt begin, BidirectionIt end)
{
    BidirectionIt it = begin;
    for (++it; it != end; ++it)
    {
        for (BidirectionIt it2 = it; it2 != begin; --it2)
        {
            BidirectionIt it1 = it2;
            --it1;
            if (*it2 < *it1)
            {
                mcpp::swap(it1, it2);
            }
            else
            {
                break;
            }
        }
    }
}

// 选择排序：从待排序序列找出最小的元素，放到有序序列尾。
// 稳定性：不稳定
// 时间复杂度：O(n^2)
template<typename ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end) {
    for (ForwardIt it = begin; it != end; ++it) {
        ForwardIt it2 = it;
        for (++it2; it2 != end; ++it2)
        {
            if (*it2 < *it) {
                mcpp::swap(it, it2);
            }
        }
    }
}

// 冒泡排序：从待排序序列底部开始查找，依次将最小的元素交换到待排序序列顶部，也就是有序序列的底部。
// 稳定性：稳定
// 时间复杂度：O(n^2)
template <typename BidirectionIt>
void bubble_sort(BidirectionIt begin, BidirectionIt end)
{
    for (; begin != end; ++begin) {
        BidirectionIt it2 = end;
        for (--it2; it2 != begin; --it2) {
            BidirectionIt it1 = it2;
            --it1;
            if (*it2 < *it1) {
                mcpp::swap(it1, it2);
            }
        }
    }
}

// 希尔排序：每趟排序，对元素按照一个增量进行分组；每个分组分别进行插入排序。每趟的增量为上一次的一半，直至增量为1，排序完成。
// 稳定性：不稳定
template<typename RandomAccessIt>
void shell_sort(RandomAccessIt begin, RandomAccessIt end) {
    for (auto inc = std::distance(begin, end) / 2; inc >= 1; inc /= 2) {
        for (auto g = 0; g <= inc; ++g) {
            for (auto i = begin + g; i < end; i += inc) {
                for (auto j = i + inc; begin < j && j < end;) {
                    auto prev = j - inc;
                    if (begin <= prev && *prev > *j) {
                        mcpp::swap(prev, j);
                        j = prev;
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

// 归并排序：拆分成子序列，对子序列进行排序，然后合并子序列。
template<typename RandomAccessIt>
void mege_sort(RandomAccessIt begin, RandomAccessIt end) {
    // ...
}

// 快速排序：选取一个基准值，将序列中比它小的放到左边，比它大的放到右边。
// 快速排序是冒泡排序的一种改进。基准值可以是任意位置的元素。在比较的时候从序列的两侧开始，左侧索引指向元素比基准值大，则两者交换位置；右侧索引指向元素比基准值小，则交换位置。
// 直到两侧索引相遇，一趟排序完成。
// 注意：下标移动的条件
template <typename RandomAccessIt>
void qsort(RandomAccessIt begin, RandomAccessIt end) {
    auto base = begin;
    for (auto left = begin + 1, right = end - 1; left <= right; ) {
        if ((left < base && *left > *base) || (left > base && *left < *base)) {
            mcpp::swap(left, base);
            base = left;
            ++left;
        } else if (left < base && *left <= *base) {
            ++left;
        }

        if ((right < base && *right > *base) || (right > base && *right < *base)) {
            mcpp::swap(base, right);
            base = right;
            --right;
        } else if (right > base && *right >= *base) {
            --right;
        }
    }

    if (begin < base) {
        qsort(begin, base);
    }

    ++base;
    if (base < end) {
        qsort(base, end);
    }
}

}

#endif
