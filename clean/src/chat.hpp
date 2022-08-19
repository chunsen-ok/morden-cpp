#ifndef CHAT_HPP
#define CHAT_HPP

#include <vector>
#include <memory>

using ChatId = std::int64_t;

enum class ChatRole
{
    Seq,
    Mute,
    Time,
};

class Chats;
class Chat: public std::enable_shared_from_this<Chat>
{
public:
    template<typename ... Args>
    static std::shared_ptr<Chat> create(const std::shared_ptr<Chats>& chats, Args ... args)
    {
        return std::shared_ptr<Chat>(new Chat(chats, std::forward<Args>(args)...));
    }

    ChatId id() const { return mId; }

    void pinTop(bool pin = true) {}

protected:
    Chat(const std::shared_ptr<Chats>& chats, ChatId id)
        : mId(id)
        , mPin(false)
    {}

private:
    ChatId mId;

    bool mPin;
};

class Chats: public std::vector<std::shared_ptr<Chat>>, public std::enable_shared_from_this<Chats>
{
public:
    using Element = std::shared_ptr<Chat>;
    
    Element chat(ChatId id) const
    {
        auto it = std::find_if(cbegin(), cend(), [id](const Element& chat){ return chat->id() == id; });
        if (it != cend()) { return *it; }
        return nullptr;
    }
    Element addChat(ChatId id)
    {
        
    }

    void pinTop(ChatId id, bool on = true)
    {
        auto it = std::find_if(cbegin(), cend(), [id](const Element& chat){ return chat->id() == id; });
        if (it != cend()) {
            (*it)->pinTop(on);
        }
    }

private:
    void change(const std::vector<ChatRole>& roles, const Element& data)
    {
        // notify changes;
    }

};

#endif
