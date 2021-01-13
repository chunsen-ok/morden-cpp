#ifndef MCPP_MICS_HPP
#define MCPP_MICS_HPP
#include <iostream>

namespace mcpp {
    template<typename InputIt>
    void println(InputIt begin, InputIt end) {
        for (; begin != end; ++begin) {
            std::cout << *begin << " ";
        }
        std::cout << std::endl;
    }
}

#endif
