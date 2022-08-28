#ifndef ALGOS_HPP
#define ALGOS_HPP

#include <cstdint>

struct Fibonacci
{
    using value_type = std::int64_t;

    value_type next()
    {
        const auto n = n0 + n1;
        n0 = n1;
        n1 = n;
        return n;
    }

private:
    value_type n0{0};
    value_type n1{1};
};



#endif
