#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <type_traits>

template<typename ForwardIter, typename T = typename std::iterator_traits<ForwardIter>::value_type>
T sum(ForwardIter begin, ForwardIter end) {
    T sum = T();
    for (auto it = begin; it != end; ++it) {
        sum += *it;
    }
    return sum;
}

int main() {
    std::vector<int> nums{1,2,3,4,5,6,7};
    std::cout << sum(nums.begin(), nums.end()) << std::endl;
}
