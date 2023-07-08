#ifndef MCPP_SQLQUERY_PRIVATE_H
#define MCPP_SQLQUERY_PRIVATE_H

#include <sqlite3.h>
#include "database.hpp"
#include "database_p.hpp"

namespace mcpp {

class SqlQueryPrivate
{
public:
    SqlQueryPrivate(const Database& db, const DatabasePrivate* dp)
        : pool(db)
        , db(dp->db)
        , stmt(nullptr)
    {}

    const Database& pool;
    sqlite3* db;
    sqlite3_stmt* stmt;
};

}

#endif