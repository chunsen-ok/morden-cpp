#include "application.hpp"
#include <windows.h>

int Application::exec()
{
    MSG msg = { };
    // 从消息队列拉取一条消息    
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
