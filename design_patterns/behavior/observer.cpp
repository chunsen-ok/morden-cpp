// 观察者模式
// 观察其他对象的改变，并作出响应。
#include <iostream>
#include <vector>
#include <algorithm>

class Subscriber {
public:
    virtual ~Subscriber() {}
    virtual void update() {
        std::cout << "Do something." << std::endl;
    }
};

class One: public Subscriber {
public:
    void update() override {
        std::cout << "I'm doing what I want to do." << std::endl;
    }
};

class Two: public Subscriber {
public:
    void update() override {
        std::cout << "Do nothing." << std::endl;
    }
};

class Publisher {
public:
    virtual ~Publisher() { }

    void add_subscriber(Subscriber *s){
        if (s) {
            m_subscribers.push_back(s);
        }
    }

    void remove_subscriber(const Subscriber *s) {
        if (s) {
            auto it = std::find(m_subscribers.begin(), m_subscribers.end(), s);
            m_subscribers.erase(it);
        }
    }

    virtual void notify() {
        for (Subscriber *s: m_subscribers) {
            s->update();
        }
    }

protected:
    std::vector<Subscriber*> m_subscribers;
};

int main() {
    Publisher publisher;
    
    Subscriber s1;
    publisher.add_subscriber(&s1);

    One s2;
    publisher.add_subscriber(&s2);

    Two s3;
    publisher.add_subscriber(&s3);

    publisher.notify();

    publisher.remove_subscriber(&s2);

    publisher.notify();
    
    return 0;
}
