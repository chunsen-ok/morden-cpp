#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <functional>

// 属性绑定
template<typename T>
class Property
{
public:
    explicit Property(const T &value): m_value(value) {}

    T get() const { return m_value; }
    void set(const T &value) {
        if (m_value != value) {
            m_value = value;
        }
    }

private:
    T m_value;
};

#endif
