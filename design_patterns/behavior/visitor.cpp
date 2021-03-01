// 访问者模式
// 将操作/算法与其作用对象分离。
// 操作是一个类层次（访问者），作用的对象是另一个类层次。（元素）

#include <iostream>
#include <vector>

class Drawable;
class Rectangle;
class Ellipse;
class Text;

class Painter {
public:
    virtual ~Painter() {}

    virtual void drawRect(const Rectangle *r) {
        std::cout << "Draw rectangle" << std::endl;
    }
    virtual void drawEllipse(const Ellipse *e) {
        std::cout << "Draw ellipse" << std::endl;
    }
    virtual void drawText(const Text *t) {
        std::cout << "Draw text" << std::endl;
    }
};

class Drawable {
public:
    virtual ~Drawable() {
        for (Drawable *item: m_items) {
            if (item) { delete item; }
        }
        m_items.clear();
    }

    virtual void draw(Painter *p) {
        for (Drawable *item: m_items) {
            item->draw(p);
        }
    }

    void add_child_item(Drawable *item) {
        if (item) { m_items.push_back(item); }
    }
protected:
    std::vector<Drawable*> m_items;
};

class Rectangle: public Drawable {
public:
    void draw(Painter *p) override {
        p->drawRect(this);
        Drawable::draw(p);
    }
};

class Ellipse: public Drawable {
public:
    void draw(Painter *p) override {
        p->drawEllipse(this);
        Drawable::draw(p);
    }
};

class Text: public Drawable {
public:
    void draw(Painter *p) override {
        p->drawText(this);
        Drawable::draw(p);
    }
};

int main() {
    Drawable *scene = new Drawable;
    
    Rectangle *rect = new Rectangle;
    scene->add_child_item(rect);

    Ellipse *ell = new Ellipse;
    scene->add_child_item(ell);

    Text *t = new Text;
    scene->add_child_item(t);

    Painter *p = new Painter;

    scene->draw(p);

    delete scene;
    delete p;

    return 0;
}
