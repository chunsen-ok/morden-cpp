#include <fstream>

int main() {
    std::fstream f("data.dat", std::ios_base::binary | std::ios_base::out);
    if (f.is_open()) {
        constexpr std::size_t total{1024*1024*30};
        std::size_t writted{0};
        while (writted < total) {
            f << 1234;
            writted += sizeof(int);
        }
    }
    return 0;
}
