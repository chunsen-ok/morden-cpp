#include <iostream>

class A
{
public:
    void check() {}
};

class B: public A
{
public:

private:
    using A::check;
};

int main()
{
    B b;
    A &a = b;
    B *c = std::addressof(b);
    // b.check(); // ERROR
    a.check();
    // c->check(); // ERROR
}

