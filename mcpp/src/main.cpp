#include <iostream>
#include <event_pool.hpp>

class EventLoop
{
public:
    int exec();
};

int EventLoop::exec()
{
    return 0;
}

int main(int argc, char *argv[])
{
    EventLoop loop;
    return loop.exec();
}
