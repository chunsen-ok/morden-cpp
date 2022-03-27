#include <iostream>

template<typename T>
void create()
{
    T table;

    std::cout << "CREATE TABLE IF NOT EXISTS " << table.table_name() << std::endl;
}

enum FieldType 
{
    TEXT = 0,
    INTEGER,
    REAL,
    NUMERIC,
    BLOB,
};

template<typename T>
class Field
{
public:

    Field(const std::string &name, FieldType type)
        : m_type(type), m_name(name) {}

    FieldType type() const { return m_type; }
    std::string name() const { return m_name; }

private:
    FieldType m_type;
    std::string m_name;
};

struct User
{
    static std::string table_name() { return "user"; }
    
    void enumerate_fields()
    {

    }

    Field<int> num{"num", INTEGER};
    Field<std::string> name{"name", TEXT};
};

int main(int argc, char *argv[])
{
    create<User>();
    auto p = &User::num;
    std::cout << p << &User::name << std::endl;

    User u;
    std::cout << (u.*p).name() << std::endl;
    return 0;
}
