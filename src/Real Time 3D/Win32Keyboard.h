
#pragma once

#include "Win32Header.h"
#include "SceneManager.h"

class Win32Keyboard
{
    LPDIRECTINPUTDEVICE8 keyboard;

    bool keyRelease[256];
    bool releaseMsg[256];
    char keyBuffer[256];

    HWND* hwnd;
public:
    Win32Keyboard();
    ~Win32Keyboard();

    void initialiseInput(HWND*);
    void outputInput(Scene*);
    void updateInput();
    void clearInput();
    void removeMsgs();

    operator LPDIRECTINPUTDEVICE8()
    {
        return keyboard;
    }
};