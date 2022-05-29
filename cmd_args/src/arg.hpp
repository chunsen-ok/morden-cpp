#ifndef ARG_HPP
#define ARG_HPP

#include <string>

namespace cmd {

class Arg
{
public:
    Arg(const std::string &name);

    Arg &take_value(bool take)
    {
        return *this;
    }

    Arg &help(const std::string &text)
    {
        return *this;
    }

    Arg &long_name(const std::string &text)
    {
        return *this;
    }

private:
    std::string m_name;
    bool        m_take_value;
    std::string m_help;
    std::string m_long_name;
};

}

#endif
