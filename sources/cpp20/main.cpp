#include <iostream>

template<typename, typename = std::void_t<>>
struct HasEnabledMember: std::false_type {};

template<typename T>
struct HasEnabledMember<T, std::void_t<decltype(&T::enabled)>>: std::true_type {};

struct A
{
    bool enabled;
    std::string name;
};

struct B {};

int main() {
    if constexpr (HasEnabledMember<A>::value) {
        std::cout << "Hello, world!\n";
    }
    return 0;
}
