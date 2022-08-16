网络与图形领域

## 函数式编程

基于lambda演算

函数式的好处：正确性和表达能力强使得可以写更少的代码。

纯函数 pure function
高阶函数 higher-order function
  使用其他函数作为参数，或者返回另外的函数。

ranges
monads
尾递归




类型推导、多态类型
惰性计算
type classes, monads
currying：将多参数的函数，转换为单参数的函数,
列表
sicp
惰性计算 lazy evaluation
列表生成表达式
列表运算
模式匹配
constexpr 
decltype 推断类型
declval 

图灵机
lambda演算
SICP
partial function application
currying
higher-order functions：使用其他函数作为参数
  map, filter, foldr, for_each, transform, remove_if
pure function, immutability
tail-recursion
list

如果将业务逻辑（修改data数据的逻辑）放在action中，存在问题，可能会存在多线程访问data的情况。

1. 模板参数
- 非类型参数
- 类型参数
- 模板参数
- 以上类型的参数包

类型函数：接受至少一个类型作为参数，或者生成至少一个类型。
类型谓词：接受类型作为类型参数，输出布尔值。
选择：特例化，递归继承
循环：递归（函数递归，类递归）调用

### 设计

- class 和 struct 一般使用 class；除非处理与 c 代码交互；
- 从特殊到一般。
- 功能的抽象 vs 数据的抽象。
- 数据、行为分离。