#include <iostream>
#include <string>
#include <memory>

class SqlBuilder
{
public:
    template<typename T>
    void create()
    {
        const T t;
        std::cout << "CREATE TABLE IF NOT EXISTS " << T::name() << "(";
        std::cout << ");";
    }
};

class Field
{
public:

};
using FieldPtr = std::shared_ptr<Field>;

struct SysKv
{
    static std::string name() { return "sys_kv"; }

    
    int role;
    std::string name;
    std::string value;
    FieldPtr ext0;
    FieldPtr ext1;
    FieldPtr ext2;
};

int main(int argc, char *argv[])
{
    SqlBuilder sql;
    sql.create<SysKv>();

    return 0;
}
