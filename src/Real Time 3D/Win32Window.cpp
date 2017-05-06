
#include "Win32Window.h"

Win32Window::Win32Window()
{
    HWND handle = GetDesktopWindow();
    RECT desktop;

    GetWindowRect(handle, &desktop);

    region.h = desktop.bottom / 2;
    region.w = desktop.right / 2;
    region.x = NULL;
    region.y = NULL;

    title = "Default Title";
}

Win32Window::~Win32Window()
{
    wglDeleteContext(context);
    wglMakeCurrent(NULL, NULL);
    DestroyWindow(window);
}

void Win32Window::initialise()
{
    WNDCLASSEX WindowClass;
    WindowClass.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
    WindowClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_WINLOGO));
    WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WindowClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
    WindowClass.cbSize = sizeof(WNDCLASSEX);
    WindowClass.lpszClassName = "W";
    WindowClass.hInstance = GetModuleHandle(NULL);
    WindowClass.lpfnWndProc = WndProc;
    WindowClass.hIconSm = NULL;
    WindowClass.lpszMenuName = 0;
    WindowClass.cbClsExtra = 0;
    WindowClass.cbWndExtra = 0;
    RegisterClassEx(&WindowClass);
}

bool Win32Window::onUpdate()
{
    PeekMessage(&GetMsg(), NULL, NULL, NULL, PM_REMOVE);

    if (GetMsg().message == WM_QUIT)
    {
        return FALSE;
    }

    TranslateMessage(&GetMsg());
    DispatchMessage(&GetMsg());
    return TRUE;
}

LRESULT CALLBACK Win32Window::WndProc(HWND Hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
        case WM_DESTROY: 
            PostQuitMessage(0); 
            return NULL;
        case WM_SIZE: 
            glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));  
            break;
        default:
            break;
    }

    return DefWindowProc(Hwnd, Message, wParam, lParam);
}

void Win32Window::display(WindowType type)
{
    auto instance = GetModuleHandle(NULL);
    auto settings = WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX;

    if (type == WindowType::Fullscreen)
    {
        DEVMODE Screen;
        ZeroMemory(&Screen, sizeof(DEVMODE));
        Screen.dmSize = sizeof(DEVMODE);
        Screen.dmPelsHeight = region.h;
        Screen.dmPelsWidth = region.w;
        Screen.dmBitsPerPel = 32;
        Screen.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

        if (ChangeDisplaySettings(&Screen, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
        {
            RECT rect;
            rect.bottom = region.h;
            rect.right = region.w;
            rect.left = NULL;
            rect.top = NULL;

            AdjustWindowRectEx(&rect, WS_POPUP, false, WS_EX_APPWINDOW);
        }

        window = CreateWindowEx(0, "W", title, WS_POPUP, region.x, region.y, region.w, region.h, 0, 0, instance, 0);
    }
    else
    {
        window = CreateWindowEx(0, "W", title, settings, region.x, region.y, region.w, region.h, 0, 0, instance, 0);
    }

    UpdateWindow(window);
    ShowWindow(window, SW_SHOW);
}

void Win32Window::enableOpenGL()
{
    PIXELFORMATDESCRIPTOR pfd;
    HDC hDC = GetDC(window);
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;

    int iFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, iFormat, &pfd);
    context = wglCreateContext(hDC);
    wglMakeCurrent(hDC, context);
}

HWND& Win32Window::GetHandle()
{
    return window;
}

MSG& Win32Window::GetMsg()
{
    return message;
}

void Win32Window::setTraits(TCHAR* title, int x, int y, int width, int height)
{
    this->title = title;
    region.h = height;
    region.w = width;
    region.x = x;
    region.y = y;

    if (region.x == (int)WindowLocation::Center)
    {
        region.x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    }

    if (region.y == (int)WindowLocation::Center)
    {
        region.y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
    }
}

