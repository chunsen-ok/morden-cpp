#ifndef MCPP_ABSTRACT_FACTORY_HPP
#define MCPP_ABSTRACT_FACTORY_HPP

#include "product.hpp"

namespace mcpp {

    class Product1: public Product {
    public:
        Product1(const std::string &name): Product(name) {}
    };

    class Product2: public Product {
    public:
        Product2(const std::string &name): Product(name) {}
    };

    class Product3: public Product {
    public:
        Product3(const std::string &name): Product(name) {}
    };

    // 抽象工厂模式：用于创建一组功能上具有关联的对象。
    class AbstractFactory {
    public:
        virtual ~AbstractFactory() {}
        
        virtual Product1 *createProduct1() = 0;
        virtual Product2 *createProduct2() = 0;
        virtual Product3 *createProduct3() = 0;
    };
    
}

#endif
