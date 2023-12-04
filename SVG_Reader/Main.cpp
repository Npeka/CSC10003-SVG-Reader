#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN   
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

//using namespace std;
//using namespace Gdiplus;

#include "src/SVGImage.h"

float zoomFactor = 1.0f;

VOID OnPaint(HDC& hdc)
{
    Gdiplus::Graphics graphics(hdc);
    graphics.ScaleTransform(zoomFactor, zoomFactor);

    SVGImage svg("sample.svg");
    for (int i =0 ;i < svg.figure.size();i++) {
		svg.figure[i]->draw(graphics);
	}
}

void ZoomIn(HWND& hWnd) {
    zoomFactor *= 1.2f;  // Tăng tỷ lệ zoom (có thể điều chỉnh)
    InvalidateRect(hWnd, NULL, TRUE);  // Gọi OnPaint để vẽ lại
}

void ZoomOut(HWND& hWnd) {
    zoomFactor /= 1.2f;  // Giảm tỷ lệ zoom (có thể điều chỉnh)
    InvalidateRect(hWnd, NULL, TRUE);  // Gọi OnPaint để vẽ lại
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ADD:        // Phím "+" - Zoom in
            ZoomIn(hWnd);
            break;
        case VK_SUBTRACT:   // Phím "-" - Zoom out
            ZoomOut(hWnd);
            break;
        }
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("GettingStarted"),   // window class name
        TEXT("SVG Demo"),  // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        NULL);                    // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}  // WinMain