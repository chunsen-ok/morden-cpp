// 图灵机
// lambda演算
// SICP
// partial function application
// currying
// higher-order functions：使用其他函数作为参数
//   map, filter, fold, for_each, transform, remove_if
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
#include <functional>

namespace rp {
    template<typename T>
    std::pair<std::optional<T>, std::vector<T>> take(std::vector<T> v, std::size_t count)
    {
        if (v.size() > 0) {
            auto opt = std::make_optional(v.at(0));
            v.erase(v.begin());
            return std::make_pair(opt, v);
        }
        return std::make_pair(std::nullopt, v);
    }

    template<typename T, typename Pred>
    std::vector<T> filter(std::vector<T> v, const Pred &pred)
    {
        auto end = std::remove_if(v.begin(), v.end(), pred);
        return std::vector<T>(v.begin(), v.end());;
    }

    template<typename T>
    std::vector<T> concat(std::vector<T> v1, const std::vector<T> &v2)
    {
        v1.insert(v1.end(), v2.begin(), v2.end());
        return v1;
    }
}

std::vector<int> my_qsort(std::vector<int> v)
{
    const auto vv = rp::take(v, 1); // optional
    if (vv.first) {
        const auto val = vv.first.value();
        auto left = rp::filter(vv.second, [val](int e){ return e <= val; });
        const auto right = rp::filter(vv.second, [val](int e){ return e > val; });

        std::for_each(left.begin(), left.end(), [](int e){ std::cout << e << " "; });
        std::cout << std::endl;

        std::for_each(right.begin(), right.end(), [](int e){ std::cout << e << " "; });
        std::cout << std::endl;

        auto l1 = my_qsort(left);
        auto r1 = my_qsort(right);

        l1.push_back(val);
        return rp::concat(l1, r1);
    }
    return v;
}

int main()
{
    std::vector<int> v{234,62,763,3526,234};
    my_qsort(v);

    std::for_each(v.begin(), v.end(), [](int e){ std:: cout << e << " "; });
    std::cout << std::endl;
    return 0; 
}

/*

// Reactive, Functional
// Basic types
type Int
type Float
type Double
type Bool
type Char
type () // tuple
type [] // list

// Custom type
type <TypeName> { [Body] } 

// Enum type
enum <EnumName> { [Enumerators] }

// Function type
fn load(moduleFile: String) -> Object {
    // ...
}

type Object {
    // default private
    pub name: String
}

type Source: Object {
}

type Target: Object {
    sources: [Source]
}

--

type Executable: Target {

}

--

type Library: Target {

}

--

type StaticLibrary: Library {

}

--

type DynamicLibrary: Library {

}

--

// modules
import std{ io{ Stdio, File } }
import build{ Executable }

type ProcessMiscs: Procedure {

    pub fn process() {
        return Procedure::process()
    }
}

build.Executable {
    name: "play"

    compilerFlags: [
        "O2",
        "Wall",
        "std=c++17",
    ]

    sources: [
        CppFile {
            source: "miscs.cpp",
            procedure: ProcessMiscs {}
        },
        CppFiles {
            sources: [
                "main.cpp",
                "utils.hpp",
                "utils.cpp"
            ]
        }
    ]
}

*/
