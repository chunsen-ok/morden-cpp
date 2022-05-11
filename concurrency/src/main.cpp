/*!
    并发：在计算机中，指在一个系统中，两个及以上的任务同时发生。
    并行：是指在硬件层面上，两个任务是真正同时运行，发生着的。
    并发有可能不是并行，只是CPU核心通过任务切换的方式，让其表现得像是并行的。
    即使在多核心的计算机上，由于大量任务在运行着，其数量远超CPU核心的数量，
    因此，还是不可避免的需要进行任务切换。

    并发的方式：
    - 多进程并发
    - 单进程多线程并发

    管理线程：
    - 启动、等待/分离、线程信息
*/

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
