#include <iostream>
#include <cstdio>
#include <CxDb/Database>
#include <CxDb/SqlQuery>

using namespace mcpp;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::printf("Invalid arguments\n\nUsage: %s <path>\n", argv[0]);
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
    if (query.prepare("SELECT count(1) FROM stories;")) {
        if (query.step()) {
            std::cout << "count: " << query.value_int(0) << std::endl;
        }
    }

    return 0;
}
