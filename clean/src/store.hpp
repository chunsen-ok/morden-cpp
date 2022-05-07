#ifndef CLEAN_STORE_HPP
#define CLEAN_STORE_HPP

#include <type_traits>

template<typename T>
class Store
{
public:
    template<typename ... Args>
    Store(Args ... args): m_data(std::forward<Args>(args)...) {}

    const T &data() const { return m_data; }
    const T *operator->() const { return std::addressof(m_data); }

    template<typename F, typename = typename std::invoke_result_t<F, T*, Store<T>*>>
    void dispatch(F &&action)
    {
        std::invoke(std::move(action), std::addressof(m_data), this);
    }

protected:
    T m_data;
};

#endif
