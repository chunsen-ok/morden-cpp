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
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <optional>
#include <variant>
#include <functional>

// constexpr 
// decltype 推断类型
// declval 

// 条件 - 模板参数特例化
// 循环 - 递归

template<typename T>
struct ElementType
{
    using type = typename std::iterator_traits<decltype(std::begin(std::declval<T>()))>::value_type;
};

template<int N>
struct Sum {
    static const int value = Sum<N-1>::value + N;
};

template<>
struct Sum<0> {
    static const int value = 0;
};

int main() {
    static_assert(std::is_same<int, ElementType<std::vector<int>>::type>::value, "Element type is not int");

    constexpr int val = Sum<3>::value;
    std::cout << val << std::endl;

    return 0;
}
