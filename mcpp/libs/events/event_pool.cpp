#include "event_pool.hpp"
#include "private/event_pool_p.hpp"
#include <iostream>

EventPool *EventPool::instance()
{
    static EventPool pool;
    return &pool;
}

EventPool::EventPool()
    : d(std::make_unique<EventPoolPrivate>())
{

}

EventPool::~EventPool()
{
    std::cout << "~EventPool" << std::endl;
}

void EventPool::push_event(mcpp::Event *ev)
{
    if (!ev) { return; }
    d->m_events.push_back(ev);
}
