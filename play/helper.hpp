#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>

namespace play {

template<typename Callable, typename ... Args>
void wrap_test(Callable &&cb, Args ... args)
{
    std::cout << "=== START ===" << std::endl;
    cb(std::forward<Args>(args)...);
    std::cout << "=== END ===" << std::endl;
}

}

#endif
