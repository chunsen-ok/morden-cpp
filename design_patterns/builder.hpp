#ifndef MCPP_BUILDER_HPP
#define MCPP_BUILDER_HPP

#include "product.hpp"

namespace mcpp {
    class Builder {
    public:
        virtual ~Builder() {}

        virtual Product *build() = 0;
    };
}

#endif
