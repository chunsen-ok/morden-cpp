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
class Store
{
public:
    Store(T &&data): m_data(std::move(data)) {}

    // 实现多线程访问该方法
    template<typename Callable>
    void dispatch(Callable &&action)
    {
        std::cout << "thread: " << std::this_thread::get_id() << std::endl;
        std::invoke(std::move(action), &m_data, this);
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
    store.dispatch(reset_number(10));

    // std::thread t([](DataStore *store){
    //     store->dispatch(inc_number);
    // }, &store);
    // t.join();

    for (int dy = 0; dy <= 10; ++dy) {
        const auto x = pixel_circle(10.0, dy);
        std::cout  << dy << ", " << std::round(x) << std::endl;
    }

    return 0;
}
