// 适配器模式
// 对接两个接口不兼容的系统，添加适配器使两者可以交互
#include <iostream>

class Program
{
public:
    virtual ~Program() {}
    
    virtual void greeting() const {
        std::cout << "Ok!" << std::endl;
    }
};

void program_info(const Program *const p)
{
    p->greeting();
}

class Program2
{
public:
    void hello(const std::string &name) const {
        std::cout << "Hello, I'm " << name << std::endl;
    }
};

// program_info系统中，需要使用Program的对象，但是我们提供的是Program2，
// 两者无法直接一起工作。在两者都不便于修改的情况下，可以使用适配器模式，使
// 两者可以一起工作。
// 通过继承被适配对象类型，重写需要适配的方法。在该方法中实际调用另一系统的接口，
// 实现两者适配。
class Adapter: public Program
{
public:
    void set_program2(Program2 *p) {
        m_p = p;
    }
    void set_name(const std::string &name) {
        m_name = name;
    }

    void greeting() const override {
        if (m_p) {
            m_p->hello(m_name);
        }
    }
protected:
    Program2 *m_p {nullptr};
    std::string m_name;
};

int main() {
    Program p;
    program_info(&p);

    Program2 p2;
    // 两者接口不兼容，无法直接调用
    // program_info(&p2);

    // 使用一个适配器，使两者兼容
    Adapter adapter;
    adapter.set_program2(&p2);
    adapter.set_name(std::string{"Adapter"});
    program_info(&adapter);

    return 0;
}
