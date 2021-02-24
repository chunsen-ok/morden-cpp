#include <iostream>
#include "design_patterns/chain_of_responsibility/chain_of_responsibility.hpp"

class InputHandler: public Handler {
public:
    InputHandler(const std::string &hint)
        : Handler()
        , m_hint(hint) {}
    
    bool handle(c *Context) override {
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
    bool handle(c *Context) override {
        std::cout << "Welcome!" << c->value() << std::endl;
        return true;
    }
};

int main() {
    InputHandler h1("Hello");
    VipHandler h2;
    h1.set_next(&h2);

    Context c(12);
    h1.handle(&c);

    return 0;
}
