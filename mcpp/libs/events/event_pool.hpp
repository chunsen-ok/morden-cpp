#ifndef REACTIVE_EVENT_POOL_HPP
#define REACTIVE_EVENT_POOL_HPP

#include <memory>

namespace mcpp {
    
class Event;

}

class EventPoolPrivate;
class EventPool
{
public:
    static EventPool *instance();
    EventPool();
    ~EventPool();

    void push_event(mcpp::Event *ev);

private:
    std::unique_ptr<EventPoolPrivate> d;
};

#endif
