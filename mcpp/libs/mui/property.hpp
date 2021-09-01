#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <functional>

// 属性绑定
template<typename T>
class Property
{
public:
    Property() {}
    explicit Property(const T &value): m_value(value) {}

    T get() const { return m_value; }
    void set(const T &value) {
        if (m_value != value) {
            m_value = value;
            // m_value.fire();
        }
    }

    const T &operator*() const {
        return m_value;
    }

    Property &operator=(const T &value) {
        set(value);
        return *this;
    }

private:
    T m_value;
};

#endif
