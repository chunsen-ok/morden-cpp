#include <iostream>
#include <vector>
#include <reactive.hpp>

template<typename T>
struct Size
{
    T width{0}, height{0};

    Size &operator=(const Size &s) {
        width = s.width;
        height = s.height;
        return *this;
    }
};

using Sizei = Size<int>;
using Sizef = Size<double>;


template<typename T>
struct Point
{
    T x{0}, y{0};

    Point &operator=(const Point &p) {
        x = p.x;
        y = p.y;
        return *this;
    }
};

using Pointi = Point<int>;
using Pointf = Point<double>;

class Widget
{
public:
    explicit Widget(Widget *parent = nullptr): m_parent(parent)
    {
        if (m_parent) {
            m_parent->append_child(this);
        }
    }

    ~Widget() {
        for (auto it = m_children.begin(); it != m_children.end(); ++it) {
            Widget *c = *it;
            if (c) {
                delete c;
            }
        }
        m_children.clear();
    }

    void append_child(Widget *child) {
        m_children.push_back(child);
    }

    Property<Sizef> size;
    Property<Pointf> position;

private:
    Widget *m_parent;
    std::vector<Widget*> m_children;
};


int main(int argc, char *argv[])
{
    reactive::start(12342)
    .then([](int v) {
        std::cout << "Then: " << v << std::endl;
        return std::string{"Hello"};
    })
    .then([](const std::string &v){
        std::cout << "Then: " << v << std::endl;
        return 0;
    })
    .done();

    Property<int> value{2354};
    value.changed([](int v){
        std::cout << "property changed: " << v << std::endl;
        return v * 2;
    })
    .then([](int v){
        std::cout << "changed again: " << v << std::endl;
        return 0;
    });

    Widget widget;
    
    widget.size
    .changed([](const Sizef &s){
        return Sizef{};
    });
    
    return 0;
}