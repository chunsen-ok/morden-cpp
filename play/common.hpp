#ifndef COMMON_HPP
#define COMMON_HPP

#include <utility>

namespace play {

template<typename T>
T max(T arg1, T arg2) {
    return std::max(arg1, arg2);
}

template<typename T, typename ... Args>
T max(T arg, Args ... args) {
    return std::max(arg, play::max(args...));
}

namespace test {
    void range_max() {
        std::cout << play::max(2,4,6,4,6,4,62,23) << std::endl;
    }
}
}

#endif
