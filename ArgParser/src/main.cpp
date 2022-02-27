#include <iostream>

class Arg;
class ArgParser
{
public:
    void parse(int argc, char *argv[]);
    void add_arg(const Arg &arg);
};

class Arg
{
public:
    Arg(const std::string &name, const std::string &description = std::string{}, const std::string &value = std::string{});
};

int main(int argc, char *argv[])
{
    ArgParser parser;

    const Arg help{"help", "Show help information"};
    parser.add_arg(help);

    const Arg version{"version", "Show version information"};
    parser.add_arg(version);

    const Arg newArg{"new", "Create a new package"};
    parser.add_arg(newArg);

    const Arg buildArg{"build", "Build current package"};
    parser.add_arg(buildArg);

    parser.parse(argc, argv);

    return 0;
}
