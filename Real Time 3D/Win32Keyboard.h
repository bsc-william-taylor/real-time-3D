
#pragma once

#include "Win32Header.h"
#include "Scene.h"

class Demo;

class Win32Keyboard
{
	private:

		typedef LPDIRECTINPUTDEVICE8 Keyboard;

		Keyboard m_Keyboard;

		bool m_KeyRelease[256];
		bool m_ReleaseMsg[256];
		char m_KeyBuffer[256];

		HWND * m_Hwnd;

	public:

	Win32Keyboard();

		void OutputInput(Demo *, Scene *);
		void InitialiseInput(HWND *);
		void UpdateInput();
		void ClearInput();
		void RemoveMsgs();

		operator Keyboard()
		{
			return m_Keyboard;
		}

	~Win32Keyboard();
};