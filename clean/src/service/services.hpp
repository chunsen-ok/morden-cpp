#ifndef CLEAN_SERVICE_HPP
#define CLEAN_SERVICE_HPP

#include <data/app_data.hpp>

using Task = Action<AppData>;
using AsyncTask = AsyncAction<AppData>;

class IncNumber: public Task
{
public:
    IncNumber(int inc): Task{}, m_num{inc} {}

    void exec(AppData *data, AppStore*) const override
    {
        std::cout << "inc" << std::endl;
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

#endif
