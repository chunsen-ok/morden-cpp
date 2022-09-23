#ifndef MCPP_COLUMN_TRAITS_HPP
#define MCPP_COLUMN_TRAITS_HPP

#include <string>
#include <cstdint>

extern "C" {
#include <sqlite3/sqlite3.h>
}

template<typename T>
struct db_column_traits;

template<>
struct db_column_traits<int>
{
    static constexpr int column_type_index = SQLITE_INTEGER;
};

template<>
struct db_column_traits<std::int64_t>
{
    static constexpr int column_type_index = SQLITE_INTEGER;
};

template<>
struct db_column_traits<std::string>
{
    static constexpr int column_type_index = SQLITE_TEXT;
};

#endif
