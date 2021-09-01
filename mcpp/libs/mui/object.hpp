#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include <memory>
#include "property.hpp"

class ObjectPrivate;
class Object
{
public:
    explicit Object(Object *parent = nullptr);
    ~Object();

    bool has_child(const Object *child) const;
    void add_child(Object *child);

    Property<std::string> objectName;

protected:
    explicit Object(ObjectPrivate *d, Object *parent = nullptr);
    std::unique_ptr<ObjectPrivate> d;
};

#endif
