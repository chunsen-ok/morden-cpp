#ifndef CLEAN_ROLES_HPP
#define CLEAN_ROLES_HPP

enum Role
{
    RNone = 0,

    RChatList,
    RChat,
    RChatText,
    
    RFriendList,
    RFriend,
    RFriendName,

    RMessageList,
    RMessage,
    RMessageContent,
};

using Variant = int;

#endif
