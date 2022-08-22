#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

struct SizeF
{
    double width{0};
    double height{0};
};

struct RectF
{
    double x{0};
    double y{0};
    double width{0};
    double height{0};
};

template<typename Ctx>
class CanvasItem
{
public:
    SizeF layout(Ctx ctx, const RectF& vr)
    {
        const auto s = layout(ctx, SizeF(vr.width, vr.height));
        mRect = RectF(vr.x, vr.y, s.width, s.height);
        return s;
    }

    void paint(Ctx ctx)
    {
        paint(ctx, mRect);
    }

protected:
    virtual SizeF layout(Ctx ctx, const SizeF& rect) = 0;
    virtual void paint(Ctx ctx, const RectF& rect) = 0;

private:
    RectF mRect;
};

struct HistoryItemCtx
{

};

class HistoryItem: public CanvasItem<const HistoryItemCtx&>
{
public:
    SizeF layout(const HistoryItemCtx& ctx, const SizeF& rect) override
    {
        return SizeF{100.0, 100.0};
    }

    void paint(const HistoryItemCtx& ctx, const RectF& rect) override
    {
        // paint ...
    }
};

template<typename View>
class Canvas
{
public:
    SizeF layoutItems(std::size_t index, std::size_t count)
    {
        
    }
};

int main()
{
    return 0;
}
