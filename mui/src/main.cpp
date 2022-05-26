#include <vector>
#include <memory>
#include <iostream>
#include <unordered_map>

using UserID = int;

enum class UserRole
{
    Id,
    Name,
    Avatar,
};

struct UserItem
{
    using Role = UserRole;

    UserID id;
    std::string name;
    std::string avatar;
};

class Users
{
public:
    User user(UserID id) const;
};

enum class GroupRole
{
    Name,
    Avatar,
};

struct GroupItem
{
    using Role = GroupRole;
    
    std::string name;
    std::string avatar;
};

enum class ChatViewRole
{
    Name,
    Avatar,
};

struct ChatViewItem
{
    std::string name;
    std::string avatar;

    template<typename Data>
    void update(typename Data::Role role, const Data &data)
    {
        if constexpr (std::is_same_v<Data, UserItem>) {

        } else if constexpr (std::is_same_v<Data, GroupItem>) {

        }
    }
};

int main() {
    auto user = UserItem{};
    auto group = GroupItem{};
    auto v = ChatViewItem{};

    v.update(UserRole::Name, user);
    v.update(GroupRole::Name, group);

    return 0;
}
