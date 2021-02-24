#ifndef CONTEXT_HPP
#define CONTEXT_HPP

class Context {
public:
    Context(int code): m_code(code) {}
    int value() const { return m_code; }

private:
    int m_code {0};
};

#endif
