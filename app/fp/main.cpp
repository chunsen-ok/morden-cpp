#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

constexpr bool is_alpha(char c) { return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z'; }
constexpr bool is_digit(char c) { return '0' <= c && c <= '9'; }
constexpr bool is_alpha_digit(char c) { return is_alpha(c) || is_digit(c); }

class Url{};
class UrlScheme{
public:
    UrlScheme(const std::string& scheme)
        : m_scheme(scheme)
    {
    }

    static constexpr bool is_valid_scheme_char(char c) {
        return is_alpha_digit(c) || c == '+' || c == '-' || c == '.';
    }

    static bool is_valid_scheme(const std::string& scheme) {
        return !scheme.empty() && (std::isalpha(scheme.at(0)) != 0) && std::all_of(scheme.begin(), scheme.end(), is_valid_scheme_char);
    }

private:
    std::string m_scheme;
};
class UrlHost{};
class UrlPort{};
class UrlQuery{};
class UrlFragment{};

Url makeUrl(const Url& url);
Url makeUrl(const std::string& url);
Url makeUrl(const UrlScheme& scheme, const UrlHost& host);
Url makeUrl(const UrlScheme& scheme, const UrlHost& host, const UrlQuery& query);
Url makeUrl(const UrlScheme& scheme, const UrlHost& host, const UrlFragment& fragment);
Url makeUrl(const UrlScheme& scheme, const UrlHost& host, const UrlQuery& query, const UrlFragment& fragment);

int main()
{
    // makeUrl(UrlScheme{"http"}, UrlHost{"127.0.0.1"}, UrlQuery("value=1&value=2"));

    return 0;
}
