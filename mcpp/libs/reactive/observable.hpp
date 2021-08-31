#ifndef REACTIVE_OBSERVABLE_HPP
#define REACTIVE_OBSERVABLE_HPP

#include <type_traits>

template<typename T>
class Observable
{
public:
    Observable(const T &v): value(v) {}

    template<typename Callable, typename R = typename std::invoke_result<Callable, T>::type>
    Observable<R> then(Callable &&cb) {
        auto r = cb(value);
        return Observable<R>(r);
    }

    void done() {
        std::cout << "Done!" << std::endl;
    }

private:
    T value;
};

#endif
