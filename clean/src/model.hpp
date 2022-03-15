#ifndef CLEAN_MODEL_HPP
#define CLEAN_MODEL_HPP

#include <string>
#include "data.hpp"
#include "roles.hpp"
#include "actions.hpp"

struct Chat
{
    enum Role
    {
        PinTop = RUserRole + 1,
        Timestamp,
        Mute,
        Avatar,
        Name,
        Message,
    };

    int pin_top;
    int ms;
    bool mute;
    std::string avatar;
    std::string name;
    std::string msg;
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
};

#endif
