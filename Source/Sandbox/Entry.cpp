#define UNICODE
#include <windows.h>
#include "SandboxApp.hpp"
#include "Freight/Log.hpp"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


HWND CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"Main Window Class";
    wc.hIconSm = NULL;

    RegisterClassEx(&wc);
    
    HWND hwnd;

    hwnd = CreateWindowEx(
        NULL,
        L"Main Window Class",
        L"Main Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    FR8_ASSERT(hwnd, "Could not create HWND");

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return hwnd;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    CreateMainWindow(hInstance, nCmdShow);

    FR8::Freight *app = new FR8::SandboxApp;
    app->start();

    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        else
        {
            app->update();
        }
    }

    app->stop();
    delete app;

    return (int) msg.wParam;
}