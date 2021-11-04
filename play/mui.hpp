#ifndef PLAY_ARCHITECTURE_HPP
#define PLAY_ARCHITECTURE_HPP

#include <vector>

/*
存在的问题是：
1. 编写代码重复度高（搭建新的界面、模型类型，关联两者时，代码差不多）
2. 界面和模型数据关联有些麻烦，甚至可能存在运行效率问题
3. 基础设施的数据、资源变化必须通过model来关联
3. DataRole 膨胀
*/

namespace play {

namespace infras {

class NetworkManager
{
public:

};

}

namespace model {

class Account;
class UserPool;
class MessageList;
class ChatList
{
public:
    // 依赖注入
    ChatList(UserPool users);
};

class FriendList
{
public:
    FriendList();
};

class GroupList;

class AppModel
{
public:
    Account account();
    UserPool users();

    ChatList chats();
    FriendList friends();
    GroupList groups();
};

}

namespace ui {

class TitleBar;
class MainMenu;
class ChatList;
class MessageList;
class FriendList;
class GroupList;

class ChatList
{
public:
    ChatList(model::ChatList chats)
    {
        binding(chats, &model::ChatList::data_changed, this, [](int index, const std::vector<int> &roles){
            controller.update(index, roles);
        });

        binding(chats, &model::ChatList::row_inserted, this, [](int start, int end){
            // ...
            update(start, end);
        });
    }

protected:
    ListController controller;
};

class ListController
{
public:
    ListController(model::ChatList model, ChatList view)
    {

    }

    // 简单逻辑没有必要使用controller
    // 复杂逻辑、或者数据的转换由controller负责
    void update(int index, const std::vector<int> &roles) {

        // 涉及数据的转换
        if (roles.contains(role::Avatar)) {
            util::clearAvatarCache();
        }

        view.update(index);
    }
};


class MainWindow
{
public:
    MainWindow(model::AppModel model)
    {
        // model-view bindings
        chats.set_model(model.chats);
    }

private:
    TitleBar title;
    MainMenu menu;
    ChatList chats;
    MessageList messages;
};

}

namespace test {

void start() {

}

}

}

#endif
