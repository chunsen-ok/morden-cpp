#include <fstream>
#include <iostream>
#include <string>
#include <utility>

int main()
{
    std::fstream f("data.dat", std::ios_base::binary | std::ios_base::out);

    std::size_t bytesWritten{0};
    while (bytesWritten < 1024 * 1024 * 100) {
        f << 3525;
        f << 90878;

        bytesWritten += 8;
    }

    return 0;
}
