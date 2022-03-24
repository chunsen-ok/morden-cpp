// 图灵机
// lambda演算
// SICP
// partial function application
// currying
// higher-order functions：使用其他函数作为参数
//   map, filter, foldr, for_each, transform, remove_if
// pure function, immutability
// tail-recursion
// list
// lazy evaluation

// 函数式编程
// 基于lambda演算
// 类型推导、多态类型
// 惰性计算
// 高阶函数
// type classes, monads
// currying：将多参数的函数，转换为单参数的函数,
// 列表
// sicp
//
// 惰性计算
// 列表生成表达式
// 列表运算
// 模式匹配
// constexpr 
// decltype 推断类型
// declval 

// 条件 - 模板参数特例化
// 循环 - 递归

#include <string>
#include <vector>
#include <iostream>
#include <functional>

//! 优化 DataPath，支持payload
//! 如何简化 selector
//! 如果将业务逻辑（修改data数据的逻辑）放在action中，存在问题，可能会存在多线程访问data的情况。

namespace core {

class DataIndex
{
public:
    enum Type
    {
        None = 0,

        Number,
        String,

        NumberFilter,
        StringFilter,

        NumberCollection,
        StringCollection,

        UserType,
    };

    DataIndex(Type tp): m_type{tp} {}
    virtual ~DataIndex() = default;

    Type type() const { return m_type; }

private:
    Type m_type;
};

class NumberIndex: public DataIndex
{
public:
    NumberIndex(int index)
        : DataIndex{Number}, m_index{index} {}

    int value() const { return m_index; }

private:
    int m_index;
};

class StringIndex: public DataIndex
{
public:
    StringIndex(const std::string &index)
        : DataIndex{String}, m_index(index) {}

    const std::string &value() const {
        return m_index;
    }

private:
    std::string m_index;
};

class NumberFilterIndex: public DataIndex
{
public:
    NumberFilterIndex(std::function<bool(int)> &&fn)
        : DataIndex{NumberFilter}, m_filter(std::move(fn)) {}

    bool exec(int num) const { return m_filter(num); }

private:
    std::function<bool(int)> m_filter;
};

class NumberCollectionIndex: public DataIndex
{
public:
    NumberCollectionIndex(std::initializer_list<int> nums)
        : DataIndex{NumberCollection}, m_nums{nums} {}

    bool exec(int num) const {
        auto it = std::find(m_nums.cbegin(), m_nums.cend(), num);
        return it != m_nums.cend();
    }

private:
    std::vector<int> m_nums;
};

class DataPath
{
public:
    DataPath() = default;
    DataPath(DataIndex *base) { join(base); }
    DataPath(const std::string &base) { join(base); }
    DataPath(int base) {join(base); }
    ~DataPath() {
        for (auto index: m_nodes) {
            delete index;
        }
    }

    DataPath &join(const std::string &index)
    {
        m_nodes.push_back(new StringIndex{index});
        return *this;
    }

    DataPath &join(int index)
    {
        m_nodes.push_back(new NumberIndex{index});
        return *this;
    }

    DataPath &join(DataIndex *index)
    {
        if (index) {
            m_nodes.push_back(index);
        }
        return *this;
    }

    const DataIndex *next()
    {
        DataIndex *index{nullptr};
        if (m_current < m_nodes.size()) {
            index = m_nodes.at(m_current);
            ++m_current;
        }
        return index;
    }

    bool empty() const { return m_nodes.empty(); }
    
private:
    std::size_t m_current{0};
    std::vector<DataIndex*> m_nodes;
};

template<typename T>
class DataStore;

template<typename T>
class Action
{
public:
    virtual ~Action() = default;
    virtual DataPath exec(T *data, DataStore<T> *store) const { return DataPath{}; }
    virtual DataPath exec(T *data, DataStore<T> *store) { return DataPath{}; }
};

template<typename T>
class DataStore
{
public:
    DataStore(const T &data): m_data{data} {}
    DataStore(T &&data): m_data(std::move(data)) {}

