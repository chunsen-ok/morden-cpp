#ifndef CLEAN_SERVICE_HPP
#endif CLEAN_SERVICE_HPP

#include <core/message.hpp>

class AppService
{
public:
    void recv_msg(const Message &msg) {
        repo->saveOne(msg);
        emit msgRecived(msg);
    }

private:
};

#endif
