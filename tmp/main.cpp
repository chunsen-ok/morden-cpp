#include <iostream>
#include <string>
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


template<typename T>
class Property
{
public:
    explicit Property(const T &v): value(v) {}

    template<typename Callable>
    Observable<T> changed(Callable &&cb) {
        auto v = cb(value);
        return Observable<T>(v);
    }

private:
    T value;
};


namespace reactive {

template<typename T>
Observable<T> start(const T &v)
{
    std::cout << "Start: " << v << std::endl;
    return Observable{v};
}

template<typename T>
Observable<T> bind() { }

}

int main()
{
    reactive::start(12342)
    .then([](int v) {
        std::cout << "Then: " << v << std::endl;
        return std::string{"Hello"};
    })
    .then([](const std::string &v){
        std::cout << "Then: " << v << std::endl;
        return 0;
    })
    .done();

    Property<int> value{2354};
    value.changed([](int v){
        std::cout << "property changed: " << v << std::endl;
        return v * 2;
    })
    .then([](int v){
        std::cout << "changed again: " << v << std::endl;
        return 0;
    });
    
    return 0;
}