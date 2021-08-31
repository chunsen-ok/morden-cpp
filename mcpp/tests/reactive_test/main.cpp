#include <iostream>
#include <reactive.hpp>

int main() {
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
