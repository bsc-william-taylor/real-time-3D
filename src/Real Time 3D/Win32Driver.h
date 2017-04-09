
/* -------------------------------------------------
  
 @Filename  : Win32Driver.h
 @author	: William Taylor
 @date		: 12/02/2014
 @purpose	: Acts as a easy interface to setup
			  multiple input devices.

 ------------------------------------------------- */

#pragma once

#include "Win32Keyboard.h"
#include "Win32Mouse.h"

// Currently support 2 devices : Keyboard & Mouse
class Win32Driver
{
private:

	typedef LPDIRECTINPUTDEVICE8 Win32Device;	// Custom definitions because someone 
	typedef LPDIRECTINPUT8 Win32Controller;		// at microsoft left caps lock on

private:

	Win32Controller m_pDriver;					// DirectInput object
	Win32Keyboard * m_pKeyboard;				// Ptr To Keyboard Class
	Win32Mouse * m_pMouse;						// Ptr To Mouse Class

	HWND * m_pHandle;							// Handle To Window.

public:

	// Constructor & Deconstructor
	Win32Driver();
	~Win32Driver();

	// Member Functions
	void Initialise(HWND * hWnd);
	void Update();

	// Get & Set Functions
	Win32Controller getDirectInput();
	Win32Keyboard * getKeyboard();
	Win32Mouse * getMouse();

	HWND * getWindowHandle();
};

// END