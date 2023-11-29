#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

static const char special_character[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
static const char numbers[] = "0123456789";
static const char upper_alphas[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char lower_alphas[] = "abcdefghijklmnopqrstuvwxyz";
constexpr bool is_alpha(char c) { return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z'; }
constexpr bool is_digit(char c) { return '0' <= c && c <= '9'; }
constexpr bool is_alpha_digit(char c) { return is_alpha(c) || is_digit(c); }

#define READ_CONFIG(x) if (value == std::string(#x)) { m##x = "x"; }

int main(int argc, char* argv[])
{
    std::string value;
    READ_CONFIG(Hello)
    return 0;
}
