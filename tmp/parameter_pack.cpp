// 模板参数包
// variadic template 可变参数模板
// 展开位置
//   函数实参列表
//   
//  template template parameter
#include <iostream>

template<typename Arg>
void print(Arg arg) {
    std::cout << arg;
}

template<typename Arg, typename ... Args> // 2： type template parameter pack
void print(Arg val, Args ... args) { // 4: function parameter pack
    std::cout << val;
    print(args...); // 5： parameter pack expansion
}

template<typename T>
class A { };

template<typename T, template<typename> typename X>
class B {
    X<T> inner;
};

int main() {
    B<int, A> x;

    const std::string name{"LiuChunsen"};
    print("name: ", name, ", age: ", 21);
    
    return 0;
}
