#ifndef CLEAN_ACTION_HPP
#define CLEAN_ACTION_HPP

template<typename T>
class DataStore;

template<typename T>
class Action
{
public:
    virtual ~Action() = default;
    virtual void exec(T *data, DataStore<T> *store) const = 0;
};

template<typename T>
class AsyncAction
{
public:
    virtual ~AsyncAction() = default;
    virtual void exec(T *data, DataStore<T> *store) = 0;
};

#endif
