// Value categories
// glvalue: 
// prvalue: 
// xvalue:
// lvalue: a glvalue, but not xvalue
// rvalue: a prvalue or xvalue
//
// std::move 返回一个右值引用

#include <iostream>
#include <type_traits>

template<typename T>
class Number
{
public:
    Number(const T &value): m_value(value) {}
    Number(const Number &other): m_value(other.m_value)
    {
        std::cout << "Copy Number" << std::endl;
    }
    Number &operator=(const Number &other)
    {
        m_value = other.m_value;
    }
    ~Number() {
        std::cout << "~Number" << std::endl;
    }

    Number &operator++() {
        ++m_value;
        return *this;
    }

    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Number<U> &rhs);
private:
    T m_value;
};

template<typename U>
std::ostream &operator<<(std::ostream &os, const Number<U> &rhs)
{
    os << rhs.m_value;
    return os;
}

template<typename T>
void increment(Number<T> &&value)
{
    ++value;
    std::cout << value << std::endl;
}

int main() {
    auto n0 = Number<int>(123);
    increment(std::move(n0));
}
