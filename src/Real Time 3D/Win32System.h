
#pragma once

#include "Win32Window.h"
#include "Win32Driver.h"

class Win32System
{
    Win32Window window;
    Win32Driver driver;

    WindowType type;
    BOOL quit;
public:
    Win32System();
    ~Win32System();

    Win32Window* getWindow();

    void setWindowTraits(CHAR *, Region);
    void setWindowType(WindowType);
    void swapWindowBuffers();
    void initialise();
    void onUpdate();

    bool windowRunning();
};