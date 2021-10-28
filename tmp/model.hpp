#ifndef FIELD_HPP
#define FIELD_HPP

#include <string>

/// Usage: Field<int, 1> uid{"uid"};
/// std::cout << uid.name() << ", " << uid.value() << ", " << uid.role() << std::endl;
/// <<- "uid, 0, 1"
template<typename Type, int Role>
class Field 
{
public:
    Field(const char *name)
        : m_name(name)
        , m_value(Type()) {}

    std::string name() const {
        return std::string(m_name);
    }

    void set_value(const Type &val) {
        m_value = val;
    }
    
    const Type &value() const {
        return m_value;
    }

    int role() const {
        return Role;   
    }

private:
    const char *m_name;
    Type m_value;
};

class Item
{
public:
    int idt;
    long long uid;
    std::string name;
    std::string avatar;
};

class Model
{
public:

private:
};

#include <iostream>

namespace test {

struct Account
{
    Field<long long, 1> uid{"uid"};
    Field<int, 2> type{"tp"};
    Field<std::string, 3> name{"name"};
};

void test_field()
{
    std::cout << "--- test_field ---" << std::endl;

    Field<long long, 1> uid{"uid"};
    std::cout << uid.name() << ", " << uid.value() << ", " << uid.role() << std::endl;

    Account account;
    account.uid.set_value(352623);
    account.type.set_value(46);
    account.name.set_value("Liu Chunsen");
    std::cout << account.uid.name() << ", " << account.uid.value() << ", " << account.uid.role() << std::endl;
    std::cout << account.type.name() << ", " << account.type.value() << ", " << account.type.role() << std::endl;
    std::cout << account.name.name() << ", " << account.name.value() << ", " << account.name.role() << std::endl;
}

}

#endif
