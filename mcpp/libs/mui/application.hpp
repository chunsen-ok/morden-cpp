#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "widget.hpp"

class Application
{
public:
    Application(int argc, char *argv[]);

    void set_root(Widget *widget);

    int exec();
};

#endif
