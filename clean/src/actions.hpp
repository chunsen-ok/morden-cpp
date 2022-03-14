#ifndef CLEAN_ACTION_HPP
#define CLEAN_ACTION_HPP

#include "roles.hpp"

class Action
{
public:
    enum Type
    {
        Update = 0,
        Add,
        Delete,
        Other,
    };

    Action(Type tp, Role role): m_type(tp), m_role(role) {}

    bool operator==(const Action &other) const {
        return other.m_role == m_role && other.m_type == m_type;
    }

    Type action() const { return m_type; }
    Role role() const { return m_role; }
    bool is(Type tp, Role role) const { return m_type == tp && m_role == role; }

private:
    Type m_type{Update};
    Role m_role{RNone};
};

class UpdateAction: public Action
{
public:
    UpdateAction(Role role, const Variant &data)
        : Action(Update, role)
        , m_data(data) {}

    Variant data() const { return m_data; }

private:
    Variant m_data;
};

class AddAction: public Action
{
public:
    AddAction(Role role, const Variant &data)
        : Action(Add, role)
        , m_data(data) {}

    Variant data() const { return m_data; }

private:
    Variant m_data;
};

class DeleteAction: public Action
{
public:
    DeleteAction(Role role)
        : Action(Delete, role) {}
};

#endif
