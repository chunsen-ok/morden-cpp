#ifndef CLEAN_DATA_STORE_HPP
#define CLEAN_DATA_STORE_HPP

#include "action.hpp"

template<typename T>
class DataStore
{
public:
    DataStore(const T &data): m_data(data) {}
    DataStore(T &&data): m_data(std::move(data)) {}

    const T &data() const { return m_data; }

    void dispatch(const Action<T> &action)
    {
        action.exec(&m_data, this);
    }

    void dispatch(Action<T> *action)
    {
        action->exec(&m_data, this);
    }

    void subscribe()
    {
        
    }

private:
    T m_data;
};

#endif
