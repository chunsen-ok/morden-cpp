#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <string>

class Arg
{
public:
    Arg(const std::string &name, const std::string &description = std::string{}, const std::string &value = std::string{});
};

class ArgParser
{
public:
    void add_arg(const Arg &arg);
    
    void parse(int argc, char *argv[]);
};

#endif
