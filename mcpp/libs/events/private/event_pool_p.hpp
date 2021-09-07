#ifndef EVENT_POOL_P_HPP
#define EVENT_POOL_P_HPP

#include <vector>

namespace mcpp {

class Event;

}

class EventPoolPrivate
{
public:
    std::vector<mcpp::Event*> m_events;
};

#endif