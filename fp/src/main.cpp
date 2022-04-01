// 图灵机
// lambda演算
// SICP
// partial function application
// currying
// higher-order functions：使用其他函数作为参数
//   map, filter, foldr, for_each, transform, remove_if
// pure function, immutability
// tail-recursion
// list
// lazy evaluation

// 函数式编程
// 基于lambda演算
// 类型推导、多态类型
// 惰性计算
// 高阶函数
// type classes, monads
// currying：将多参数的函数，转换为单参数的函数,
// 列表
// sicp
//
// 惰性计算
// 列表生成表达式
// 列表运算
// 模式匹配
// constexpr 
// decltype 推断类型
// declval 

// 条件 - 模板参数特例化
// 循环 - 递归

//! 如果将业务逻辑（修改data数据的逻辑）放在action中，存在问题，可能会存在多线程访问data的情况。

#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <type_traits>

// 1. 模板参数
// - 非类型参数
// - 类型参数
// - 模板参数
// - 以上类型的参数包
//
// 类型函数：接受至少一个类型作为参数，或者生成至少一个类型。
// 类型谓词：接受类型作为类型参数，输出布尔值。
// 选择：特例化，递归继承
// 循环：递归（函数递归，类递归）调用

class Range
{
public:
    Range(int from, int to)
        : m_from(from), m_to(to) {}

    class iterator
    {
    public:
        iterator(int v): value(v) {}
        friend bool operator!=(const iterator &lhs, const iterator &rhs) {
            return lhs.value != rhs.value;
        }
        iterator &operator++() {
            ++value;
            return *this;
        }
        int operator*() const { return value; }
    private:
        int value;
    };

    iterator begin() { return iterator(m_from); }
    iterator end() { return iterator(m_to); }

private:
    int m_from;
    int m_to;
};

int main()   {

    for (int num: Range(1, 10)) {
        std::cout << num << std::endl;
    }

    return 0;
}