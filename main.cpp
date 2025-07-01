#include "Base.h"
#include "Shape.h"
#include "Renderer.h"

// Biến GDI+
ULONG_PTR gdiplusToken;
Renderer renderer;

// Hàm xử lý vẽ
VOID OnPaint(HDC hdc) {
    Graphics graphics(hdc);
    RECT rect;
    GetClientRect(WindowFromDC(hdc), &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    renderer.render(graphics, width, height);
}

// Hàm Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            MessageBox(hWnd, TEXT("SVG Viewer\n(c) 2024"), TEXT("About"), MB_OK | MB_ICONINFORMATION);
            break;
        case IDM_EXIT:
            PostQuitMessage(0);
            break;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Entry point WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    // Khởi động GDI+
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Đăng ký lớp cửa sổ
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SVGDEMO));        // icon từ resource.h
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAINFRAME);                    // menu từ resource.h

    RegisterClass(&wc);

    // Tạo cửa sổ
    HWND hWnd = CreateWindowEx(
        0, L"MyWindowClass", L"SVG Viewer",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600,
        NULL, NULL, hInstance, NULL);

    if (!hWnd) return 0;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Load file SVG vào renderer
    renderer.loadSVG("mediator7.svg");    

    // Vòng lặp message
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Giải phóng GDI+
    GdiplusShutdown(gdiplusToken);

    return (int)msg.wParam;
}