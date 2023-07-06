#ifndef MCPP_FIND_HPP
#define MCPP_FIND_HPP

#include <iterator>

namespace mcpp {

template<typename Iter, typename T = typename std::iterator_traits<Iter>::value_type>
std::pair<Iter, Iter> find_value_range(Iter begin, Iter end, const T &value)
{
    while (begin < end) {
        auto it = std::next(begin, std::distance(begin, end) / 2);
        if (*it == value) {
            auto [lowerBegin, lowerEnd] = find_value_range(begin, it); // 下边界
            auto [upperBegin, upperEnd] = find_value_range(it, end);   // 上边界
            return std::make_pair(lowerBegin, upperEnd);
        } else if (*it < value) {
            begin = std::next(it);
        } else if (*it > value) {
            end = it;
        }
    }

    return std::make_pair(end, end);
}

}

#endif
