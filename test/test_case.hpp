#ifndef MCPP_TEST_CASE_HPP
#define MCPP_TEST_CASE_HPP

#include <iostream>

namespace mcpp {
    class TestCase {
    public:
        virtual ~TestCase() {}

        virtual bool test() {
            std::cout << "TO DO ..." << std::endl;
            return true;
        }
    };
}

#endif
