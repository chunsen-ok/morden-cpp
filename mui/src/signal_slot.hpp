#ifndef MUI_SIGNAL_SLOT_HPP
#define MUI_SIGNAL_SLOT_HPP

#include <vector>
#include "mui_global.hpp"

MUI_BEGIN_NAMESPACE

template<typename T>
class Connection;

template<typename T>
class Signal
{
    friend class Connection<T>;
public:
    ~Signal() {
        std::cout << "~Signal: " << this << std::endl;
        for (auto conn: mConnections) {
            conn->disconnect();
            delete conn;
        }
    }
    void call(const T &v) {
        for (const auto conn: mConnections) {
            conn->call(v);
        }
    }

private:
    std::vector<Connection<T>*> mConnections;
};

template<typename T>
class Slot
{
    friend class Connection<T>;
public:
    ~Slot() {
        std::cout << "~Slot: " << this << std::endl;
        for (auto conn: mConnections) {
            conn->disconnect();
            delete conn;
        }
    }
    void call(const T &v) {
        std::cout << "in slot: " << v << std::endl;
    }

private:
    std::vector<Connection<T>*> mConnections;
};

template<typename T>
class Connection {
public:
    Signal<T> *mSignal {nullptr};
    Slot<T> *mSlot {nullptr};

    ~Connection() {
        std::cout << "~Connection: " << this << std::endl;
    }

    void call(const T &v) {
        mSlot->call(v);
    }

    void disconnect() {
        std::remove_if(mSignal->mConnections.begin(), mSignal->mConnections.end(), [this](auto conn){
            return conn == this;
        });
        
        std::remove_if(mSlot->mConnections.begin(), mSlot->mConnections.end(), [this](auto conn){
            return conn == this;
        });

        mSignal = nullptr;
        mSlot = nullptr;
    }

    static Connection *create(Signal<T> *signal, Slot<T> *slot) {
        auto conn = new Connection{signal, slot};
        signal->mConnections.push_back(conn);
        slot->mConnections.push_back(conn);
        return conn;
    }
};

MUI_END_NAMESPACE

#endif
