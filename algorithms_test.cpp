#include <vector>
#include <functional>
#include "mics/print.hpp"
#include "algorithms/sort.hpp"

template<typename SortFn>
void sort_test(SortFn fn, const std::string &name) {
    std::vector<int> a{27, 46, 2, 7, 83, 53, 63, 34, 47, 253, 72, 3532, 34};
    fn(a.begin(), a.end());
    mcpp::println(name, a.begin(), a.end());
}

int main() {
    using iter_type = std::vector<int>::iterator;
    sort_test(mcpp::insertion_sort<iter_type>, std::string("insertion"));
    sort_test(mcpp::selection_sort<iter_type>, std::string("selection"));
    sort_test(mcpp::bubble_sort<iter_type>, std::string("bubble"));
    sort_test(mcpp::shell_sort<iter_type>, std::string("shell"));
    sort_test(mcpp::qsort<iter_type>, std::string("qsort"));

    return 0;
}
