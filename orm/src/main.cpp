#include <iostream>

class SqlBuilder 
{
public:

};

template<typename T>
struct db_type;

template<>
struct db_type<std::int32_t> {
    static constexpr char name[] = "INT4";
};

template<>
struct db_type<std::int64_t> {
    static constexpr char name[] = "INT8";
};

template<>
struct db_type<std::string> {
    static constexpr char name[] = "TEXT";
};


template<typename T>
struct Field
{
    Field(const std::string &name): m_name(name) {}

    constexpr const char *type() const { return db_type<T>::name; }
    void set_value(const T &value) { m_value = value; }
    const T value() const { return m_value; }
    std::string expr() const
    {
        std::string e;
        e.append(m_name);
        e.append(" ");
        e.append(type());
        return e;
    }

private:
    const std::string m_name;
    T m_value;
};

struct User
{
    Field<int> id{"id"};
    Field<std::string> name{"name"};
    Field<int> age{"age"};
};

int main() {
    User user;
    std::cout << user.id.expr() << std::endl;
    std::cout << user.name.expr() << std::endl;
    std::cout << user.age.expr() << std::endl;
    return 0;
}
