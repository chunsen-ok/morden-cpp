#ifndef SESSION_DATA_HPP
#define SESSION_DATA_HPP

#include <anylib/global.hpp>

class SessionDataPrivate;
class ANY_EXPORT SessionData
{
public:
    SessionData();
    void chats();

private:
    SessionDataPrivate *d_ptr;
};

#endif
