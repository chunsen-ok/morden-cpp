// 责任链模式
// 对请求沿着处理对象链传递，直到被处理
#include <iostream>
#include <vector>

#include "misc/world.hpp"

enum class Msg {
    Unknown,
    One,
    Two,
    Tree,
};

struct Request {
    Msg msg;
    std::vector<char> data;
};

class Handler {
public:
    virtual ~Handler() {}

    virtual bool handle(const Request *r) {
        if (m_next) {
            return m_next->handle(r);
        }
        return false;
    }

    void set_next(Handler *next) {
        if (next) {
            m_next = next;
        }
    }

protected:
    Handler *m_next {nullptr};
};

class GuardHandler: public mcpp::Object, public Handler {
public:
    bool handle(const Request *r) override {
        if (r->msg == Msg::Unknown) {
            std::cout << "Message is unknown. Can't be processed." << std::endl;
            return true;
        }

        return Handler::handle(r);
    }
};

class FirstHandler: public mcpp::Object, public Handler {
public:
    bool handle(const Request *r) override {
        if (r->msg == Msg::One) {
            std::cout << "This is message one" << std::endl;
            return true;
        }

        return Handler::handle(r);
    }
};

class SecondHandler: public mcpp::Object, public Handler {
public:
    bool handle(const Request *r) override {
        if (r->msg == Msg::Two) {
            std::cout << "This is message two" << std::endl;
            return true;
        }

        return Handler::handle(r);
    }
};

int main() {
    mcpp::World w;

    auto h1 = new GuardHandler;
    h1->set_object_name("Guard");
    w.add_object(h1);

    auto h2 = new FirstHandler;
    h2->set_object_name("First");
    h1->set_next(h2);
    w.add_object(h2);

    auto h3 = new SecondHandler;
    h3->set_object_name("Second");
    h2->set_next(h3);
    w.add_object(h3);

    Request r;
    r.msg = Msg::Two;

    h1->handle(&r);

    return w.exec();
}
