#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <string>
#include <iostream>
#include <unordered_map>

class Arg
{
public:
    Arg(const std::string &name, const std::string &description = std::string{}, const std::string &value = std::string{})
        : mName(name), mDesc(description), mValue(value) {}

    const std::string &name() const {
        return mName;
    }

private:
    std::string mName;
    std::string mDesc;
    std::string mValue;
};

class ArgParser
{
public:
    void add_arg(const Arg &arg) {
        mArgs.insert({arg.name(), arg});
    }
    
    void parse(int argc, char *argv[]) {
        const std::string name{argv[0]};
        std::cout << name << std::endl;

        for (int i = 1; i < argc; ++i) {
            const std::string arg{argv[i]};
            if (arg.size() == 1) {
                if (arg[0] == '-') {
                    // standard input
                } else {
                    // option value
                }
            } else if (arg.size() == 2) {
                if (arg == "--") {
                    // delimiter
                } else if (arg[0] == '-') {
                    // short-option
                } else {
                    // option value
                }
            } else if (arg.size() > 2) {
                if (arg == "--") {
                    // long-option
                } else if (arg[0] == '-') {
                    // short-options
                } else {
                    // option value
                }
            }
            std::cout << arg << std::endl;
        }
    }

private:
    std::unordered_map<std::string, Arg> mArgs;
};

#endif
