#ifndef CLEAN_MODEL_HPP
#define CLEAN_MODEL_HPP

#include <string>
#include "data.hpp"
#include "roles.hpp"
#include "actions.hpp"

struct Chat
{

};

struct ChatList
{

};

struct Friend
{

};

struct FriendList
{

};

struct Group
{
};

struct GroupList
{
};

struct Message
{

};

struct MessageList
{

};

struct Model
{
    Data<RChatList, ChatList> chats;
    Data<RFriendList, FriendList> friends;
};

void main_reducer(Model &model, const Action &action)
{
    if (action.is(Action::Update, RChatList)) {
        // reset_chats();
    } else if (action.is(Action::Update, RFriendList)) {
        // reset_friends();
    } // else if (model.chats->contains(action.role())) {
        // chats_reducer(model.chats, action);
    // } else if (model.friends->contains(action.role())) {
        // friends_reducer(model.friends, action);
    // }
}

#endif
