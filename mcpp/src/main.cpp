#include <iostream>
#include <bigint.hpp>

int main()
{
    const auto n1 = BigInt::random();
    const auto n2 = BigInt::random();
    std::cout << n1 * n2 << std::endl;

    return 0;
}
