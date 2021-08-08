// 控制反转 inversion of controle
// Elm
//
// event happen -> signal change
// 行为可见，状态不可见
#include <iostream>

template<typename T>
class ScopedPointer
{
public:
    ScopedPointer(): data(nullptr) {}
    ScopedPointer(T *ptr): data(ptr) {}
    ~ScopedPointer() { if (data) delete data; data = nullptr; }

    void set(T *ptr) {
        if (data) delete data;
        data = ptr;
    }

    T *get() const { return data; }

private:
    T *data;
};

template<unsigned V>
struct is_zero {
    constexpr static bool value = false;
};

template<>
struct is_zero<0>
{
    constexpr static bool value = true;
};

template<unsigned V>
constexpr bool isZero = is_zero<V>::value;

int main() {
    static_assert(!isZero<235>, "232 is not zero");
    return 0;
}
