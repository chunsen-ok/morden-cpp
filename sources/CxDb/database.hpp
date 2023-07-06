#ifndef MCPP_DATABASE_HPP
#define MCPP_DATABASE_HPP

#include <string>
#include <sqlite3.h>

class Database
{
    friend class SqlQuery;
public:
    ~Database()
    {
        if (mDb) { sqlite3_close(mDb); }
    }

    bool open(const std::string& path)
    {
        const int rc = sqlite3_open(path.c_str(), &mDb);
        if (rc != SQLITE_OK) {
            return false;
        }
        return true;
    }

private:
    sqlite3* db() const { return mDb; }

private:
    sqlite3 *mDb{nullptr};
};

#endif
