// https://docs.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-
//
// 窗口类
// 窗口
// 窗口过程瓶颈，以及如何避免 - https://docs.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure

#include <Windows.h>
#include <ShObjIdl.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CALLBACK OpenDialog();

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
        NULL       // Additional application data
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

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
