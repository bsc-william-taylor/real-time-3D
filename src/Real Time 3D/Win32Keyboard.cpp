
#include "Win32Keyboard.h"
#include "Win32Codes.h"

Win32Keyboard::Win32Keyboard() :
    hwnd(nullptr)
{
    clearInput();
}

Win32Keyboard::~Win32Keyboard()
{
    if (keyboard != nullptr)
    {
        keyboard->Unacquire();
        keyboard->Release();
        keyboard = nullptr;
    }
}

void Win32Keyboard::initialiseInput(HWND* hwnd)
{
    DWORD Settings = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
    keyboard->SetDataFormat(&c_dfDIKeyboard);
    keyboard->SetCooperativeLevel(*hwnd, Settings);
    keyboard->Acquire();
    this->hwnd = hwnd;
}

void Win32Keyboard::updateInput()
{
    keyboard->Acquire();
    keyboard->GetDeviceState(sizeof(keyBuffer), &keyBuffer);
}

void Win32Keyboard::outputInput(Scene * CurrentState)
{
    for (auto i = 0; i < 255; i++)
    {
        if (keyBuffer[i] & 0x80 && !keyRelease[i])
        {
            CurrentState->onKeyPress(i, PRESSED);
            releaseMsg[i] = false;
            keyRelease[i] = true;
        }

        if (keyRelease[i] && keyBuffer[i] & 0x80)
        {
            CurrentState->onKeyPress(i, HOLDING);
            releaseMsg[i] = false;
        }

        if (!(keyBuffer[i] & 0x80) && keyRelease[i])
        {
            CurrentState->onKeyPress(i, RELEASED);
            keyRelease[i] = false;
            releaseMsg[i] = true;
        }
    }
}


void Win32Keyboard::clearInput()
{
    for (auto i = 0; i < 255; i++)
    {
        keyRelease[i] = false;
        releaseMsg[i] = false;
    }
}

void Win32Keyboard::removeMsgs()
{
    for (auto i = 0; i < 255; i++)
    {
        releaseMsg[i] = false;
    }
}