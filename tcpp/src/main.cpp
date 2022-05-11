//! C++元编程
//!
// 1. 模板参数 template parameter
// - 类型参数 type template parameter
// - 非类型参数 non-type template parameter
// - 模板参数 template template parameter
// - 以上类型的参数包
//
// 片特化只适用于类模板和变量模板。
// 
// 模板只会在使用时被特例化或者实例化。需要完整对象类型或者函数定义的
// 上下文中引用了模板特例化，模板将会被实例化。
//
// 类型函数：接受至少一个类型作为参数，或者生成至少一个类型。
// 类型谓词：接受类型作为类型参数，输出布尔值。
// 选择：特例化，递归继承
// 循环：递归（函数递归，类递归）调用
//
// 元函数：class/struct，一般只定义一个输出（一种值或者一直类型，类型和值可以同时存在用于描述同一事物）
// 类型元函数、值元函数

#include <iostream>
#include <string>
#include <functional>
#include <type_traits>

template<typename T, typename = void>
struct dispatch {};

template<typename T>
struct dispatch<T, typename std::invoke_result_t<T, int>>
{
    using type = typename std::invoke_result_t<T, int>;

    static void call(T &&fn, int a, int)
    {
        std::invoke(std::move(fn), a);
    }
};

template<typename T>
struct dispatch<T, typename std::invoke_result_t<T, int, int>>
{
    using type = typename std::invoke_result_t<T, int, int>;

    static void call(T &&fn, int a, int b)
    {
        std::invoke(std::move(fn), a, b);
    }
};

void a(int a) {
    std::cout << a << std::endl;
}

void b(int a, int b) {
    std::cout << a << ", " << b << std::endl;
}

template<typename F, typename = typename dispatch<F>::type>
void exec(F &&fn)
{
    dispatch<F>::call(std::move(fn), 1, 2);
}

struct Action
{
    void operator()(int a, int b)
    {
        std::cout << a << " - " << b << std::endl;
    }
};

int main() {
    exec(a);
    exec(b);
    exec([](int a){ std::cout << a << std::endl; });
    exec(Action{});
    return 0;
}
