
#pragma once

#include "Win32Header.h"

#define WND_CALLBACK static LRESULT __stdcall

struct SIZES {
	int x;
	int y;
	int w;
	int h;
};

class Win32Window 
{
public:

	enum Type { FULLSCREEN, WINDOWED };

private:

	WND_CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	static CHAR m_Key;
	BOOL m_Fullscreen;
	TCHAR * m_Title;
	SIZES m_Sizes;
	MSG m_Msg;

public:

	Win32Window();
	~Win32Window();

	void DrawFunc(void *);
	void Display(Type);
	void Initialise();
	bool Update();

	void SetTraits(TCHAR *, int, int, int, int);
	void MakeFullscreen();
	void EnableOpenGL();

	HWND& GetHandle(){ return m_Window; }
	MSG& GetMsg(){ return m_Msg; }

	static CHAR getLastKey();

public:

	static HWND m_Window;
};