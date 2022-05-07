//! 如何建立资源并管理。
//! 资源独立于Data，通过依赖注入
//! Data 中包含关于本数据的操作逻辑，并会通知外部
//! 
//! 组件间model的层级依赖，组件间model的通信
//! 模块、组件间要相互独立，可独立替换、修改
//! 子组件间相互独立，涉及多组件的时候，子组件发出通知，由父组件调配各子组件完成功能。
//! 提供一种映射，缓存机制

#include <iostream>
#include <store.hpp>

class AppData
{
public:
    int number;
};

auto set_number(int num) {
    return [=](AppData *data, Store<AppData> *store){
        data->number = num;
    };
}

// pure action
auto inc_number(int num) {
    return [=](AppData *data, Store<AppData> *store){
        data->number += num;
    };
}

auto fetch_number() {
    return [=](AppData *data, Store<AppData> *store){
        Api->fetch("/v1/num")
        .then([store](int num){
            store->dispatch(set_number(num));
        });
    };
}

// side-effect action
auto fetch_add_save(int num) {
    return [=](AppData *data, Store<AppData> *store){
        // fetch(this)
        // | [=](int value){ return value + num; }
        // | save(this);
    };
}

// from db
auto fetch_db() {
    return [](AppData *data, Store<AppData> *store){
        localstorage->query()
        .then([store](int num){
            store->dispatch(set_number(num));
        });
    };
}

int main() {
    Store<AppData> store;

    store.dispatch(inc_number(10086));
    std::cout << store->number << std::endl;

    return 0;
}
