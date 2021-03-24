// 组合模式
// 众多对象组合成树状结构，可以像一个独立对象一样使用
// 内部通过递归方式操作所有对象
#include <iostream>
#include <vector>

class Object {
public:
    virtual ~Object() {
        for (Object *c : m_children) {
            if (c) {
                delete c;
            }
            m_children.clear();
        }
    }

    void append(Object *child) {
        if (child) {
            m_children.push_back(child);
        }
    }

    // 通过递归调用直接子节点的方法，实现与对象树的所有对象的交互
    int count() const {
        int n = 1;
        for (const Object *const c : m_children) {
            n += c->count();
        }
        return n;
    }
protected:
    std::vector<Object*> m_children;
};

int main() {
    Object root;
    Object *obj1 = new Object;
    root.append(obj1);
    Object *obj2 = new Object;
    root.append(obj2);

    Object *obj11 = new Object;
    obj1->append(obj11);
    Object *obj12 = new Object;
    obj1->append(obj12);

    Object *obj21 = new Object;
    obj2->append(obj21);
    Object *obj22 = new Object;
    obj2->append(obj22);

    std::cout << "Total objects: " << root.count() << std::endl;

    return 0;
}
