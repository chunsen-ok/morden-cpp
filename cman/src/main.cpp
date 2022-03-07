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
//! References:
//!     

#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include "arg_parser.hpp"

void printOption(const std::string &name, const std::string &desc) {
    std::cout << "    " << std::setw(20) << std::left << name << desc << std::endl;
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
    printOption("install", "Install current package to specific directory");
    std::cout << std::endl;

    std::cout << "Other informations." << std::endl;
}

void printVersion() {
    std::cout << "cman 0.0.1 (2022-03-07)" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printHelp();
        return -1;
    }

    const char *arg = argv[1];
    if (arg[0] == '-') {
        // option or standard input or output
        const auto len = std::strlen(arg);
        if (len == 1) {
            // standard input or output
        } else if (len == 2) {
            if (arg[1] == 'h') {
                printHelp();
                return 0;
            } else if (arg[1] == 'v') {
                printVersion();
                return 0;
            }
        } else {
            // ...
        }
    } else {
        // command
        if (std::strcmp(arg, "new")) {

        } else if (std::strcmp(arg, "build")) {

        } else if (std::strcmp(arg, "run")) {

        } else if (std::strcmp(arg, "install")) {

        }
    }

    return 0;
}
