#ifndef MCPP_SQLQUERY_HPP
#define MCPP_SQLQUERY_HPP

#include <optional>
#include <mcpp/db/databse.hpp>
#include <mcpp/db/sqlerror.hpp>
#include <mcpp/db/column_policy.hpp>
#include <mcpp/db/column_traits.hpp>

class SqlQuery
{
public:
public:
    SqlQuery(Database& db)
        : mDb(db.db())
        , mStmt(nullptr)
    {}

    ~SqlQuery()
    {
        if (mStmt) {
            sqlite3_finalize(mStmt);
        }
    }

    bool prepare(const std::string& sql)
    {
        const int rc = sqlite3_prepare_v2(mDb, sql.c_str(), sql.size(), &mStmt, nullptr);
        if (rc != SQLITE_OK) {
            return false;
        }
        return true;
    }

    int exec_step()
    {
        return sqlite3_step(mStmt);
    }

    void finish()
    {
        sqlite3_reset(mStmt);
        sqlite3_clear_bindings(mStmt);
    }

    int bind_value(int col, int value)
    {
        return sqlite3_bind_int(mStmt, col+1, value);
    }

    int bind_value(int col, std::int64_t value)
    { 
        return sqlite3_bind_int64(mStmt, col+1, value);
    }

    int bind_value(int col, const std::string& value)
    {
        return sqlite3_bind_text64(mStmt, col+1, value.c_str(), value.size(), SQLITE_STATIC, SQLITE_UTF8);
    }

    int bind_blob_value(int col, const std::string& value)
    {
        return sqlite3_bind_blob64(mStmt, col+1, value.c_str(), value.size(), SQLITE_STATIC);
    }

    int bind_null_value(int col)
    {
        return sqlite3_bind_null(mStmt, col+1);
    }

    template<typename T>
    std::optional<T> value(int col)
    {
        constexpr int col_type = db_column_traits<T>::column_type_index;
        if constexpr (col_type == SQLITE_INTEGER) {
            const sqlite3_int64 t = sqlite3_column_int64(mStmt, col);
            return std::make_optional(db_column_policy<T>::from_int64(t));
        } else if constexpr (col_type == SQLITE_FLOAT) {
            const double t = sqlite3_column_double(mStmt, col);
            return std::make_optinal(db_column_policy<T>::from_double(t));
        } else if constexpr (col_type == SQLITE_TEXT) {
            const unsigned char* t = sqlite3_column_text(mStmt, col);
            const int size = sqlite3_column_bytes(mStmt, col);
            return std::make_optional(db_column_policy<T>::from_text(t, size));
        } else if constexpr (col_type == SQLITE_BLOB) {
            const void* t = sqlite3_column_blob(mStmt, col);
            const int size = sqlite3_column_bytes(mStmt, col);
            return std::make_optional(db_column_policy<T>::from_blob(t, size));
        } else {
            return std::nullopt;
        }
    }

    SqlError error() const
    {
        return SqlError{mDb};
    }

private:
    sqlite3 *mDb;
    sqlite3_stmt *mStmt;
};

#endif
