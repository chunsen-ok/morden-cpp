#include <iostream>
#include "signal_slot.hpp"

using namespace mui;

int main(int argc, char *argv[])
{
    Signal<int> num;
    Slot<int> setNum;
    auto conn = Connection<int>::create(&num, &setNum);

    Slot<int> setNum1;
    auto conn1 = Connection<int>::create(&num, &setNum1);

    num.call(42);

    return 0;
}
