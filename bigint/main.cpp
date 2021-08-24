#include "bigint.hpp"

void add_test(const std::string &comment) {
    std::cout << "=== " << comment << " ===" << std::endl;
    const auto n0 = BigInt::random<10, 20>();
    std::cout << "n0: " << n0 << std::endl;

    const auto n1 = BigInt::random<10, 20>();
    std::cout << "n1: " << n1 << std::endl;
    
    std::cout << n0 + n1 << std::endl;
}

void sub_test(const std::string &comment) {
    std::cout << "=== " << comment << " ===" << std::endl;
    const auto n0 = BigInt::random<10, 20>();
    std::cout << "n0: " << n0 << std::endl;

    const auto n1 = BigInt::random<10, 20>();
    std::cout << "n1: " << n1 << std::endl;
    
    std::cout << n0 - n1 << std::endl;
    std::cout << n1 - n0 << std::endl;
}

void mul_test(const std::string &comment) {
    std::cout << "=== " << comment << " ===" << std::endl;
    const auto n0 = BigInt::random<10, 20>();
    std::cout << "n0: " << n0 << std::endl;

    const auto n1 = BigInt::random<10, 20>();
    std::cout << "n1: " << n1 << std::endl;
    
    std::cout << n0 * n1 << std::endl;

    const BigInt n2{"7289758278935728978927894", false};
    std::cout << n0 * n2 << std::endl;
}

void div_test(const std::string &comment) {
    std::cout << "=== " << comment << " ===" << std::endl;
    const auto n0 = BigInt::random<20, 30>();
    std::cout << "n0: " << n0 << std::endl;

    const auto n1 = BigInt::random<10, 20>();
    std::cout << "n1: " << n1 << std::endl;
    
    std::cout << n0 / n1 << std::endl;
}

void mod_test(const std::string &comment) {
    std::cout << "=== " << comment << " ===" << std::endl;
    const auto n0 = BigInt::random<6, 10>();
    std::cout << "n0: " << n0 << std::endl;

    const auto n1 = BigInt::random<3, 6>();
    std::cout << "n1: " << n1 << std::endl;

    const auto nm = n0 / n1;

    std::cout << nm << std::endl;
    std::cout << n0 - nm * n1 << "," << nm * n1 << std::endl;
    std::cout << n0 % n1 << std::endl;
}

int main() {

    add_test("Addition");
    sub_test("Subtraction");
    mul_test("Multiply");
    div_test("Division");
    mod_test("Modulo");
    return 0;
}

/*
++ -> +
+- -> -
-+ -> -
-- -> -(+)

++ -> - 
+- -> +
-+ -> -(+)
-- -> -
*/
