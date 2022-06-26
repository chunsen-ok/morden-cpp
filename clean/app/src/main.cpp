#include <iostream>
#include <memory>

struct PeerId
{
    int type;
    std::int64_t uid;
};

class Peer
{
public:
    Peer(const PeerId &id): mId(id) {}
    virtual ~Peer() = default;

    PeerId id() const { return mId; }
    
private:
    PeerId mId;
};

class User: public Peer
{
public:

};

class Group: public Peer
{
public:

};

class SysUser: public Peer
{
public:
};

class FileTransfer: public Peer
{
public:
    FileTransfer(User *user);

    std::string name() const;
    std::string avatar() const;
};

int main() {
    // ...
}
