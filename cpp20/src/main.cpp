#include <iostream>
#include <vector>
#include <memory>

template<typename Ctx>
class CanvasItem
{
public:
    void paint() {
        paintForward<Ctx::IsForward>();
    }
    void layout()
    {
        layoutForward<Ctx::IsForward>();
    }

private:
    template<bool forward>
    void layoutForward();

    template<>
    void layoutForward<true>() { std::cout << "Forward\n"; }
    
    template<>
    void layoutForward<false>() { std::cout << "Normal\n"; }

    template<bool forward>
    void paintForward();

    template<>
    void paintForward<true>() { std::cout << "Forward\n"; }

    template<>
    void paintForward<false>() { std::cout << "Normal\n"; }
};

template<bool IsForward>
struct CanvasItemTraits
{
    static constexpr bool IsForward = IsForward;
};

int main()
{
    CanvasItem<CanvasItemTraits<true>> a;
    CanvasItem<CanvasItemTraits<false>> b;

    a.layout();
    b.layout();

    return 0;
}
