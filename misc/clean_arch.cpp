#include <iostream>
#include <string>
#include <memory>

// 单一state
// 外部只能通过发送action来请求改变数据

class Action
{
public:

};

class AppState
{
public:
    void update(const Action &action);
};

// 