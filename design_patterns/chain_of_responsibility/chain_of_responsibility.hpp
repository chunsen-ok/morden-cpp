#ifndef CHAIN_OF_RESPONSIBILITY
#define CHAIN_OF_RESPONSIBILITY

#include "context.hpp"

class Handler {
public:
    void set_next(const h *Handler) { m_next = h; }
    Handler *next() const { return m_next; }
    
    virtual bool handle(c *Context) {
        if (m_next) { m_next->handle(c); }
        return false;
    }

protected:
    Handler *m_next{nullptr};
};

#endif
