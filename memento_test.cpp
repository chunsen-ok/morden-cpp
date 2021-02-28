// 备忘录模式
#include <iostream>
#include "misc/world.hpp"

class TextSnapshot {
public:
};

class TextEditor {
public:
    void reset() {
    }

    void append_char(char c) {
        m_text.push_back(c);
    }

    TextSnapshot *snapshot() {
        return nullptr;
    }

    void restore(TextSnapshot *s) {}

protected:
    std::string m_text;
};

int main() {
    mcpp::World w;

    return w.exec();
}
