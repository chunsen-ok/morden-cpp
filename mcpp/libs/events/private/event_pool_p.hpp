#ifndef EVENT_POOL_P_HPP
#define EVENT_POOL_P_HPP

#include <vector>

class Event;

class EventPoolPrivate
{
public:
    std::vector<Event*> m_events;
};

#endif