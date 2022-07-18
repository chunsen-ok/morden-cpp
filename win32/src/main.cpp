// https://docs.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-
//
// 窗口类
// 窗口
// 窗口过程瓶颈，以及如何避免 - https://docs.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure
#include <Windows.h>
#include <windowsx.h>
#include <ShObjIdl.h>
#include <dwmapi.h>
#include <iostream>
#include "window_state.hpp"

constexpr int padding_left = 8;
constexpr int padding_top = 30;
constexpr int padding_right = 8;
constexpr int padding_bottom = 20;

void CALLBACK OpenDialog()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        IFileOpenDialog *pFileDlg;
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileDlg));
        if (SUCCEEDED(hr)) {
            hr = pFileDlg->Show(NULL);
            if (SUCCEEDED(hr)) {
                IShellItem *pShell;
                hr = pFileDlg->GetResult(&pShell);
                if (SUCCEEDED(hr)) {
                    PWSTR pszFilePath;
                    hr = pShell->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    if (SUCCEEDED(hr)) {
                        MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        CoTaskMemFree(pszFilePath);
                    }
                    pShell->Release();
                }
            }
        }
        pFileDlg->Release();
    }
    CoUninitialize();
}

void CALLBACK SetWindowState(HWND hwnd, LPARAM lParam)
{
    CREATESTRUCT *createData = reinterpret_cast<CREATESTRUCT*>(lParam);
    auto state = reinterpret_cast<WindowState*>(createData->lpCreateParams);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)state);
}

WindowState* CALLBACK GetState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    return reinterpret_cast<WindowState*>(ptr);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_CREATE:
    {
        SetWindowState(hwnd, lParam);

        RECT rcClient;
        GetWindowRect(hwnd, &rcClient);
        SetWindowPos(
            hwnd, 
            NULL, 
            rcClient.left, 
            rcClient.top,
            rcClient.right - rcClient.left,
            rcClient.bottom - rcClient.top,
            SWP_FRAMECHANGED
        );
    }
        break;
    case WM_DESTROY: // 窗口销毁的消息
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // DWORD color = 0;
        // BOOL opaque = FALSE;
        // HRESULT hr = DwmGetColorizationColor(&color, &opaque);
        HBRUSH hbr = CreateSolidBrush(RGB(30, 200, 210));
        FillRect(hdc, &ps.rcPaint, hbr);
        EndPaint(hwnd, &ps);
        DeleteObject((HGDIOBJ)hbr);
    }
        return 0;
    case WM_ACTIVATE:
    {
        // no window border
        MARGINS margins;
        margins.cxLeftWidth = 1;
        margins.cxRightWidth = 1;
        margins.cyBottomHeight = 1;
        margins.cyTopHeight = 1;
        HRESULT hr = DwmExtendFrameIntoClientArea(hwnd, &margins);
    }
        return 0;
    case WM_NCCALCSIZE:
    {
        if (wParam == TRUE) {
            // NCCALCSIZE_PARAMS *pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);
            // pncsp->rgrc[0].left   = pncsp->rgrc[0].left   + 0;
            // pncsp->rgrc[0].top    = pncsp->rgrc[0].top    + 0;
            // pncsp->rgrc[0].right  = pncsp->rgrc[0].right  - 0;
            // pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom - 0;
            return 0;
        }
    }
        break;
    case WM_NCHITTEST:
    {
        // Get the point coordinates for the hit test.
        POINT ptMouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};

        // Get the window rectangle.
        RECT rcWindow;
        GetWindowRect(hwnd, &rcWindow);

        // Get the frame rectangle, adjusted for the style without a caption.
        RECT rcFrame = { 0 };
        AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

        // Determine if the hit test is for resizing. Default middle (1,1).
        USHORT uRow = 1;
        USHORT uCol = 1;
        bool fOnResizeBorder = false;

        // Determine if the point is at the top or bottom of the window.
        if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + padding_top)
        {
            fOnResizeBorder = (ptMouse.y < (rcWindow.top - rcFrame.top));
            uRow = 0;
        }
        else if (ptMouse.y < rcWindow.bottom && ptMouse.y >= rcWindow.bottom - padding_bottom)
        {
            uRow = 2;
        }

        // Determine if the point is at the left or right of the window.
        if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + padding_left)
        {
            uCol = 0; // left side
        }
        else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - padding_right)
        {
            uCol = 2; // right side
        }

        // Hit test (HTTOPLEFT, ... HTBOTTOMRIGHT)
        LRESULT hitTests[3][3] = 
        {
            { HTTOPLEFT,    fOnResizeBorder ? HTTOP : HTCAPTION, HTTOPRIGHT },
            { HTLEFT,       HTNOWHERE,     HTRIGHT },
            { HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT },
        };

        LRESULT res = hitTests[uRow][uCol];
        if (res != HTNOWHERE) { return res; }
    }
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // 窗口类：定义多个窗口可能共有的一组行为。
    LPCWSTR CLASS_NAME  = L"Sample Window Class";
    WNDCLASSEX wc = { };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WindowProc; // 窗口过程
    wc.hInstance     = hInstance; // 应用实例
    wc.lpszClassName = CLASS_NAME; // 窗口类标识字符串
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    // 向操作系统注册窗口类
    RegisterClassEx(&wc);
    
    WindowState state;

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
        &state       // Additional application data
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
