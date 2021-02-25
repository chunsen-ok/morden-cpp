#ifndef MCPP_FACTORY_METHOD_HPP
#define MCPP_FACTORY_METHOD_HPP

namespace mcpp {

    // 抽象产品类
    class Product {
    public:
    };

    // 通过派生子类，根据需求创建不同的实际产品类型。
    class Factory
    {
    public:
        virtual Product *create() = 0;
    };
}

#endif
