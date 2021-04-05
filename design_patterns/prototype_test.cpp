#include <iostream>
#include <unordered_map>

class Prototype {
public:
    virtual ~Prototype() {
        std::cout << "Drop prototype" << std::endl;
    }

    virtual Prototype *clone() {
        Prototype *p = new Prototype;
        p->set_name(m_name);
        return p;
    }

    void set_name(const std::string &name) {
        m_name = name;
    }

    const std::string &name() const {
        return m_name;
    }

protected:
    std::string m_name;
};

class Registry {
public:
    ~Registry() {
        for (auto &pair: m_protos) {
            delete pair.second;
        }
        m_protos.clear();
    }

    void add_prototype(const std::string &t, Prototype *proto) {
        auto it = m_protos.find(t);
        if (it != m_protos.end()) {
            Prototype *p = it->second;
            delete p;
        }
        proto->set_name(t);
        m_protos.insert({t, proto});
    }

    Prototype *clone(const std::string &t) {
        auto it = m_protos.find(t);
        if (it != m_protos.end() && it->second) {
            Prototype *p = it->second;
            return p->clone();
        }
        return nullptr;
    }

protected:
    std::unordered_map<std::string, Prototype *> m_protos;
};

class Car: public Prototype {
public:
    Prototype *clone() override {
        Car *c = new Car;
        c->m_price = m_price;
        c->m_name = m_name;
        return c;
    }

    void set_price(int price) {
        m_price = price;
    }

    int price() const {
        return m_price;
    }

protected:
    int m_price{0};
};

class Fly: public Prototype {
public:
    Prototype *clone() override {
        Fly *f = new Fly;
        f->m_weight = m_weight;
        f->m_name = m_name;
        return f;
    }

    void set_weight(int w) {
        m_weight = w;
    }

    int weight() const {
        return m_weight;
    }

protected:
    int m_weight {0};
};

int main() {
    Registry r;

    r.add_prototype("car", new Car);
    r.add_prototype("fly", new Fly);

    Prototype *obj0 = r.clone("car");
    if (obj0) {
        std::cout << obj0->name() << std::endl;
        delete obj0;
    }

    Prototype *obj1 = r.clone("fly");
    if (obj1) {
        std::cout << obj1->name() << std::endl;
        delete obj1;
    }

    return 0;
}
