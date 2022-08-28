#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

double unit(double x, double n)
{
    return (std::pow(-1.0, n) * std::pow(x, 2.0 * n + 1.0)) / (2 * n + 1);
}

double arctan(double x, std::size_t times)
{
    double sum = 0.0;
    for (std::size_t i = 0; i < times; ++i) {
        sum += unit(x, static_cast<double>(i));
    }
    return sum;
}

int main()
{
    std::cout << arctan(2.0, 10000000000) << std::endl;
    return 0;
}
