#include "database.hpp"
#include "database_p.hpp"

namespace mcpp {

Database::Database()
    : d{new DatabasePrivate}
{

}

Database::Database(const std::string& path)
    : d{new DatabasePrivate}
{
    open(path);
}

Database::~Database()
{
    close();
}

bool Database::is_open() const
{
    return d->is_open;
}

void Database::open(const std::string& path)
{
    if (is_open()) {
        return;
    }

    d->result_code = sqlite3_open(path.c_str(), &d->db);
    d->is_open = d->result_code == SQLITE_OK;
}

void Database::close()
{
    if (d->db) {
        sqlite3_close(d->db);
        d->db = nullptr;
        d->is_open = false;
        d->result_code = SQLITE_OK;
    }
}

bool Database::has_error() const
{
    return d->result_code != SQLITE_OK && 
    d->result_code != SQLITE_ROW && 
    d->result_code != SQLITE_DONE;
}

const char* Database::error_msg() const
{
    return sqlite3_errmsg(d->db);
}

}
