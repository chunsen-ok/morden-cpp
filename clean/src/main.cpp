//! 如何建立资源并管理。
//! 资源独立于Data，通过依赖注入
//! Data 中包含关于本数据的操作逻辑，并会通知外部
//! 
//! 组件间model的层级依赖，组件间model的通信
//! 模块、组件间要相互独立，可独立替换、修改
//! 子组件间相互独立，涉及多组件的时候，子组件发出通知，由父组件调配各子组件完成功能。
//! 提供一种映射，缓存机制
#include <iostream>
#include <infras/network.hpp>
#include <infras/local_storage.hpp>
#include <service/services.hpp>
#include <service/server_event_receiver.hpp>

int main(int argc, char *argv[])
{
    LocalStorage storage;
    Network network;
    
    AppData data(&storage, &network);
    DataStore<AppData> store{std::move(data)};

    ServerEventReceiver receiver(&store);
    receiver.run();

    store.dispatch(inc_number(1001));
    store.dispatch(inc_number(1254));

    auto login = new Login;
    store.dispatch(login);
    delete login;

    return 0;
}
