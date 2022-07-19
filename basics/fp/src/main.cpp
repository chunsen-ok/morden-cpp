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

int main()
{
    SessionApi api;

    api.post(createPost());
    return 0;
}
