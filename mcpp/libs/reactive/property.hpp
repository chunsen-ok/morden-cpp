#ifndef REACTIVE_PROPERTY_HPP
#define REACTIVE_PROPERTY_HPP

#include "emitter.hpp"

namespace reactive {

template<typename T>
class Property
{
public:
    Emitter<T> onChanged;
    Emitter<T> aboutToDestruct;

    void bind();
};

}

#endif