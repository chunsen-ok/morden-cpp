#include <fstream>
#include <iostream>
#include <string>
#include <utility>

int main()
{
    std::fstream f("data.dat", std::ios_base::binary | std::ios_base::out);

    f << (unsigned int)0xA0B0C0D0;
    f << (unsigned short)1; // version
    f << (unsigned short)1; // type
    f << u"你好";

    return 0;
}
