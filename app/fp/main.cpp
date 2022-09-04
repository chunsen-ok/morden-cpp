#include <iostream>
#include <string>
#include <variant>
#include <algorithm>
#include <functional>

static const char special_character[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
static const char numbers[] = "0123456789";
static const char upper_alphas[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char lower_alphas[] = "abcdefghijklmnopqrstuvwxyz";

// url: https://www.server.com/path#section?key=value

enum class Method
{
    Get,
    Post,
    Put,
    HEAD,
    OPTION,
};

class Scope
{

};

class Route
{
    friend class RouteBuilder;
public:

private:
    Method mMethod;
    std::string mPath;
};

class RouteBuilder
{
public:
    operator Route()
    {
        return std::move(mRoute);
    }

    RouteBuilder& method();
    RouteBuilder& path();
    RouteBuilder& handler();
    RouteBuilder& guard();
    RouteBuilder& middleware();

private:
    Route mRoute;
};

int main(int argc, char* argv[])
{
    return 0;
}

// 状态机
// 图
// 代数数据类型