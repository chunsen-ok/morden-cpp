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
    app.set_version("0.0.1")
    .add_command(
        Command{"new", "Create new package", "path"}
        .add_arg(Arg{"name", "The package name, default is package path name", "NAME"})
    )
    .add_command(
        Command{"build", "Build current package"}
    )
    .add_command(
        Command{"run", "Run current package binary"}
    )
    .add_command(
        Command{"install", "Install current package"}
        .add_arg(Arg{"path", "Install target directory"})
    );

    app.parse(argc, argv);

    if (app.is_set("help")) {
        app.show_help();
    } else if (auto cmd = app.command_is_set("new"); cmd.has_value()) {
        if (cmd->is_set("help")) {
            cmd->show_help();
        }
    } else if (auto cmd = app.command_is_set("build"); cmd.has_value()) {
        cmd->show_help();
    }

    return 0;
}
