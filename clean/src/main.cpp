//! 如何建立资源并管理。
#include <iostream>
#include <core/data_store.hpp>
#include <core/action.hpp>

template<typename T>
class observable
{
public:

};

class AppData
{
public:
    int num;
    observable<bool> open;
};
using AppStore = DataStore<AppData>;
using Task = Action<AppData>;
using AsyncTask = AsyncAction<AppData>;

class IncNumber: public Task
{
public:
    IncNumber(int inc): Task{}, m_num{inc} {}

    void exec(AppData *data, AppStore*) const override
    {
        std::cout << "inc" << std::endl;
        data->num += m_num;
    }

private:
    const int m_num;
};

class Login: public AsyncTask
{
public:
    Login(): AsyncTask() {}

    void exec(AppData *data, AppStore *store) override
    {
        std::cout << "login" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    DataStore<AppData> store{AppData{}};

    store.dispatch(IncNumber{1001});

    auto login = new Login;
    store.dispatch(login);
    delete login;
    
    return 0;
}
