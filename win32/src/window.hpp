#ifndef WINDOW_HPP
#define WINDOW_CPP

#include <windows.h>

class Window
{
public:
    static void CALLBACK registerClass(HINSTANCE hInstance);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

    Window(HINSTANCE hInstance);

    void show(int cmdShow);

private:
    HWND mHwnd;
};

#endif
