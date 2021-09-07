#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "widget.hpp"
#include <memory>

class ApplicationPrivate;
class Application
{
public:
    Application(int argc, char *argv[]);
    ~Application();

    void set_root(Widget *widget);

    int exec();

private:
    std::unique_ptr<ApplicationPrivate> d;
};

#endif
