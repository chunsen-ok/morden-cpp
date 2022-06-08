// https://docs.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-
//
// 窗口类
// 窗口
// 窗口过程瓶颈，以及如何避免 - https://docs.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // 窗口类：定义多个窗口可能共有的一组行为。
    LPCWSTR CLASS_NAME  = L"Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc   = WindowProc; // 窗口过程
    wc.hInstance     = hInstance; // 应用实例
    wc.lpszClassName = CLASS_NAME; // 窗口类标识字符串
    // 向操作系统注册窗口类
    RegisterClass(&wc);

    // 创建窗口实例
    // 每个特定窗口的唯一数据被称为**实例数据**
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    // 从消息队列拉取一条消息    
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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
