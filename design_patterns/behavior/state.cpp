// 状态模式
// 将对象中与状态有关的操作抽象成独立的状态类。
#include <iostream>
#include <memory>

class Life;

class LifeState {
public:
    virtual void grow(Life *life) = 0;

    virtual void what_you_want() const {
        std::cout << "Live" << std::endl;
    }
};

class Life
{
public:
    Life(LifeState *s) : m_state(s) { }

    void set_state(LifeState *s) {
        m_state.reset(s);
    }

    void grow_up() {
        std::cout << "What you want now: ";
        m_state->what_you_want();
        m_state->grow(this);
    }

protected:
    std::unique_ptr<LifeState> m_state;
};

class Senior : public LifeState
{
public:
    void grow(Life *life) override
    {
        std::cout << "death" << std::endl;
    }
    void what_you_want() const override
    {
        std::cout << "Enjoy the life." << std::endl;
    }
};

class Adult : public LifeState
{
public:
    void grow(Life *life) override
    {
        life->set_state(new Senior);
    }
    void what_you_want() const override
    {
        std::cout << "Family, money and peace life." << std::endl;
    }
};

class Young : public LifeState
{
public:
    void grow(Life *life) override
    {
        life->set_state(new Adult);
    }
    void what_you_want() const override
    {
        std::cout << "Dream girl" << std::endl;
    }
};

class Child : public LifeState
{
public:
    void grow(Life *life) override
    {
        life->set_state(new Young);
    }
    void what_you_want() const override
    {
        std::cout << "Toys" << std::endl;
    }
};

class Baby: public LifeState {
public:
    void grow(Life *life) override {
        life->set_state(new Child);
    }
    void what_you_want() const override {
        std::cout << "Mami" << std::endl;
    }
};

int main() {
    Life one(new Baby);
    one.grow_up();
    one.grow_up();
    one.grow_up();
    one.grow_up();
    one.grow_up();
    one.grow_up();
    one.grow_up();
    return 0;
}
