#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include <memory>

class Event;

class ObjectPrivate;
class Object
{
public:
    explicit Object(Object *parent = nullptr);
    ~Object();

protected:
    std::unique_ptr<ObjectPrivate> d;
};

#endif
