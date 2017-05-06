
#include "Win32Driver.h"
#include "SceneManager.h"

Win32Driver::Win32Driver()
{
}

Win32Driver::~Win32Driver()
{
}

void Win32Driver::initialise(HWND * handle)
{
    HINSTANCE instance = GetModuleHandle(NULL);
    DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&driver, NULL);
    this->handle = handle;

    driver->CreateDevice(GUID_SysKeyboard, (Win32Device *)&keyboard, NULL);
    driver->CreateDevice(GUID_SysMouse, (Win32Device *)&mouse, NULL);

    keyboard.initialiseInput(handle);
    mouse.initialiseInput(handle);
}

void Win32Driver::onUpdate()
{
    auto scene = SceneManager::get()->getCurrent();

    keyboard.updateInput();
    keyboard.outputInput(scene);
    keyboard.removeMsgs();

    mouse.updateInput();
    mouse.outputInput(scene);
    mouse.removeMsgs();
}

Win32Driver::Win32Controller Win32Driver::getDirectInput()
{
    return driver;
}

Win32Keyboard* Win32Driver::getKeyboard()
{
    return &keyboard;
}

Win32Mouse* Win32Driver::getMouse()
{
    return &mouse;
}

HWND* Win32Driver::getWindowHandle()
{
    return handle;
}
