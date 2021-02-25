#ifndef CHAIN_OF_RESPONSIBILITY
#define CHAIN_OF_RESPONSIBILITY

#include <iostream>
#include "context.hpp"

class Handler {
public:
    virtual ~Handler() { }

    void set_next(Handler *h) { m_next = h; }
    Handler *next() const { return m_next; }
    
    virtual bool handle(Context *c) {
        if (m_next) { m_next->handle(c); }
        return false;
    }

protected:
    Handler *m_next{nullptr};
};

#endif
