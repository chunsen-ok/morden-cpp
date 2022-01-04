#include "helper.hpp"
#include "common.hpp"
// #include "sort_by_multi_fields.hpp"
#include "reverse_iterator.hpp"

#include <tuple>
#include <utility>

using namespace play;

int main() {
    // wrap_test(test::sort_by_multi_fields);
    wrap_test(test::reverse_iterator);
    wrap_test(test::range_max);

    return 0;
}
