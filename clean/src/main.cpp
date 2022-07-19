#include <string>
#include <vector>
#include <iostream>
#include <memory>

class HistoryItem
{
public:
    enum Type
    {
        Binary,
        Text,
        Picture,
    };

public:
    virtual ~HistoryItem() = default;

    virtual Type type() const { return Binary; }
    int sessionId() const;

private:
    int mSessionId;
};

class HistoryViewItem
{
public:
    virtual ~HistoryViewItem() = default;

    virtual void layout() {}
    virtual void paint() {}
};

class HistoryComposeItem
{
public:
    virtual ~HistoryComposeItem() = default;

    virtual HistoryItem *data() = 0;
    virtual const HistoryItem *data() const = 0;

    virtual HistoryViewItem *view() = 0;
    virtual const HistoryViewItem *view() const = 0;
};

class HistoryTextItem: public HistoryItem
{
public:
    virtual Type type() const override { return Text; }

private:
    std::string mText;
};

class HistoryTextViewItem: public HistoryViewItem
{
public:
    void layout() override {}
    void paint() override {}
};

template<typename Data, typename View>
class ComposeItem: public HistoryComposeItem
{
public:
    HistoryItem *data() override { return std::addressof(mData); }
    const HistoryItem *data() const override { return std::addressof(mData); }

    HistoryViewItem *view() override { return std::addressof(mView); }
    const HistoryViewItem *view() const override { return std::addressof(mView); }

private:
    Data mData;
    View mView;
};

class Data
{};

class View
{};

class Config
{};

int main()
{
    return 0;
}
