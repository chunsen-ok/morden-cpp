#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    char ch = 'A';
    std::size_t count = 0;
    if (argc >= 2) {
        ch = argv[1][0];
    }

    if (argc >= 3) {
        count = std::stoi(std::string(argv[2]), nullptr);
    }

    std::cout << ch << " " << count << std::endl;
    if (count <= 0) { return 1; }

    std::fstream f("data.txt", std::ios_base::binary | std::ios_base::out);
    if (f.is_open()) {
        f.seekp(1);
        std::size_t writted{0};
        while (writted <= count) {
            f << ch;
            writted += sizeof(int);
        }
    }

    return 0;
}
