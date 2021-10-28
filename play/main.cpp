#include "helper.hpp"
#include "sort_by_multi_fields.hpp"
#include "reverse_iterator.hpp"

using namespace play;

int main() {
    wrap_test(test::sort_by_multi_fields);
    wrap_test(test::reverse_iterator);
    return 0;
}
