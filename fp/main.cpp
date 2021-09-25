// 图灵机
// lambda演算
// SICP
// partial function application
// currying
// higher-order functions：使用其他函数作为参数
//   map, filter, fold, for_each, transform, remove_if
// pure function, immutability
// lazy evaluation
// tail-recursion
// list

// 函数式编程
// 基于lambda演算
// 纯粹的函数式编程没有赋值操作
// 类型推导、多态类型
// 惰性计算
// 高阶函数
// type classes, monads
// currying：将多参数的函数，转换为单参数的函数,
// 列表
// sicp

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template<typename T>
std::vector<T> generate(const std::vector<T> &vec)
{
    return vec;
}

template<typename T, typename ... Expr>
std::vector<T> generate(const std::vector<T> &vec, Expr ... exprs)
{
    return generate((exprs(vec), ...));
}

std::vector<int> qsort(std::vector<int> vec)
{
    if (vec.size() == 0) { return vec; }

    const int flag = vec.front();
    vec.erase(vec.begin());
    auto left = generate(vec, [flag](std::vector<int> v){
        std::remove_if(v.begin(), v.end(), [flag](int n){
            return n > flag;
        });
        return v;
    });

    auto right = generate(vec, [flag](std::vector<int> v){
        std::remove_if(v.begin(), v.end(), [flag](int n){
            return n <= flag;
        });
        return v;
    }); 

    left.push_back(flag);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

int main()
{
    const auto vec = qsort({235,623,26,262,234});
    std::for_each(vec.begin(), vec.end(), [](auto v){
        std::cout << v << " ";
    });
    std::cout << std::endl;

    return 0; 
}
