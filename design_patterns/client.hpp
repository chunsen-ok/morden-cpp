#ifndef MCPP_CLIENT_HPP
#define MCPP_CLIENT_HPP

namespace mcpp {
    class Client {
    public:
        virtual ~Client() {}
        virtual void request() = 0;
    };
}

#endif
