#include <iostream>

void number_search(std::int64_t value)
{
    std::size_t times = 0;
    std::int64_t begin = 0;
    std::int64_t end = std::numeric_limits<std::int64_t>::max();

    while (begin < end) {
        ++times;
        auto mid = begin + (end - begin) / 2;
        if (mid > value) {
            end = mid;
        } else if (mid < value) {
            begin = mid + 1;
        } else {
            break;
        }
    }

    std::cout << "loop " << times << " times, found value: " << value << std::endl;
}

int main()
{
    number_search(8);
    // number_search(0);
    // number_search(1);
    // number_search(2);
    // number_search(3);
    // number_search(4);
    // number_search(5);
    // number_search(6);
    // number_search(7);
    // number_search(8);
    // number_search(9);
    return 0;
}
