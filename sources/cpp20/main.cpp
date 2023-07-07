#include <vector>
#include <iostream>
#include <unordered_map>

using UserId = int;
using GroupId = int;
using MemberId = int;

class User
{
public:
    using Ptr = std::shared_ptr<User>;
};

class Group
{
public:
    using Ptr = std::shared_ptr<Group>;
};

class GroupMember
{
public:
    using Ptr = std::shared_ptr<GroupMember>;
};

class Chat
{
public:
    using Ptr = std::shared_ptr<Chat>;

    void sendMessage();
    void receiveMessage();
};

template<typename T>
class Promise;

class AppState
{
public:
    GroupMember::Ptr groupMember(GroupId groupId, MemberId memberId) const;
    Promise<GroupMember::Ptr> groupMemberAsync(GroupId groupId, MemberId memberId);
    void fetchGroupMember(GroupId groupId, MemberId memberId);

    void signalUserChanged();
    void signalGroupMemberAdded();
    void signalGroupMemberRemoved();

private:
    using GroupMembers = std::unordered_map<MemberId, GroupMember::Ptr>;

    std::unordered_map<UserId, User::Ptr> mUsers;
    std::unordered_map<GroupId, Group::Ptr> mGroups;
    std::unordered_map<GroupId, GroupMembers> mGroupMembers;
    std::vector<Chat::Ptr> mChats;
};

int main(int argc, char* argv[])
{
    AppState state;

    return 0;
}
