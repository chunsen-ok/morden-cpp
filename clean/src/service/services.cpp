#include "services.hpp"
#include <iostream>

WrapTask inc_number(int inc)
{
    return WrapTask{[inc](AppData *data, AppStore *store){
        data->num += inc;
        std::cout << "inc: " << data->num << std::endl;
    }};
}

void Login::exec(AppData *data, AppStore *store)
{
    std::cout << "Login ..." << std::endl;
}
