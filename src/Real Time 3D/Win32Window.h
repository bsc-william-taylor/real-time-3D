
#pragma once

#include "Win32Header.h"

enum class WindowType
{
    Fullscreen,
    Windowed
};

enum class WindowLocation
{
    Center = -1
};

struct Region
{
    int x, y, w, h;
};

class Win32Window
{
    Region region;
    MSG message;
    HGLRC context;
    TCHAR* title;
    HWND window;
public:
    Win32Window();
    ~Win32Window();

    void setTraits(TCHAR*, int, int, int, int);
    void enableOpenGL();
    void display(WindowType);
    void initialise();
    bool onUpdate();

    HWND& getHandle();
    MSG& getMsg();
private:
    static LRESULT __stdcall WndProc(HWND, UINT, WPARAM, LPARAM);
};

using Window = Win32Window;