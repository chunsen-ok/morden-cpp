#ifndef CLEAN_APP_DATA_HPP
#define CLEAN_APP_DATA_HPP

#include <core/data_store.hpp>
#include <core/action.hpp>

class LocalStorage;
class Network;

class Chats
{
public:

};

class Chatting
{
public:
    
};

class Chattings
{
public:

};

class AppData
{
public:
    AppData(LocalStorage *storage, Network *network)
        : m_storage(storage)
        , m_network(network) {}

    int num{0};
    Chats chats;
    Chattings chattings;

private:
    LocalStorage *m_storage;
    Network *m_network;
};

using AppStore = DataStore<AppData>;

#endif
