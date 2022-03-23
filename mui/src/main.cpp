#include <iostream>
#include <vector>

class BDataStore
{
public:
    void dispatch();
};

class BDataService{};

int main() {
    std::vector<int> v{1,2,3,34};

    auto it = std::prev(v.begin());
    std::cout << (it == v.begin()) << (it == v.end()) << std::endl;
    return 0;
}
