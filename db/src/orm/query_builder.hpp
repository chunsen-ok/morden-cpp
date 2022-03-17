#ifndef MUI_QUERY_BUILDER_HPP
#define MUI_QUERY_BUILDER_HPP

#include <string>
#include <vector>

class DbColumn
{
public:
    DbColumn(const std::string &name, const std::string &type)
        : m_name(name)
        , m_type(type) {}

    const std::string &name() const { return m_name; }

    std::string to_string() const
    {
        return m_name + " " + m_type;
    }

private:
    std::string m_name;
    std::string m_type;
};

class DbTable
{
public:
    DbTable(const std::string &name): m_name(name) {}

    void set_pkeys(const std::vector<std::string> &keys)
    {
        m_pkeys = keys;
    }

    void add_column(const DbColumn &column)
    {
        for (const auto &col: m_columns) {
            if (col.name() == column.name()) {
                return;
            }
        }

        m_columns.push_back(column);
    }

    void migrate()
    {
        
    }

private:
    std::vector<std::string> m_pkeys;
    std::string m_name;
    std::vector<DbColumn> m_columns;
};

class QueryBuilder
{
public:

};

#endif
