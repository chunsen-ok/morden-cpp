#include <iostream>

class A {
public:
    A(int v): a(v) {}
    
    const int a{0};
};

int main() {
    A a = A(212);
    std::cout << a.a << std::endl;
    return 0;
}
