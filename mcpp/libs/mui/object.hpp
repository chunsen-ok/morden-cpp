#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include "property.hpp"

class Event;

class Object
{
public:
    explicit Object(Object *parent = nullptr);

    Property<std::string> objectName;

protected:
    void event(Event *ev);
};

#endif
