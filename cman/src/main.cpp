//! The C/C++ package manager.
//!
//! Usage: 
//!     cman [OPTIONS]
//!
//! Options:
//!     -h, --help        Prints help information
//!     -v, --version     Print version info
//!
//! Commands:
//!     new        Create a new package
//!     build      Compile current package
//!     run        Run current package binary
//!
//! Other informations.
//!

#include <string>
#include <iostream>
#include "arg_parser.hpp"

void printOption(const std::string &name, const std::string &desc) {
    std::cout << "    " << name << "\t\t" << desc << std::endl;
}

void printHelp() {
    std::cout << "The C/C++ package manager.\n" << std::endl;
    
    std::cout << "Usage:" << std::endl;
    std::cout << "    " << "cman [OPTIONS] [COMMAND]\n" << std::endl;
    
    std::cout << "Options:" << std::endl;
    printOption("-h, --help", "Prints help information");
    printOption("-v, --version", "Print version info");
    std::cout << std::endl;
    
    std::cout << "Commands:" << std::endl;
    printOption("new", "Create a new package");
    printOption("build", "Compile current package");
    printOption("run", "Run current package binary");
    std::cout << std::endl;

    std::cout << "Other informations." << std::endl;
}

int main(int argc, char *argv[])
{
    const std::string name{argv[0]};

    if (argc == 1) {
        printHelp();
        return -1;
    }

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

    return 0;
}
