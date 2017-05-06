
#pragma once

#include "Win32Keyboard.h"
#include "Win32Mouse.h"

class Win32Driver
{
    using Win32Device = LPDIRECTINPUTDEVICE8;
    using Win32Controller = LPDIRECTINPUT8;

	Win32Controller driver;					
	Win32Keyboard keyboard;			
	Win32Mouse mouse;						

	HWND* handle;							
public:
	Win32Driver();
	~Win32Driver();

	void initialise(HWND* hWnd);
	void onUpdate();

	Win32Controller getDirectInput();
	Win32Keyboard* getKeyboard();
	Win32Mouse* getMouse();

	HWND * getWindowHandle();
};