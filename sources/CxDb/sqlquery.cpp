#include "sqlquery.hpp"
#include "sqlquery_p.hpp"

namespace mcpp {

SqlQuery::SqlQuery(const Database& db)
    : d{new SqlQueryPrivate(db, db.d.get())}
{
}

SqlQuery::~SqlQuery()
{
    if (d->stmt) {
        sqlite3_finalize(d->stmt);
    }
}

bool SqlQuery::prepare(const std::string& sql)
{
    const int rc = sqlite3_prepare_v2(d->db, sql.c_str(), sql.size(), &d->stmt, nullptr);
    if (rc != SQLITE_OK) {
        return false;
    }
    return true;
}

bool SqlQuery::step()
{
    const int rc = sqlite3_step(d->stmt);
    return rc == SQLITE_OK || rc == SQLITE_DONE || rc == SQLITE_ROW;
}

void SqlQuery::reset()
{
    sqlite3_reset(d->stmt);
    sqlite3_clear_bindings(d->stmt);
}

int SqlQuery::bind_double(int index, double value)
{
    return sqlite3_bind_double(d->stmt, index+1, value);
}

int SqlQuery::bind_int(int index, int value)
{
    return sqlite3_bind_int(d->stmt, index+1, value);
}

int SqlQuery::bind_int64(int index, std::int64_t value)
{ 
    return sqlite3_bind_int64(d->stmt, index+1, value);
}

int SqlQuery::bind_text(int index, const std::string& value)
{
    return sqlite3_bind_text64(d->stmt, index+1, value.c_str(), value.size(), SQLITE_STATIC, SQLITE_UTF8);
}

int SqlQuery::bind_blob(int index, const std::string& value)
{
    return sqlite3_bind_blob64(d->stmt, index+1, value.c_str(), value.size(), SQLITE_STATIC);
}

int SqlQuery::bind_null(int index)
{
    return sqlite3_bind_null(d->stmt, index+1);
}

double SqlQuery::value_double(int index)
{
    return sqlite3_column_double(d->stmt, index);
}

int SqlQuery::value_int(int index)
{
    return sqlite3_column_int(d->stmt, index);
}

std::int64_t SqlQuery::value_int64(int index)
{
    return sqlite3_column_int64(d->stmt, index);
}

const std::uint8_t* SqlQuery::value_text(int index)
{
    return sqlite3_column_text(d->stmt, index);
}

const void* SqlQuery::value_blob(int index)
{
    return sqlite3_column_blob(d->stmt, index);   
}

bool SqlQuery::has_error() const
{
    return d->pool.has_error();
}

const char* SqlQuery::error_msg() const
{
    return d->pool.error_msg();
}

}
