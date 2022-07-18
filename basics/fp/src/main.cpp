#include <iostream>
#include <cstring>

template<std::size_t size>
class Mid
{
public:
};

template<>
class Mid<32>
{
public:
    constexpr Mid()
        : buf{0}
    {}

    friend bool operator==(const Mid<32> &lhs, const Mid<32> &rhs);

private:
    char buf[32];
};

inline bool operator==(const Mid<32> &lhs, const Mid<32> &rhs)
{
    return 0 == std::memcmp(lhs.buf, rhs.buf, 32);
}

int main() {
    Mid<32> m0;
    Mid<32> m1;

    return 0;
}
