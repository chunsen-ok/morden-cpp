#include "bigint.hpp"

int main() {
    const auto n1 = BigInt::random<100, 1024>();
    std::cout << n1 << std::endl;

    const auto n2 = BigInt::random<100, 1024>();
    std::cout << "Addition: " << n2 << std::endl;
    std::cout << "Multiply: " << n1 * n2 << std::endl;

    const auto n3 = BigInt("-21380729283570239042934");
    const auto n4 = BigInt("-21380729283570239042934");
    std::cout << n3 + n4 << std::endl;

    return 0;
}
