#ifndef MCPP_DATABASE_HPP
#define MCPP_DATABASE_HPP

#include <string>
#include <memory>

namespace mcpp {

class SqlQuery;
class DatabasePrivate;
class Database
{
    friend SqlQuery;
public:
    Database();
    Database(const std::string& path);
    ~Database();

    bool is_open() const;
    void open(const std::string& path);
    void close();

    bool has_error() const;
    const char* error_msg() const;
    
private:
    std::unique_ptr<DatabasePrivate> d;
};

}

#endif
