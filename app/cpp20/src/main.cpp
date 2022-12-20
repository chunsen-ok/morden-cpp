#include <iostream>
#include <vector>
#include <variant>
#include <ranges>
#include <format>

class CanvasItem: public std::enable_shared_from_this<CanvasItem>
{
public:
    static std::shared_ptr<CanvasItem> create(double x, double y, double w, double h)
    {
        return std::shared_ptr<CanvasItem>(new CanvasItem(x,y,w,h));
    }

    double x() const { return mX; }
    double y() const { return mY; }
    double width() const { return mWidth; }
    double height() const { return mHeight; }

protected:
    CanvasItem(double x, double y, double w, double h)
        : mX(x), mY(y), mWidth(w), mHeight(h)
    {}

private:
    double mX;
    double mY;
    double mWidth;
    double mHeight;
};

class BucketItem
{
public:

private:
    std::weak_ptr<CanvasItem> mBucketItem;
};

class Bucket: public std::enable_shared_from_this<Bucket>
{
public:
    static std::shared_ptr<Bucket> create()
    {
        return std::shared_ptr<Bucket>(new Bucket);
    }

    double baseMin() const;
    double baseMax() const;
    double min() const;
    double max() const;
    void insert(const BucketItem& item);
    std::vector<BucketItem> intersected(double x) const;
    void insertIntersects(const std::vector<BucketItem>& items);

protected:
    Bucket() {}
};

class BucketLayout
{
public:
    void clear() { mBuckets.clear(); }

    std::shared_ptr<Bucket> bucketAt(double x) const
    {
        // ...
    }


    void layout(const std::shared_ptr<CanvasItem>& data)
    {
        const auto x = data->x();

    }

private:
    std::vector<std::shared_ptr<Bucket>> mBuckets;
};

int main() {
    std::vector<std::shared_ptr<CanvasItem>> datas;
    datas.push_back(CanvasItem::create(0,0,10,10));
    datas.push_back(CanvasItem::create(20,0,10,10));
    datas.push_back(CanvasItem::create(30,0,10,10));

    BucketLayout layout;
    layout.clear();
    for (const auto& data: datas) {
        layout.layout(data);
    }

    return 0;
}
