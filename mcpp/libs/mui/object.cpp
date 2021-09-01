#include "object.hpp"
#include "private/object_p.hpp"

Object::Object(Object *parent)
    : d(std::make_unique<ObjectPrivate>())
{

}

Object::~Object()
{

}
