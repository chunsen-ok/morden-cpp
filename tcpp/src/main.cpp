#include <iostream>
#include <string>

class CanvasData
{
public:
    CanvasData() {
        std::cout << "CanvasData" << std::endl;
    }
    ~CanvasData() {
        std::cout << "~CanvasData" << std::endl;
    }
};

class CanvasItem
{
public:
    CanvasItem()
        : m_data(new CanvasData)
    {
        std::cout << "CanvasItem" << std::endl;
    }
    CanvasItem(CanvasItem &&other) noexcept
        : m_data(std::exchange(other.m_data, nullptr))  {}
    ~CanvasItem() {
        std::cout << "~CanvasItem" << std::endl;
        if (m_data) {
            delete m_data;
        }
        m_data = nullptr;
    }

    CanvasItem &operator=(CanvasItem &&other) noexcept {
        if (this != &other) {
            m_data = std::exchange(other.m_data, nullptr);
        }
        return *this;
    }

private:
    CanvasData *m_data;
};

int main() {
    CanvasItem a;
    auto b = std::move(a);
    return 0;
}
