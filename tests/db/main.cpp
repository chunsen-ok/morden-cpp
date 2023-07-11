#include <iostream>
#include <chrono>
#include <iterator>
#include <fstream>
#include <cstdio>
#include <CxDb/Database>
#include <CxDb/SqlQuery>

using namespace mcpp;

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::printf("Invalid arguments\n\nUsage: %s <path> <word>\n", argv[0]);
        return 1;
    } else if (std::strcmp(argv[1], "--help") == 0) {
        std::printf("Usage: %s <path>\n", argv[0]);
        return 0;
    }

    Database db{argv[1]};
    if (!db.is_open()) {
        std::cout << "Database can't open: " << db.error_msg() << std::endl;
        return 1;
    }

    SqlQuery query(db);
    if (!query.prepare("SELECT * FROM chinese_token WHERE chinese_token MATCH 'x';")) {
        std::cout << "Can't create virtual table using cppjieba: " << query.error_msg() << std::endl;
        return 1;
    }

    // std::cout << std::string(argv[2]) << std::endl;
    // query.bind_text(0, std::string(argv[2]));

    if (!query.step()) {
        std::cout << "step: " << query.error_msg() << std::endl;
        return 1;
    }

    std::cout 
    << "id:" << query.value_int64(0)
    << ", text: " << query.value_text(1)
    << std::endl;

    return 0;
}
