#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <vector>
#include <iterator>
#include <iostream>

namespace play {
namespace test {

void reverse_iterator()
{
    std::vector<int> nums{2235,235,342,6,2,622,623,25};

    for (auto it = std::crbegin(nums); it != std::crend(nums); ++it) {
        // std::cout << *it << " distance: " << std::distance(it, std::prev(std::crend(nums))) << std::endl;
        std::cout << *it << " index: " << nums.size() - std::distance(std::crbegin(nums), it) << std::endl;
    }
}

}
}

#endif
