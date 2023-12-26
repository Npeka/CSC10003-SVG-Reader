#include <winsock2.h>
#include <objidl.h>
#include <windows.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#include "src/SVG_Image.h"

float offsetX = 0.0f;
float offsetY = 0.0f;
float rotationAngle = 0.0f;
float zoomFactor = 1.0f;

// Apple_logo_black.svg
// Firefox_logo,_2019.svg
// chrome-logo.svg
// Instagram_logo_2016.svg
// TikTok_logo.svg

// Init GDI+ startup
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

// Init global SVG_Image and filename
std::string filename = "test case/svg-06.svg";
std::unique_ptr<SVG_Image> svg = std::make_unique<SVG_Image>();

VOID OnPaint(HDC& hdc)
{
    // Load SVG_Image
    svg->parse(filename);

    // Get ViewBox and ViewPort
    ViewBox view = svg->getViewBox();
    float width = svg->getWidth();
    float height = svg->getHeight();
    float scaleX = 1, scaleY = 1, scale = 1;
    if (width && height && view.width && view.height) {
        scaleX = width / view.width;
        scaleY = height / view.height;
        scale = (scaleX < scaleY) ? scaleX : scaleY;
    }
    static bool loop = true;
    if (loop && view.width != 0 && view.width) {
        offsetX += abs(width - view.width * scale) / 2;
        offsetY += abs(height - view.height * scale) / 2;
        loop = false;
    }

    // Init GDI+ Graphics
    Gdiplus::Graphics graphics(hdc);

    // Set GDI+ transform
    graphics.RotateTransform(rotationAngle);
    graphics.SetClip(Gdiplus::RectF(offsetX, offsetY, width * zoomFactor, height * zoomFactor));
    graphics.TranslateTransform(offsetX, offsetY);
    graphics.ScaleTransform(zoomFactor * scale, zoomFactor * scale);

    // Set GDI+ rendering graphics
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
    graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
    graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
    graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

    // Render SVG_Image
    SVG_Render(*svg, graphics);
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
    zoomFactor *= zoom;
    InvalidateRect(hWnd, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    /*int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    wstring wide_filename;
    if (argc > 1)
    {
        wide_filename = argv[1];
        filename = string(wide_filename.begin(), wide_filename.end());
    }
    LocalFree(argv);*/

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
    //Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    //ULONG_PTR           gdiplusToken;

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
        TEXT("SVG_Reader"),  // window caption
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

int main(int argc, char* argv[]) {
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    if (argc > 1) filename = "test case/" + (string)argv[1];
    INT result = WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWNORMAL);
    return result;
}