// 模板方法模式
// 接口定义一系列方法，按照固定顺序调用。子类可扩展全部或部分接口。
#include <iostream>

class ProcessTemplate {
public:
    virtual ~ProcessTemplate() {}

    void exec() {
        stepOne();
        stepTwo();
        stepThree();
    }

protected:
    void stepOne() {
        std::cout << "Always first!" << std::endl;
    }
    virtual void stepTwo() {
        std::cout << "default step 2" << std::endl;
    }
    virtual void stepThree() {
        std::cout << "default step 3" << std::endl;
    }
};

class CustomProcess: public ProcessTemplate {
public:
protected:
    void stepTwo() override {
        std::cout << "My custom step 2" << std::endl;
    }

    void stepThree() override {
        std::cout << "My custom step 3" << std::endl;
    }
};

class TemplateMethod {
public:
    ~TemplateMethod() {
        if (m_process) {
            delete m_process;
        }
    }
    
    void set_template(ProcessTemplate *process) {
        if (m_process) {
            delete m_process;
        }
        m_process = process;
    }

    void do_works() {
        m_process->exec();
    }

protected:
    ProcessTemplate *m_process;
};

int main() {
    TemplateMethod client;
    client.set_template(new ProcessTemplate);
    client.do_works();
    client.set_template(new CustomProcess);
    client.do_works();

    return 0;
}
