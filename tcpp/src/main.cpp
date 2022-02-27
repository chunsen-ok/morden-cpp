#include <iostream>

// -E preprocessor
// -S preprocess, compile
// -c preprocess, compile, assemble
// -o output
//
// -I include search path
// -L library search path

enum DataRole {
    None,
    Name,
    Avatar,
};

class A {
public:
    void test() {
        std::cout << "A" << std::endl;
    }
};

class B {
public:
    void do_it() {
        std::cout << "B" << std::endl;
    }
};

template<DataRole R> struct role {};  
template<> struct role<Avatar> { using value_type = A; };
template<> struct role<Name> { using value_type = B; };

template<DataRole R, typename T = typename role<R>::value_type>
T value() { return T{}; }

int main(int argc, char *argv[])
{
    auto v0 = value<Name>();
    auto v1 = value<Avatar>();
    v0.do_it();
    v1.test();
    return 0;
}
