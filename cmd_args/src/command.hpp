#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include "arg.hpp"

namespace cmd {

class Command
{
public:
    Command(const std::string &name);

    void about(const std::string &about);
    void arg(const Arg &arg);

    void exec(int argc, char *argv[]);
};

}

#endif