    const T &data() const { return m_data; }

    void dispatch(const Action<T> &action)
    {
        std::cout << __LINE__ << std::endl;
        const auto path = action.exec(&m_data, this);
        if (!path.empty()) {
            std::cout << __LINE__ << std::endl;
            call(path);
            std::cout << __LINE__ << std::endl;
        }
    }

    void subscribe(std::function<void(const DataPath&)> &&subscriber)
    {
        m_subscribers.push_back(std::move(subscriber));
    }

private:
    void call(const DataPath &data)
    {
        for (auto &fn: m_subscribers) {
            fn(data);
        }
    }

private:
    T m_data;
    std::vector<std::function<void(const DataPath&)>> m_subscribers;
};

}

namespace infras {

class FileFetcher
{
public:
    FileFetcher(const std::string &url): m_url{url} {}

    void finished(std::function<void(const std::string&)> &&cb) {
        cb(m_url);
    }

private:
    std::string m_url;
};

}

namespace data {

class Message
{
public:
    enum Index
    {
        SenderID,
        Name,
        Avatar,
        Signature,
        Content,
    };

    std::string content;
};

class MessageList
{
public:
    std::vector<Message> datas;
};

class AppData
{
public:
    enum Index
    {
        Messages,
    };

    MessageList messages;
};

using DataStore = core::DataStore<AppData>;
using Action = core::Action<AppData>;

class UpdateMessageInfo: public Action
{
public:
    UpdateMessageInfo(): Action{} {}

    core::DataPath exec(AppData *data, DataStore *store) const override
    {
        return core::DataPath{"msgs"};
    }
};

class DownloadFileAsync: public Action
{
public:
    DownloadFileAsync(const std::string &oss): Action(), m_url{oss} {}

    core::DataPath exec(AppData *data, DataStore *store) const override
    {
        if (data->messages.datas.size() > 0) {
            auto &msg = data->messages.datas.at(0);
            msg.content = "downloading";
        }

        auto fetcher = new infras::FileFetcher(m_url);
        fetcher->finished([store](const std::string &path){
            std::cout << __LINE__ << std::endl;
            store->dispatch(UpdateMessageInfo{});
            std::cout << __LINE__ << std::endl;
        });
        delete fetcher;

        core::DataPath path("msgs");
        path.join(0).join(Message::Content);
        return path;
    }

private:
    const std::string &m_url;
};

}

namespace view {

}

using namespace core;
using namespace data;

int main() {
    data::AppData data;
    data::DataStore store{std::move(data)};

    store.subscribe([](DataPath path) {
        // selectors
        for (auto index = path.next(); index != nullptr; index = path.next()) {
            if (index->type() == DataIndex::Number) {
                auto num = static_cast<const NumberIndex*>(index);
                if (num) {
                    std::cout << "number: " << num->value() << std::endl;
                }
            } else if (index->type() == DataIndex::String) {
                auto str = static_cast<const StringIndex*>(index);
                if (str) {
                    std::cout << "string: " << str->value() << std::endl;
                }
            } if (index->type() == DataIndex::NumberFilter) {
                auto num = static_cast<const NumberFilterIndex*>(index);
                if (num) {
                    for (auto v: {1,2,3,4,5,6,7,8}) {
                        if (num->exec(v)) {
                            std::cout << "number filter: " << v << std::endl;
                        }
                    }
                }
            } if (index->type() == DataIndex::StringFilter) {
                auto num = static_cast<const NumberCollectionIndex*>(index);
                if (num) {
                    for (auto v: {1,2,3,4,5,6,7,8}) {
                        std::cout << "number filter: " << num->exec(v) << std::endl;
                    }
                }
            }
        }
    });

    store.dispatch(DownloadFileAsync{"https://oss.com/res"});

    return 0;
}
