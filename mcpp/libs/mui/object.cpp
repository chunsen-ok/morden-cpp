#include "object.hpp"
#include "private/object_p.hpp"
#include <algorithm>
#include <cassert>

Object::Object(Object *parent)
    : Object(new ObjectPrivate, parent)
{
}

Object::Object(ObjectPrivate *d, Object *parent)
    : d(d)
{
    assert(d);

    d->parent = parent;
    if (d->parent) {
        d->parent->add_child(this);
    }
}

Object::~Object()
{
}

bool Object::has_child(const Object *child) const
{
    auto it = std::find(d->children.begin(), d->children.end(), child);
    return it != d->children.end();
}

void Object::add_child(Object *child)
{
    if (!has_child(child)) {
        d->children.push_back(child);
    }
}
