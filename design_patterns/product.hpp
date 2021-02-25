#ifndef MCPP_PRODUCT_HPP
#define MCPP_PRODUCT_HPP

#include <string>

namespace mcpp {

    class Product {
    public:
        Product(const std::string &name): m_name(name) {}
        virtual ~Product() {}

        const std::string &name() const { return m_name; }
        void set_name(const std::string &name) { m_name = name; }

    protected:
        std::string m_name;
    };
}

#endif
