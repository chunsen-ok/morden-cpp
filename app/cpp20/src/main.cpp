#include <iostream>
#include <vector>

template<typename T>
concept Addable = requires (T a, T b)
{
    a + b;
};

template<typename T> requires Addable<T>
T add(T a, T b)
{
    return a + b;
}

int main() {
    std::cout << add(1,2) << std::endl;
    return 0;
}
