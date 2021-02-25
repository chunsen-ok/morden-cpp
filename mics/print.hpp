#ifndef MCPP_MICS_HPP
#define MCPP_MICS_HPP

#include <iostream>
#include <string>

namespace mcpp {
    template<typename InputIt>
    void println(const std::string &info, InputIt begin, InputIt end) {
        std::cout << info << ":\t";
        for (; begin != end; ++begin) {
            std::cout << *begin << " ";
        }
        std::cout << std::endl;
    }
}

#endif
