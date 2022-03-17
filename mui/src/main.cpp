#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>

namespace view {
    class View {};
    class ViewModel {};
    // selectors
}

namespace core {
    class Action {};
    
    template<typename T>
    class Store
    {
    public:
        const T &state() const { return m_state; }
        void reducer(const Action &action);
        void subscribe();

    private:
        T m_state;
    };

    class DataPath
    {
    public:
        enum Action {
            None = 0,
            Update,
            Add,
            Delete,
        };

        DataPath() = default;
        DataPath(Action action, const std::vector<int> &path): m_action(action), m_path(path) {} 
        DataPath(Action action, std::initializer_list<int> path): m_action(action), m_path{path} {}

        Action action() const { return m_action; }
        bool empty() const { return m_path.empty(); }
        bool contains(const DataPath &other) const
        {
            if (m_path.size() >= other.m_path.size()) { return false; }

            for (auto i = 0; i < m_path.size(); ++i) {
                if (m_path[i] != other.m_path[i]) {
                    return false;
                }
            }

            return true;
        }
        DataPath join(const DataPath &other) const
        {
            std::vector<int> path = m_path;
            path.insert(path.end(), other.m_path.begin(), other.m_path.end());
            return DataPath{ other.m_action, path };
        }

        friend constexpr bool operator==(const DataPath &lhs, const DataPath &rhs);
        friend std::ostream &operator<<(std::ostream &os, const DataPath &rhs);

    private:
        Action m_action{None};
        std::vector<int> m_path;
    };
    
    constexpr bool operator==(const DataPath &lhs, const DataPath &rhs)
    {
        return lhs.m_path == rhs.m_path;
    }
    
    std::string path_action_string(DataPath::Action action)
    {
        switch (action)
        {
        case DataPath::Update: return "Update";
        case DataPath::Add: return "Add";
        case DataPath::Delete: return "Delete";
        default: return "";
        }
    }

    std::ostream &operator<<(std::ostream &os, const DataPath &rhs)
    {
        os << "DataPath{ " << path_action_string(rhs.action()) << ": ";
        for (auto i = 0; i < rhs.m_path.size(); ++i) {
            os << rhs.m_path[i];
            if (i != rhs.m_path.size() - 1) {
                os << ", ";
            }
        }
        os << " }";
        return os;
    }
}

class State
{
public:
    enum Path {
        None = 0,
        PChats,
        PHistorys,
        PFriends,
        PGroups,
    };
};

class Chats
{
public:
    enum Path {
        None = 0,
        PId,
        PName,
        PAvatar,
        PContent,
        PTime,
    };
};

class Friends
{
public:
    enum Path {
        None = 0,
        PId,
        PName,
        PAvatar,
        PSignature,
    };
};

int main() {
    auto root = core::DataPath{};
    std::cout << root.empty() << std::endl;

    auto groups = core::DataPath{core::DataPath::Update, {State::PGroups}};
    
    auto chats = core::DataPath{core::DataPath::Update, {State::PChats}};
    auto path0 = core::DataPath{core::DataPath::Add, {State::PChats, 1}};
    std::cout << path0 << std::endl;

    auto path1 = core::DataPath{core::DataPath::Update, {State::PChats, 2, Chats::PName}};
    auto path2 = core::DataPath{core::DataPath::Update, {State::PFriends, 0, Friends::PId}};
    auto path3 = core::DataPath{core::DataPath::Delete, {State::PFriends, 0, Friends::PName}};

    std::cout << (root == groups) << std::endl;
    std::cout << path0.contains(path1) << std::endl;
    std::cout << root.contains(path3) << std::endl;
    std::cout << chats.contains(path1) << std::endl;

    std::cout << path3 << std::endl;
    std::cout << path2.join(path1) << std::endl;
    return 0;
}
