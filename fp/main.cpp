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
#include <algos/sort.hpp>

// constexpr 
// decltype 推断类型
// declval 

// 条件 - 模板参数特例化
// 循环 - 递归

#include <typeinfo>

class Note
{
public:

};

int main() {
    auto note = Note{};
    const auto &info = typeid(note);
    std::cout << "class: " << info.name() << std::endl;

    std::vector<int> ints{352,62356,236,235,2354,2362,34,46};
    mcpp::qsort(ints.begin(), ints.end());
    for (auto num: ints) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
