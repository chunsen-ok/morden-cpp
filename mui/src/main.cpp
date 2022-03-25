#include <iostream>

// action的管理，同步，异步支持。
class Store {};

// 管理数据获取、存储
// 通知数据变更
class Data {};

// 负责业务逻辑，从Data获取需要的数据
// Action支持组合
class Action {};

// 发送Action
// 从Data获取数据显示
// 监听Data变更
class Presenter {};

int main() {
    std::cout << 0xfff << std::endl;
    return 0;
}
