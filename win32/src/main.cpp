// https://docs.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-
//
// 窗口类
// 窗口
// 窗口过程瓶颈，以及如何避免 - https://docs.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure

#include "application.hpp"
#include "window.hpp"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    Application app;
    Window::registerClass(hInstance);

    Window window(hInstance);
    window.show(nCmdShow);

    return app.exec();
}
