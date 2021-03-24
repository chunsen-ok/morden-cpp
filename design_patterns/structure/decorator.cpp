// 装饰模式
// 通过将被装饰的对象放入装饰器对象中，为被装饰的对象添加新的功能。
// 对接口进行重载，调用被封装对象的方法前，添加一些操作。
// 多个适配器可以嵌套装饰，实现功能的多层装饰。
#include <iostream>
#include <string>
#include <string_view>

constexpr char char_distance() {
    return 'a' - 'A';
}

class StrFormatter {
public:
    virtual ~StrFormatter() {}

    void set_wrappee(StrFormatter *wrappee) {
        m_wrappee = wrappee;
    }

    virtual std::string format(std::string &&str) {
        if (m_wrappee) {
            return m_wrappee->format(std::move(str));
        }
        return str;
    }
protected:
    StrFormatter *m_wrappee {nullptr};
};

class ToUpperFomatter: public StrFormatter {
public:
    std::string format(std::string &&str) override {
        // 执行原有功能
        std::string s = StrFormatter::format(std::move(str));

        // 添加了额外的功能
        for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
            const char ch = *it;
            if ('a' <= ch && ch <= 'z') {
                *it = ch - char_distance();
            }
        }

        return s;
    }
};

class ZeroFormatter: public StrFormatter {
public:
    std::string format(std::string &&str) override {
        // 执行原有功能
        std::string s = StrFormatter::format(std::move(str));

        // 添加了额外的功能
        for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
            const char ch = *it;
            if (ch < 'A' || 'Z' < ch) {
                *it = 'A';
            }
        }

        return s;
    }
};

int main() {
    std::string s{"Hello World !"};
    ToUpperFomatter f1;

    ZeroFormatter f2;
    f2.set_wrappee(&f1);
    s = f2.format(std::move(s));

    std::cout << s << std::endl;

    return 0;
}
