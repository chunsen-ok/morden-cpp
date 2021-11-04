// MVC 模式
// Model - 业务逻辑与程序状态相关逻辑
// View - 用户界面、内容展示；逻辑最小化，任何逻辑都应与内容展示相关
// Controller - 处理用户输入和交互，负责选择模型和视图；控制应用如何响应请求
#include <iostream>

namespace model {

class Account;
class ChatList;
class Chatting;
class UserPool;
class FriendList;
class GroupList;
class MessageList;
class ChattingGroupMemberList;
class SearchResultList;

class Model
{
public:
    Account account();
    ChatList chats();
    Chatting chatting();
    UserPool users();
    FriendList friends();
    GroupList groups();
    MessageList messages();
    ChattingGroupMemberList chattingGroupMembers();
    SearchResultList searchResults();
};

}

namespace view {

class ChatList
{
public:
    ChatList();
};

class View
{
public:

};

}

class Controller {
public:
    void update(Model model, int role);
};

int main() {
    // todo ...
    return 0;
}
