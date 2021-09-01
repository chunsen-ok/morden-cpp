#include <iostream>
#include <event_pool.hpp>

#include <widget.hpp>

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

    Widget widget;
    
    // widget.size
    // .changed([](const Size<double> &size){
    // });

    widget.position = Point<double>{100, 100};
    widget.size = Size<double>{800, 600};

    widget.show();

    return loop.exec();
}
