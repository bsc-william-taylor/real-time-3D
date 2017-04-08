
#pragma once

#include "Win32Header.h"
#include "Scene.h"

class Win32Mouse
{
	private:

	struct CursorPoint
	{
		float x; float y;
	};

	private:

		LPDIRECTINPUTDEVICE8 m_Mouse;
		DIMOUSESTATE2 m_State;

		CursorPoint m_Position;
		HWND * m_Hwnd;

		bool m_MouseRelease[3];
		bool m_ReleaseMsg[3];

	public:

	Win32Mouse();

		CursorPoint GetMousePosition();

		void OutputInput(Scene *);
		void InitialiseInput(HWND *);
		void UpdateInput();
		void ClearInput();
		void RemoveMsgs();

		operator LPDIRECTINPUTDEVICE8()
		{
			return m_Mouse;
		}

	~Win32Mouse();
};