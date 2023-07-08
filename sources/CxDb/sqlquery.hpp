#ifndef MCPP_SQLQUERY_HPP
#define MCPP_SQLQUERY_HPP

#include <string>
#include <memory>

namespace mcpp {

class Database;
class SqlQueryPrivate;
class SqlQuery
{
public:
    SqlQuery(const Database& db);
    ~SqlQuery();

    bool prepare(const std::string& sql);
    bool step();
    void reset();

    int bind_double(int index, double value);
    int bind_int(int index, int value);
    int bind_int64(int index, std::int64_t value);
    int bind_text(int index, const std::string& value);
    int bind_blob(int index, const std::string& value);
    int bind_null(int index);

    double value_double(int index);
    int value_int(int index);
    std::int64_t value_int64(int index);
    const std::uint8_t* value_text(int index);
    const void* value_blob(int index);

    bool has_error() const;
    const char* error_msg() const;
    
private:
    std::unique_ptr<SqlQueryPrivate> d;
};

}

#endif
