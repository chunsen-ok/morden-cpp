#include <vector>
#include <string>
#include <iostream>
#include <memory>

struct PeerId
{
    enum Type
    {
        None = 0,
        User,
        Group,
        System,
    };

    constexpr PeerId(const PeerId &other)
        : mType(other.mType)
        , mUid(other.mUid)
    {}

    constexpr PeerId(PeerId &&other)
        : mType(std::move(other.mType))
        , mUid(std::move(other.mUid))
    {}

    constexpr PeerId &operator=(const PeerId &other)
    {
        mType = other.mType;
        mUid  = other.mUid;
        return *this;
    }

    constexpr PeerId &operator=(PeerId &&other)
    {
        mType = std::move(other.mType);
        mUid = std::move(other.mUid);
        return *this;
    }

    constexpr Type type() const { return mType; }
    constexpr std::int64_t uid() const { return mUid; }

    static constexpr PeerId none() { return PeerId{PeerId::None, 0}; }
    static constexpr PeerId user(std::int64_t uid) { return PeerId{PeerId::User, uid}; }
    static constexpr PeerId group(std::int64_t uid) { return PeerId{PeerId::Group, uid}; }
    static constexpr PeerId system(std::int64_t uid) { return PeerId{PeerId::System, uid}; }

    constexpr friend bool operator==(const PeerId &lhs, const PeerId &rhs)
    {
        return lhs.mType == rhs.mType && lhs.mUid == rhs.mUid;
    }

    constexpr friend bool operator!=(const PeerId &lhs, const PeerId &rhs)
    {
        return !(lhs == rhs);
    }

private:
    PeerId() = default;
    constexpr PeerId(Type type, std::int64_t uid)
        : mType(type)
        , mUid(uid)
    {}

    Type mType;
    std::int64_t mUid;
};

class Chat: public std::enable_shared_from_this<Chat>
{
public:
    using Ptr = std::shared_ptr<Chat>;
    using WeakPtr = std::weak_ptr<Chat>;

    [[nodiscard]] Ptr create() { return Ptr{new Chat}; }

    PeerId id() const { return mId; }

protected:
    Chat()
        : mId{PeerId::none()}
    {}

private:
    PeerId mId;
};

class Session: public std::enable_shared_from_this<Session>
{
public:
    using Ptr = std::shared_ptr<Session>;

    [[nodiscard]] static Ptr create() { return Ptr(new Session); }

    Chat::Ptr chat(const PeerId &id) const
    {
        for (const auto &chat: mChats) {
            if (chat->id() == id) {
                return chat;
            }
        }
        return Chat::Ptr{};
    }

protected:
    Session() = default;

private:
    std::vector<Chat::Ptr> mChats;
};

constexpr bool test(const PeerId &id, const PeerId &other)
{
    auto t = id;
    return t == other;
}

int main()
{
    return 0;
}
