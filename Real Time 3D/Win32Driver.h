
#pragma once

#include "Win32Keyboard.h"
#include "Win32Mouse.h"

class Win32Driver
{
	typedef LPDIRECTINPUTDEVICE8 Win32Device;
	typedef LPDIRECTINPUT8 Win32Controller;

	private:

		Win32Controller m_Driver;
		Win32Keyboard * m_Keyboard;
		Win32Mouse * m_Mouse;

		static HWND * Handle;
		bool m_Disable;

	public:

	Win32Driver();
	~Win32Driver();

	void Initialise(HWND *);
	void DisableInput();
	void Update();
};