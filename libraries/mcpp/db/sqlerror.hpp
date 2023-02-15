#ifndef MCPP_SQLERROR_HPP
#define MCPP_SQLERROR_HPP

#include <string>
#include <sqlite3/sqlite3.h>

class SqlError
{
    friend class SqlQuery;
protected:
    SqlError(sqlite3* db)
        : mDb(db)
        , mErrCode(sqlite3_errcode(mDb))
        , mExErrCode(sqlite3_extended_errcode(mDb))
        , mErrOffset(sqlite3_error_offset(mDb))
    {
    }

public:
    bool hasError() const
    {
        return (mErrCode != SQLITE_OK && mErrCode != SQLITE_ROW && mErrCode != SQLITE_DONE) 
        || (mExErrCode != SQLITE_OK && mExErrCode != SQLITE_ROW && mExErrCode != SQLITE_DONE);
    }

    int code() const { return mErrCode; }
    int extended_code() const { return mExErrCode; }
    int offset() const { return mErrOffset; }

    std::string error() const
    {
        const char* text = sqlite3_errmsg(mDb);
        return std::string(text);
    }
    
    std::string text() const
    {
        const char* text = sqlite3_errstr(mErrCode);
        return std::string(text);
    }

    std::string extended_text() const
    {
        const char* text = sqlite3_errstr(mExErrCode);
        return std::string(text);
    }

private:
    sqlite3* mDb;
    int mErrCode;
    int mExErrCode;
    int mErrOffset;
};

#endif
