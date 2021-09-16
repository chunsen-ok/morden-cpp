// Value categories
// glvalue: 
// prvalue: 
// xvalue:
// lvalue: a glvalue, but not xvalue
// rvalue: a prvalue or xvalue
//
// std::move 返回一个右值引用

#include <iostream>
#include <tuple>
#include <algorithm>
#include <type_traits>

template<typename T, const char *Name, int Role>
class Field
{
public:
    Field(): m_value(T()) {}
    const T &value() const { return m_value; }
    void set_value(const T &val) { if (val != m_value) { m_value = val; } }

    constexpr int role() const { return Role; }
    constexpr const char *name() const { return Name; }

private:
    Field(const Field &);
    Field &operator=(const Field &);
    Field(Field&&);
    Field &operator=(Field&&);

    T m_value;
};

namespace {
namespace field {

static const char uid[] = "uid";
static const char name[] = "name";
static const char avatar[] = "avatar";
static const char email[] = "email";
static const char phone[] = "phone";
static const char signature[] = "signature";

}
}

struct AccountInfo
{
    Field<long long, field::uid, 1> uid;
    Field<std::string, field::name, 2> name;
    Field<std::string, field::avatar, 3> avatar;
    Field<std::string, field::email, 4> email;
    Field<std::string, field::phone, 5> phone;
    Field<std::string, field::signature, 6> signature;
};

template<std::size_t M, std::size_t N>
class CStr
{
public:
    constexpr CStr(const char (&key)[M], const char (&val)[N])
    {
        std::copy_n(key, M, m_key);
        std::copy_n(val, N, m_val);
    }

private:
    char m_key[M];
    char m_val[N];
};

struct Emoji 
{
    const char *name{nullptr};
    const char *url{nullptr};
    unsigned int color0{0};
};

static constexpr const Emoji emojis0[] = {
    {"proxy_off", ":/res/icon/proxy_off.png"},
    {"proxy_on", ":/res/icon/proxy_on.png"},
    {"quiz_explain", ":/res/icon/quiz_explain.png"},
    {"quiz_timer", ":/res/icon/quiz_timer.png"},
    {"replies_userpic", ":/res/icon/replies_userpic.png"},
    {"settings_advanced", ":/res/icon/settings_advanced.png"},
    {"settings_chat", ":/res/icon/settings_chat.png"},
    {"settings_edit", ":/res/icon/settings_edit.png"},
    {"settings_edit_name", ":/res/icon/settings_edit_name.png"},
    {"settings_emoji", ":/res/icon/settings_emoji.png"},
    {"settings_faq", ":/res/icon/settings_faq.png"},
    {"settings_folders", ":/res/icon/settings_folders.png"},
    {"settings_information", ":/res/icon/settings_information.png"},
    {"settings_interface_scale", ":/res/icon/settings_interface_scale.png"},
    {"settings_language", ":/res/icon/settings_language.png"},
    {"settings_name", ":/res/icon/settings_name.png"},
    {"settings_notifications", ":/res/icon/settings_notifications.png"},
    {"settings_phone_number", ":/res/icon/settings_phone_number.png"},
    {"settings_privacy_security", ":/res/icon/settings_privacy_security.png"},
    {"settings_stickers", ":/res/icon/settings_stickers.png"},
    {"settings_themes", ":/res/icon/settings_themes.png"},
    {"settings_username", ":/res/icon/settings_username.png"},
    {"stickers_add", ":/res/icon/stickers_add.png"},
};

int main()
{
    AccountInfo account;

    account.uid.set_value(10086);
    account.name.set_value("China");
    account.avatar.set_value("oss://ajlfasd/asdfjasjdfljaksdf");

    constexpr std::size_t emojis0_size = sizeof(emojis0) / sizeof(Emoji);
    static_assert(emojis0_size == 23, "compile timer eval");
    static_assert(emojis0[3].name == "quiz_timer", "sdf");
    for (auto i = 0; i < emojis0_size; ++i) {
        std::cout << emojis0[i].name << std::endl;
    }

    return 0;
}