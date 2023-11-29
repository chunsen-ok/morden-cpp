/*! cman
 * > cman --help
 * The C/C++ build tool & package manager.
 * 
 * Usage: cman [options] [command]
 * 
 * Options:
 *     -h, --help
 *     -v, --version
 * 
 * Commands:
 *     new
 *     build
 *     test
 *     install
 *     update
 * 
 * [Footers]
*/

#include <iostream>
#include <tui.h>

int main(int argc, char* argv[])
{
    using namespace tui;

    Document doc;
    doc.add_element(Paragraph{"The C/C++ build tool & package manager."});
    doc.add_element(Paragraph{"Usage: cman [options] [commands]"});

    OptionList options;
    options.add_element(OptionItem{"help"});
    options.add_element(OptionItem{"version"});

    UnorderedList commands;
    commands.

    return 0;
}
