#ifndef CHAIN_OF_RESPONSIBILITY
#define CHAIN_OF_RESPONSIBILITY

#include <iostream>

namespace mcpp {

    class Context
    {
    public:
        Context(int code) : m_code(code) {}
        virtual ~Context() {}

        int value() const { return m_code; }

    private:
        int m_code{0};
    };

    class Handler
    {
    public:
        virtual ~Handler() {}

        void set_next(Handler *h) { m_next = h; }
        Handler *next() const { return m_next; }

        virtual bool handle(Context *c)
        {
            if (m_next)
            {
                m_next->handle(c);
            }
            return false;
        }

    protected:
        Handler *m_next{nullptr};
    };
    
}


#endif
