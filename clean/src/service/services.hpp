#ifndef CLEAN_SERVICE_HPP
#define CLEAN_SERVICE_HPP

#include <data/app_data.hpp>

using Task = Action<AppData>;
using AsyncTask = AsyncAction<AppData>;
using WrapTask = WrapAction<AppData>;

WrapTask inc_number(int inc);

class Login: public AsyncTask
{
public:
    Login(): AsyncTask() {}

    void exec(AppData *data, AppStore *store) override;
};

#endif
