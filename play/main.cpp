#include "helper.hpp"
#include "common.hpp"
// #include "sort_by_multi_fields.hpp"
// #include "reverse_iterator.hpp"

#include <tuple>
#include <utility>

using namespace play;

template<typename Callable, 
    typename R = typename std::invoke_result<Callable>::type, 
    typename ... Args>
class Runnable
{
public:
    Runnable(Callable &&cb, Args ... args)
        : callback(std::move(cb))
        , args(std::make_tuple(std::forward<Args>(args)...)) {}

    R exec() { return callback(); }

private:
    Callable callback;
    std::tuple<Args ...> args;
};

int main() {
    // wrap_test(test::sort_by_multi_fields);
    // wrap_test(test::reverse_iterator);
    wrap_test(test::range_max);

    auto worker0 = Runnable([](){ return 0; }, 12, 56);
    std::cout << worker0.exec() << std::endl;

    // Runnable worker1;
    // worker1.exec([](const std::string &name){ return ""; });

    // Runnable worker2;
    // worker2.exec([](const std::string &name, const std::string &value){ return name + value; });

    return 0;
}
