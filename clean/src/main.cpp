#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "chat.hpp"

class DataOne;
class DataTwo;
class DataThree;

class AbstractViewElement
{
public:
    int id() const;
    int ms() const;
};

template<typename T>
class DrivedElement: public T
{
public:

};

template<typename Data, typename View>
class FriendApplyView: public AbstractViewElement
{
public:

};

int main()
{
    auto chats = std::make_shared<Chats>();

    ChatId id{1};

    // find exist one
    if (auto chat = chats->chat(id); chat) {
        chat->pinTop(true);
    }

    // create new
    auto chat = chats->addChat(id);
    chat->beginMultiChange();
    chat->pinTop(true);
    chat->mute(true);
    chat->rtm(12452352);
    chat->endMultiChange();
}
