
#include <iostream>
#include <thread>
#include <functional>

template<typename T>
class Store;

template<typename T>
struct AsyncAction
{
    virtual ~AsyncAction() = default;
    virtual void exec(T *data, Store<T> *store) = 0;
};

template<typename T>
class Store
{
public:
    Store(T &&data): m_data(std::move(data)) {}

    template<typename Callable>
    using invocable_action = std::enable_if_t<std::is_invocable<Callable, T*, Store<T>*>::value>;

    template<typename Callable>
    auto dispatch(Callable &&action) -> invocable_action<Callable>
    {
        std::cout << "thread: " << std::this_thread::get_id() << std::endl;
        std::invoke(std::move(action), &m_data, this);
    }

    void dispatch(AsyncAction<T> *action)
    {
        action->exec(&m_data, this);
    }

private:
    T m_data;
};

class Data
{
public:
    int number;
};

using DataStore = Store<Data>;
using Action = std::function<void(Data*, Store<Data>*)>;

struct ActionObj: AsyncAction<Data>
{
    void exec(Data *data, Store<Data> *store)
    {
        std::cout << "Hello:" << data->number << std::endl;
    }
};

Action action_wrap(ActionObj *action)
{
    return [action](Data *data, Store<Data> *store){
        action->exec(data, store);
    };
}

Action reset_number(int num)
{
    return [num](Data *data, DataStore *store){
        data->number = num;
    };
}

Action inc_number(int inc)
{
    return [inc](Data *data, Store<Data> *store) {
        data->number += inc;
        std::cout << data->number << std::endl;
    };
}

double pixel_circle(double r, double dy)
{
    return std::sqrt(2 * r * dy - dy * dy);
}

int main(int argc, char *argv[])
{
    std::cout << "main thread: " << std::this_thread::get_id() << std::endl;
    Store<Data> store{Data{}};
    
    store.dispatch(reset_number(20));
    store.dispatch(ActionObj{});

    auto action = new ActionObj;
    store.dispatch(action);
    delete action;

    return 0;
}
