#include <vector>
#include "mics/print.hpp"
#include "algorithms/sort.hpp"

void insertion_sort_test() {
    std::vector<int> a{235, 32, 7, 2, 674, 462, 573, 34, 235};
    mcpp::insertion_sort(a.begin(), a.end());
    mcpp::println(a.begin(), a.end());
}

void selection_sort_test() {
    std::vector<int> a{27,46,2,7,83,53,63,34,47,253,72,3532,34};
    mcpp::selection_sort(a.begin(), a.end());
    mcpp::println(a.begin(), a.end());
}

void bubble_sort_test()
{
    std::vector<int> a{27, 46, 2, 7, 83, 53, 63, 34, 47, 253, 72, 3532, 34};
    mcpp::bubble_sort(a.begin(), a.end());
    mcpp::println(a.begin(), a.end());
}

int main() {
    insertion_sort_test();
    selection_sort_test();
    bubble_sort_test();
    return 0;
}
