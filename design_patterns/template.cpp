#include "template.hpp"

int main() {
    Obj o;
    o.count = 62352;
    test<MyBuilder>(&o);
    return 0;
}

