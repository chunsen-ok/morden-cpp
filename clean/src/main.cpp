//! https://my.oschina.net/u/5447363/blog/5460840
//!
//! clean/
//! |- core
//! |  |- service
//! |- ui
//! |  |- cli
//! |  |- gui
//! |  |- ...
//! |- infras
//! |   |- db
//! |   |- disk
//! |   |- web service
//! |- tests
//!
//! 不同 data 中存在相同 role 时，如何处理？（实现时应当避免这种情况出现，即使真的需要相同的role，也应该近一步区分它们（比如通过数据中携带ID），使之唯一。）
//! 

#include <iostream>
#include <core/data_store.hpp>
#include <core/action.hpp>

class AppData
{
public:
    int num;
};
using AppStore = DataStore<AppData>;
using AppAction = Action<AppData>;

class IncNumber: public AppAction
{
public:
    IncNumber(int inc): AppAction{}, m_num{inc} {}

    void exec(AppData *data, AppStore*)
    {
        data->num += m_num;
    }

private:
    const int m_num;
};

int main(int argc, char *argv[])
{
    DataStore<AppData> store{AppData{}};

    store.dispatch(IncNumber{1001});

    return 0;
}
