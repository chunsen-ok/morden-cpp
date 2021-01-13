#ifndef MCPP_SORT_HPP
#define MCPP_SORT_HPP

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
}

#endif