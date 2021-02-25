// 设计模式原则
#include <iostream>
#include <string>
#include "design_patterns/chain_of_responsibility.hpp"
#include "design_patterns/factory_method.hpp"
#include "design_patterns/abstract_factory.hpp"

#include "test/test_case.hpp"

#include "design_patterns/product.hpp"
#include "design_patterns/client.hpp"

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

class FinalHandler : public Handler {
public:
    bool handle(Context *c) {
        std::cout << "Handle it finally." << std::endl;
        return true;
    }
};

class FirstSingleProduct: public Product {
public:
    FirstSingleProduct(const std::string &name): Product(name) {}
};

class SecondSingleProduct: public Product {
public:
    SecondSingleProduct(const std::string &name): Product(name) {}
};

class FirstFactoryMethod: public FactoryMethod {
public:
    Product *create() override {
        return new FirstSingleProduct("First Single");
    }
};

class SecondFactoryMethod: public FactoryMethod {
public:
    Product *create() override {
        return new SecondSingleProduct("Second Single");
    }
};

class ChainOfResponsibilityTest: public TestCase {
public:
    bool test() override {
        InputHandler start("Hello");

        VipHandler h1;
        start.set_next(&h1);

        FinalHandler h2;
        h1.set_next(&h2);

        Context c(12);
        start.handle(&c);

        return true;
    }
};

class FactoryMethodTest: public TestCase {
public:
    bool test() override {
        Client c;
        c.set_method(new FirstFactoryMethod);
        std::cout << c.show_prodcut_name() << std::endl;
        c.set_method(new SecondFactoryMethod);
        std::cout << c.show_prodcut_name() << std::endl;
        return true;
    }

protected:
    class Client {
    public:
        ~Client() {
            if (m_method) {
                delete m_method;
                m_method = nullptr;
            }
        }

        void set_method(FactoryMethod *method) {
            if (m_method) { delete m_method; }
            m_method = method;
        }

        std::string show_prodcut_name() {
            if (m_method) {
                Product *p = m_method->create();
                const std::string n = p->name();
                delete p;
                return n;
            }
            return std::string("");
        }

    protected:
        FactoryMethod *m_method {nullptr};
    };
};

class AbstractFactoryTest: public TestCase {
public:
    
    bool test() override {
        return true;
    }
};

int main() {
    auto case1 = ChainOfResponsibilityTest();
    case1.test();

    auto case2 = FactoryMethodTest();
    case2.test();

    auto case3 = AbstractFactoryTest();
    case3.test();

    return 0;
}
