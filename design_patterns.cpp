// 设计模式原则
// 
#include <iostream>
#include "design_patterns/chain_of_responsibility/chain_of_responsibility.hpp"

using namespace mcpp;

class InputHandler: public Handler {
public:
    InputHandler(const std::string &hint)
        : Handler()
        , m_hint(hint) {}
    
    bool handle(Context *c) override {
        std::cout << "handle 1 ..." << std::endl;
        int val{0};
        std::cout << m_hint << ": ";
        std::cin >> val;
        if (val < c->value()) {
            std::cout << "Tha't ok, I can handle it." << std::endl;
            return true;
        }

        return Handler::handle(c);
    }

private:
    std::string m_hint;
};

class VipHandler: public Handler {
public:
    VipHandler(): Handler() {}
    bool handle(Context *c) override {
        std::cout << "handle 2 ..." << std::endl;
        std::cout << "Welcome! " << c->value() << std::endl;
        return Handler::handle(c);
    }
};

class FinalHandler : public Handler
{
public:
    bool handle(Context *c) {
        std::cout << "Handle it finally." << std::endl;
        return true;
    }
};

int main() {
    InputHandler start("Hello");

    VipHandler h1;
    start.set_next(&h1);

    FinalHandler h2;
    h1.set_next(&h2);

    Context c(12);
    start.handle(&c);

    return 0;
}
