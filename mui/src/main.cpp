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

struct User
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

using GroupID = int;

enum class GroupRole
{
    Id,
    Name,
    Avatar,
};

struct Group
{
    using Role = GroupRole;
    
    GroupID id;
    std::string name;
    std::string avatar;
};

using ChatViewID = int;

enum class ChatViewRole
{
    Name,
    Avatar,
};

struct ChatViewItem
{
    ChatViewID id;
    std::string name;
    std::string avatar;

    template<typename Data>
    void update(typename Data::Role role, const Data &data)
    {
        if constexpr (std::is_same_v<Data, User>) {
            updateFromUser(role, data);
        } else if constexpr (std::is_same_v<Data, Group>) {
            updateFromGroup(role, data);
        }
    }

private:
    void updateFromUser(UserRole role, const User &data)
    {
        if (UserRole::Name == role) {
            name = data.name;
        } else if (UserRole::Avatar == role) {
            avatar = data.avatar;
        }
    }

    void updateFromGroup(GroupRole role, const Group &data)
    {
        if (GroupRole::Name == role) {
            name = data.name;
        } else if (GroupRole::Avatar == role) {
            avatar = data.avatar;
        }
    }
};

int main() {
    auto user = User{};
    auto group = Group{};
    auto v = ChatViewItem{};

    v.update(UserRole::Name, user);
    v.update(GroupRole::Name, group);

    return 0;
}
