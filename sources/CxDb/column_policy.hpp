#ifndef MCPP_COLUMN_POLICY_HPP
#define MCPP_COLUMN_POLICY_HPP

#include <string>
#include <cstdint>

extern "C" {
#include <sqlite3/sqlite3.h>
}

template<typename T>
struct db_column_policy
{
    static T from_int64(sqlite3_int64 value);
    static T from_double(double value);
    static T from_text(const unsigned char* text, int size);
    static T from_blob(const void* blob, int size);
};

template<>
struct db_column_policy<std::int64_t>
{
    static std::int64_t from_int64(sqlite3_int64 value)
    {
        return value;
    }
};

template<>
struct db_column_policy<std::string>
{
    static std::string from_text(const unsigned char* text, int size)
    {
        return std::string(reinterpret_cast<const char*>(text), size);
    }
};

#endif
