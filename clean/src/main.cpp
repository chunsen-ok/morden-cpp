#include <iostream>
#include <string>
#include <memory>
#include <vector>

class Canvas: public std::enable_shared_from_this<Canvas>
{
public:
    using Ptr = std::shared_ptr<Canvas>;
    using WeakPtr = std::weak_ptr<Canvas>;

public:
    Canvas() {}
    virtual ~Canvas() = default;

    void append_element(const std::shared_ptr<Element> &el)
    {
        if (el) {
            m_children.push_back(el);
        }
    }

protected:
     std::vector<std::shared_ptr<Element>> m_children;
};

class Element: public std::enable_shared_from_this<Element>
{
public:
    using Ptr = std::shared_ptr<Element>;
    using WeakPtr = std::shared_ptr<Element>;

    explicit Element(const Canvas::Ptr& canvas)
        : m_canvas{canvas}
    {}

    virtual ~Element()
    {
        std::cout << "~Element\n";
    }

private:
    Element::WeakPtr m_parent;
    Canvas::WeakPtr  m_canvas;
};

int main()
{
    auto canvas = std::make_shared<Canvas>();

    auto el0 = std::make_shared<Element>(canvas);
    canvas->append_element(el0);
}
