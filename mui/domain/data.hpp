#ifndef MUI_DATA_HPP
#define MUI_DATA_HPP

#include <common/types.hpp>
#include <cstdint>

namespace mui {

enum UserType {
    User,
    System,
};

using GroupID = std::int64_t;

struct UserID {
    std::int64_t uid;
    UserType tp;
};

class UserData;
class GroupData;
class AppData
{
public:
private:
    UserData *mUsers{nullptr};
    GroupData *mGroups{nullptr};
};

class UserData
{
public:

};

class GroupData 
{
public:

};

class GroupMembersData
{
public:
    String memberName(GroupID group, UserID user, bool anonymous = false);
};

}

#endif
