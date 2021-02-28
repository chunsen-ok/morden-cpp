// 桥接模式
// 将抽象与实现分离到不同类层次。抽象层和实现层都有自己的抽象接口。
// 通过两个层次的接口将抽象与实现关联，称之为桥接。
// 抽象和实现可以分别扩展，它们通过组合的方式结合。
//
// 抽象层可在运行时切换实现；
// 一个实现也可以被抽象层的多个对象共享；
#include <iostream>

namespace mcpp {
    // 抽象层和实现层通过两个层次的接口进行桥接。

    // 实现层的接口
    class Implementor {
    public:
        virtual ~Implementor() {}

        virtual void operation() {}
    };

    // 抽象层的接口
    class Abstraction {
    public:
        virtual ~Abstraction() {}

        void set_impl(Implementor *impl) {
            m_impl = impl;
        }

        void operation() {
            if (m_impl) { m_impl->operation(); }
        }

    protected:
        Implementor *m_impl {nullptr};
    };
}

int main () {
    return 0;
}

