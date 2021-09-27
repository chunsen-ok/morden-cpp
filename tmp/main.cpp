// Value categories
// glvalue: 
// prvalue: 
// xvalue:
// lvalue: a glvalue, but not xvalue
// rvalue: a prvalue or xvalue
//
// std::move 返回一个右值引用

#include "model.hpp"

int main()
{
    test::test_field();
    return 0;
}
