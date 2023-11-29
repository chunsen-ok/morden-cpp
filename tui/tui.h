#ifndef TUI_H
#define TUI_H

#include <string>

namespace tui {

class Command
{
public:
    explicit Command(const std::string& name);

    void parse(int argc, char* argv[])
    {
        // parse name
        const auto name{argv[0]};
    }

private:

};

}

#endif
