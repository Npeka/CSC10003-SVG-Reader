//#define WIN32_LEAN_AND_MEAN   
#include <winsock2.h>
#include <objidl.h>
#include <windows.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#include "src/SVGImage.h"

float offsetX = 0.0f;
float offsetY = 0.0f;
float rotationAngle = 0.0f;
float zoomFactor = 1.0f;
std::string filename = "sample.svg";

VOID OnPaint(HDC& hdc)
{
    Gdiplus::Graphics graphics(hdc);
    graphics.ScaleTransform(zoomFactor, zoomFactor);
    graphics.TranslateTransform(offsetX, offsetY);
    graphics.RotateTransform(rotationAngle);

    graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
    graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
    graphics.SetTextContrast(100);
    graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
    graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
    graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

    // 01 - 02 - 09 bi loi chay chua duoc
    SVGImage svg(filename);
    SVG_Render(svg, graphics);
}

void Translate(HWND& hWnd, float x, float y) {
    offsetX += x;
    offsetY += y;
    InvalidateRect(hWnd, NULL, TRUE);
}

void Rotate(HWND& hWnd, float angle) {
    rotationAngle += angle;
    InvalidateRect(hWnd, NULL, TRUE);
}

void Zoom(HWND& hWnd, float zoom) {
    zoomFactor *= zoom;  // Tăng tỷ lệ zoom (có thể điều chỉnh)
    InvalidateRect(hWnd, NULL, TRUE);  // Gọi OnPaint để vẽ lại
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
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
            Zoom(hWnd, 1.2);
            break;
        case VK_SUBTRACT:   // Phím "-" - Zoom out
            Zoom(hWnd, 1/1.2);
            break;

        case 'W': case VK_UP:
            Translate(hWnd, 0, 10);
            break;

        case 'S': case VK_DOWN:
            Translate(hWnd, 0, -10);
            break;

        case 'A': case VK_LEFT:
            Translate(hWnd, 10, 0);
            break;

        case 'D': case VK_RIGHT:
            Translate(hWnd, -10, 0);
            break;

        case 'Q':
            Rotate(hWnd, -5);
            break;

        case 'E':
            Rotate(hWnd, 5);
            break;
        }

        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
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

//int main(int argc, char* argv[]) {
int main() {
    INT result = WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWNORMAL);
    return result;
}