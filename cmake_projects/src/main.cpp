#include <iostream>
#include <array>
#include <cstring>

class DataKey
{
public:
    friend bool operator==(const DataKey& lhs, const DataKey& rhs);

private:
    char buf[24];
};

bool operator==(const DataKey& lhs, const DataKey& rhs)
{
    return std::memcmp(lhs.buf, rhs.buf, 24) == 0;
}

int main()
{
    DataKey k0;
    DataKey k1;
    std::cout << (k0 == k1) << std::endl;

    return 0;
}
