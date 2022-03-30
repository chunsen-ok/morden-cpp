//! 如何建立资源并管理。
//! 资源独立于Data，通过依赖注入
//! Data 中包含关于本数据的操作逻辑，并会通知外部
//! 什么都用Action包裹，比较繁琐，没有必要；可以直接在Data中实现这些逻辑
#include <iostream>
#include <service/services.hpp>
#include <infras/network.hpp>
#include <infras/local_storage.hpp>
#include <presenter/server_event_receiver.hpp>

#include <rxcpp/rx.hpp>

int main(int argc, char *argv[])
{
    LocalStorage storage;
    Network network;
    
    AppData data(&storage, &network);
    DataStore<AppData> store{std::move(data)};

    ServerEventReceiver receiver(&store);
    receiver.run();

    store.dispatch(IncNumber{1001});

    auto login = new Login;
    store.dispatch(login);
    delete login;

    return 0;
}
