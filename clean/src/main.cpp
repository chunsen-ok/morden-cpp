#include <iostream>
#include <string>
#include <memory>
#include <vector>

enum class ElementType
{
    Unknown = 0,
    Event,
    One,
    Two,
};

class AbstractElementData
{
public:
    explicit AbstractElementData(ElementType type)
        : mType{type}
        , mId{0}
    {}

    AbstractElementData(ElementType type, int id)
        : mType{type}
        , mId{id}
    {}

    virtual ~AbstractElementData() = default;

public:
    ElementType type() const { return mType; }
    int id() const { return mId; }

private:
    ElementType mType;
    int mId;
};

class OneData: public AbstractElementData
{
public:
    OneData(int one, int id)
        : AbstractElementData{ElementType::One, id}
        , mOne{one}
    {}

    int one() const { return mOne; }
    void set_one(int one) { mOne = one; }

private:
    int mOne;
};

class TwoData: public AbstractElementData
{
public:
    TwoData(int two, int id)
        : AbstractElementData{ElementType::Two, id}
        , mTwo{two}
    {}

    int two() const { return mTwo; }
    void set_two(int two) { mTwo = two; }

private:
    int mTwo;
};

class EventData: public AbstractElementData
{
public:
    EventData(const std::string &text, ElementType type, int id)
        : AbstractElementData{type, id}
        , mText{text}
    {}

    const std::string &text() const { return mText; }

private:
    std::string mText;
};

class AbstractElement
{
public:
    virtual ~AbstractElement() = default;

    virtual ElementType type() const = 0;
    virtual int id() const = 0;

    virtual void paint() {}
};

class AbstractTipElement: public AbstractElement
{
public:
    void paint() override final
    {
        std::cout << "Tip: " << text() << std::endl;
    }

protected:
    virtual const std::string &text() const = 0;
};

class AbstractChatElement: public AbstractElement
{
public:
    void paint() override final
    {
        std::cout << "Paint chat\n";
        paintContent();
    }

protected:
    virtual void paintContent() = 0;
};

template<typename T>
class TipElement: public AbstractTipElement, public T
{
public:
    template<typename ... Args>
    TipElement(Args ... args)
        : AbstractTipElement()
        , T(std::forward<Args>(args)...)
    {}

    ElementType type() const override { return T::type(); }
    int id() const override { return T::id(); }
};

template<typename T>
class ChatElement: public AbstractChatElement, public T
{
public:
    template<typename ... Args>
    ChatElement(Args ... args)
        : AbstractChatElement()
        , T(std::forward<Args>(args)...)
    {}

    ElementType type() const override { return T::type(); }
    int id() const override { return T::id(); }
};

class OneElement: public ChatElement<OneData>
{
public:
    OneElement(int one, int id)
        : ChatElement<OneData>{one, id}
    {}

protected:
    void paintContent() override
    {
        std::cout << "paint one: " << one() << std::endl;
    }
};

class TwoElement: public ChatElement<TwoData>
{
public:
    TwoElement(int two, int id)
        : ChatElement<TwoData>{two, id}
    {}
    
    ~TwoElement()
    {
        std::cout << "~TwoElement\n";
    }

public:
    void paintContent() override
    {
        std::cout << "paint two: " << two() << std::endl;
    }
};

class EventElement: public TipElement<EventData>
{
public:
    EventElement(const std::string &text, int id)
        : TipElement<EventData>{text, ElementType::Event, id}
    {}

protected:
    const std::string &text() const { return EventData::text(); }
};

class MessageHistory
{
public:
    using Element = std::shared_ptr<AbstractElement>;

    template<typename T, typename ... Args>
    std::shared_ptr<T> makeMessage(Args ... args)
    {
        auto msg = std::make_shared<T>(std::forward<Args>(args)...);
        insert(msg);
        return msg; 
    }

    void insert(const Element &data)
    {
        mElements.push_back(data);
    }

    void paint()
    {
        for (const auto &ele: mElements)
        {
            ele->paint();
        }
    }

private:
    std::vector<Element> mElements;
};

int main()
{
    MessageHistory history;
    history.makeMessage<OneElement>(1124, 1);
    history.makeMessage<TwoElement>(222222, 2);
    history.makeMessage<EventElement>("Hello, world!", 3);

    history.paint();
}
