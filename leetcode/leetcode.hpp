#ifndef LEETCODE_HPP
#define LEETCODE_HPP

#include <iostream>
#include <vector>
#include <limits>

// 1. 两数之和
std::vector<int> two_sum(const std::vector<int> &nums, int target) {
    std::vector<int> indices;
    
    for (auto it0 = nums.cbegin(); it0 != nums.cend(); ++it0) {
        const int num = target - *it0;
        for (auto it1 = it0 + 1; it1 != nums.cend(); ++it1) {
            if (num == *it1) {
                indices.push_back(it0-nums.cbegin());
                indices.push_back(it1-nums.cbegin());
                return indices;
            }
        }
    }

    return indices;
}

// 7. 整数反转
int reverse_num(int x) {
    int rev = 0;
    while (x) {
        int n = x % 10;

        // INT_MIN <= rev * 10 + n <= INT_MAX
        // INT_MIN - 10 <= rev * 10 <= INT_MAX - 10
        // (INT_MIN - 10) / 10 <= rev <= (INT_MAX - 10) / 10
        if (rev >= (std::numeric_limits<int>::max() - n) / 10) {
            return 0;
        }

        if (rev <= (std::numeric_limits<int>::min() + n) / 10) {
            return 0;
        }

        rev = rev * 10 + n;
        std::cout << rev << std::endl;
        x /= 10;
    }

    return 0;
}

#endif
