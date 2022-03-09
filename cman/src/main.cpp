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

int main(int argc, char *argv[])
{
    App app{"cman", "The C/C++ package manager."};
    app.add_arg(Arg{"help", "Prints help information"})
    .add_arg(Arg("version", "Print version info"))
    .add_command(
        Command{"new", "Create new package"}
        .add_arg(Arg{"help", "Prints help information"})
        .add_arg(Arg{"version", "Print version info"})
        .add_arg(Arg{"name", "The package name, default is package directory name", "NAME"})
    )
    .add_command(
        Command{"build", "Build current package"}
        .add_arg(Arg{"help", "Prints help information"})
        .add_arg(Arg{"version", "Print version info"})
    )
    .add_command(
        Command{"run", "Run current package binary"}
        .add_arg(Arg{"help", "Prints help information"})
        .add_arg(Arg{"version", "Print version info"})
    )
    .add_command(
        Command{"install", "Install current package"}
        .add_arg(Arg{"help", "Prints help information"})
        .add_arg(Arg{"version", "Print version info"})
        .add_arg(Arg{"path", "Install target directory"})
    );

    app.parse(argc, argv);

    if (app.is_set("help")) {
        app.showHelp();
    }

    return 0;
}
