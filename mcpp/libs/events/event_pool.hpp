#ifndef REACTIVE_EVENT_POOL_HPP
#define REACTIVE_EVENT_POOL_HPP

#include <memory>

class Event;

class EventPoolPrivate;
class EventPool
{
public:
    static EventPool *instance();
    EventPool();
    ~EventPool();

    void push_event(Event *ev);

private:
    std::unique_ptr<EventPoolPrivate> d;
};

#endif
