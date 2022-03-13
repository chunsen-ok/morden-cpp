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
    };

    Action(Role role, Type action): m_role(role), m_action(action) {}

    bool operator==(const Action &other) const {
        return other.m_role == m_role && other.m_action == m_action;
    }

    Role role() const { return m_role; }
    Type action() const { return m_action; }

private:
    Role m_role{RNone};
    Type m_action{Update};
};

class UpdateAction: public Action
{
public:
    UpdateAction(Role role, const Variant &data)
        : Action(role, Update)
        , m_data(data) {}

    Variant data() const { return m_data; }

private:
    Variant m_data;
};

class AddAction: public Action
{
public:
    AddAction(Role role, const Variant &data)
        : Action(role, Add)
        , m_data(data) {}

    Variant data() const { return m_data; }

private:
    Variant m_data;
};

class DeleteAction: public Action
{
public:
    DeleteAction(Role role): Action(role, Delete) {}
};

#endif
