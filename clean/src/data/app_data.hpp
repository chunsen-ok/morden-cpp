#ifndef CLEAN_APP_DATA_HPP
#define CLEAN_APP_DATA_HPP

#include <core/data_store.hpp>
#include <core/action.hpp>
#include <rxcpp/rx.hpp>

class LocalStorage;
class Network;

class AppData
{
public:
    AppData(LocalStorage *storage, Network *network)
        : m_storage(storage)
        , m_network(network) {}

    rxcpp::observable<int> num;

private:
    LocalStorage *m_storage;
    Network *m_network;
};

using AppStore = DataStore<AppData>;

#endif
