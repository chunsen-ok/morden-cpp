#ifndef MCPP_FACTORY_METHOD_HPP
#define MCPP_FACTORY_METHOD_HPP

#include "product.hpp"

namespace mcpp {

    // 通过派生子类，根据需求创建不同的实际产品类型。
    class FactoryMethod
    {
    public:
        virtual ~FactoryMethod() {}
        
        virtual Product *create() = 0;
    };
}

#endif
