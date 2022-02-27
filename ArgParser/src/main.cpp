#include <iostream>
#include "arg_parser.hpp"

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
