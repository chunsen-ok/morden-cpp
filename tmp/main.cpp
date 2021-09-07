// Value categories
// glvalue: 
// prvalue: 
// xvalue:
// lvalue: a glvalue, but not xvalue
// rvalue: a prvalue or xvalue
//
// std::move 返回一个右值引用

#include <iostream>
#include <tuple>
#include <type_traits>

template<typename Callable, typename ... Args>
class Event
{
public:
    Event(Callable &&cb, Args ... args)
        : m_callback(cb)
        , m_args(std::make_tuple(args...))
    {

    }

    template<typename R = typename std::invoke_result<Callable, Args ...>::type>
    R exec() {
        return std::apply(m_callback, m_args);
    }

private:
    Callable m_callback;
    std::tuple<Args...> m_args;
};

int main()
{
    Event ev([](int n1, int n2, const std::string &info){
        return n1 + n2;
    }, 12, 432, "hello");

    std::cout << ev.exec() << std::endl;

    return 0;
}