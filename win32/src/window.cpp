#include "window.hpp"

static LPCWSTR CLASS_NAME  = L"Sample Window Class";

void Window::registerClass(HINSTANCE hInstance)
{
    // 窗口类：定义多个窗口可能共有的一组行为。
    WNDCLASS wc = { };
    wc.lpfnWndProc   = Window::WindowProc; // 窗口过程
    wc.hInstance     = hInstance; // 应用实例
    wc.lpszClassName = CLASS_NAME; // 窗口类标识字符串
    // 向操作系统注册窗口类
    RegisterClass(&wc);
}

LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // if (WM_CREATE == uMsg) {
    //     CREATESTRUCT *createData = reinterpret_cast<CREATESTRUCT*>(lParam);
    //     auto state = reinterpret_cast<WindowState*>(createData->lpCreateParams);
    //     SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)state);
    //     return DefWindowProc(hwnd, uMsg, wParam, lParam);
    // }

    // LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    // WindowState *state = reinterpret_cast<WindowState*>(ptr);

    switch (uMsg) {
    case WM_DESTROY: // 窗口销毁的消息
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        HBRUSH hbr = CreateSolidBrush(RGB(100, 100, 100));
        FillRect(hdc, &ps.rcPaint, hbr);
        EndPaint(hwnd, &ps);

        DeleteObject((HGDIOBJ)hbr);
    }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window::Window(HINSTANCE hInstance)
{
    // 创建窗口实例
    // 每个特定窗口的唯一数据被称为**实例数据**
    mHwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL       // Additional application data
    );
}

void Window::show(int cmdShow)
{
    ShowWindow(mHwnd, cmdShow);
}
