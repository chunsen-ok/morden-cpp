#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <functional>

// 属性绑定
template<typename T>
class Property
{
public:
    explicit Property(const T &other);

    T get() const;
    void set(T);

    void on_changed(std::function<void(T)>);
    void bind();
};

#endif