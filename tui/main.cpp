#include <iostream>
#include "tui.h"

int main(int argc, char* argv[])
{
    using namespace tui;

    Command app{"cman"};

    app.parse(argc, argv);

    return 0;
}
