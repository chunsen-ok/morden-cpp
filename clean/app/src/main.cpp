#include <vector>
#include <string>
#include <iostream>

class HistoryView {};
class HistoryModel {};
class HistoryItemData
{
public:
    virtual ~HistoryItemData() = default;
};

class TextHistory: public HistoryItemData
{
public:
    TextHistory(const std::string &text): HistoryItemData(), m_text(text) {}
    std::string m_text;
};

class PictureHistory: public HistoryItemData
{
public:
    PictureHistory(int size): HistoryItemData(), m_size(size) {}
    int m_size;
};

class AbstractHistoryItem
{
public:
    virtual ~AbstractHistoryItem() = default;
    virtual void paint(HistoryModel *model, HistoryView *view) = 0;
    virtual void layout(HistoryModel *model, HistoryView *view) = 0;
    virtual void event(HistoryModel *model, HistoryView *view) = 0;
};

namespace HistoryCanvas
{

class Tip: public AbstractHistoryItem
{
public:
    void paint(HistoryModel *model, HistoryView *view) override
    {
        std::cout << "tip: " << tip() << std::endl;
    }

protected:
    virtual std::string tip() const = 0;
};

class Chat: public AbstractHistoryItem
{
public:
    void paint(HistoryModel *model, HistoryView *view) override
    {

    }

protected:
    std::string name() const;
    std::string avatar() const;

};

};

int main()
{
    return 0;
}
