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

struct Model
{
    int value {0};
};

struct IncAction {};
struct DecAction {};
struct ResetAction {
    int new_value {0};
};
using Action = std::variant<IncAction, DecAction, ResetAction>;

// Reducer - update
Model update(Model model, Action action);

// commands
std::optional<Action> intent(char event)
{
    switch (event) {
        case '+': return IncAction{};
        case '-': return DecAction{};
        case '.': return ResetAction{};
        default: return std::nullopt;
    }
}

// draw
void draw(Model model)
{
    std::cout << model.value << std::endl;
}

int main() {
    return 0;
}
