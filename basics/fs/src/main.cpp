#include <fstream>
#include <iostream>
#include <string>
#include <utility>

class MessageData
{
public:
    int id() const;
    int type() const;
    int states() const;
};

class MessageItem
{
public:
    void layout();
    void paint();
    void update();
};

template<typename T>
class TipMessageItem: public MessageItem
{
public:
    std::string text() const;
};

int main()
{
    return 0;
}
