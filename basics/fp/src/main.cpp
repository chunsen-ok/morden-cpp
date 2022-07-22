#include <iostream>
#include <string>
#include <functional>

using PostParam = std::pair<std::string, std::string>;

class SessionApi
{
public:
    void post(const PostParam &param)
    {
        // ...
    }
};

std::string makeCreatePost()
{
    return std::string{};
}

auto createPost() -> PostParam
{
    return std::make_pair(std::string{"/user/groups"}, makeCreatePost());
}

class AbstractMainWindow
{
public:

};

class PlatformMainWindow: public AbstractMainWindow
{
public:

};

class MainWindow: public PlatformMainWindow
{
public:

};

int main()
{
    SessionApi api;

    api.post(createPost());
    return 0;
}
