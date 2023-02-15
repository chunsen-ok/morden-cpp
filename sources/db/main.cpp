#include <iostream>
#include <mcpp/db/databse.hpp>
#include <mcpp/db/sqlquery.hpp>

int main(int argc, char* argv[])
{
    Database db;
    if (!db.open("F:/me/datas/common.db")) {
        return 1;
    }

    SqlQuery query(db);

    if (!query.prepare("SELECT * FROM notes ORDER BY mt LIMIT 100;")) {
        if (const auto err = query.error(); err.hasError()) {
            std::cout << err.text() << ": " << err.error() << std::endl;
        }
        return 1;
    }

    query.bind_value(0, 12414);
    query.bind_value(1, 34524234);
    const std::string content{"What"};
    query.bind_value(2, content);

    while (SQLITE_ROW == query.exec_step()) {
        std::cout << "uid: ";
        if (const auto val = query.value<std::int64_t>(0); val) {
            std::cout << *val << " ";
        }

        // std::cout << "create time: ";
        // if (const auto val = query.value<std::string>(1); val) {
        //     std::cout << *val;
        // }
        std::cout << std::endl;
    }

    if (const auto err = query.error(); err.hasError()) {
        std::cout << err.text() << ", " << err.extended_text() << std::endl;
    }

    return 0;
}
