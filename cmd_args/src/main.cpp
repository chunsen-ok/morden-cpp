#include <iostream>
#include "command.hpp"

int main(int argc, char *argv[]) {
    auto c = cmd::Command("cmd");
    c.about("This is about test");

    auto helpArg = cmd::Arg("help");
    helpArg.long_name("help")
    .take_value(true)
    .help("Print help information");
    
    c.arg(helpArg);

    c.exec(argc, argv);

    return 0;
}
