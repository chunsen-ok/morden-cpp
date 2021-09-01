#ifndef OBJECT_P_HPP
#define OBJECT_P_HPP

#include <vector>

class Object;
class ObjectPrivate
{
public:
    Object *parent{nullptr};
    std::vector<Object*> children;
};

#endif
