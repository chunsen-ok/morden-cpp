#ifndef MCPP_DATABASE_PRIVATE_H
#define MCPP_DATABASE_PRIVATE_H

extern "C" {

#include <sqlite3.h>

}

namespace mcpp {

class DatabasePrivate
{
public:
    DatabasePrivate()
        : db{nullptr}
        , is_open{false}
        , result_code{SQLITE_OK}
    {}

    sqlite3* db;
    bool is_open;
    int result_code;
};

}

#endif
