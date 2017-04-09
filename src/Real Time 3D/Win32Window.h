
/* -------------------------------------------------
  
 @Filename  : Win32Window.h
 @author	: William Taylor
 @date		: 12/02/2014
 @purpose	: A Window class that constructs & 
			  manages a win32 window.

 ------------------------------------------------- */

#pragma once

#include "Win32Header.h"

class Win32Window 
{
public:

	struct SIZES { UINT x, y, w, h; };			// Type to simplify setting the windows size.
	enum Type { FULLSCREEN, WINDOWED };			// Enum to set the type of window to open

private:

	HGLRC m_Context;		// Window Context;
	HWND m_Window;			// Window Handle
	TCHAR * m_Title;		// Window Title
	SIZES m_Sizes;			// Window Sizes
	MSG m_Msg;				// Window Msgs

public:

	// Constructor & Deconstructor
	Win32Window();
	~Win32Window();

	// Member Functions
	void EnableOpenGL();
	void Display(Type);
	void Initialise();
	bool Update();

	// Get & Set Functions
	void setTraits(TCHAR *, int, int, int, int);
	void setWindowTraits(Type);

	HWND& GetHandle();
	MSG& GetMsg();

private:

	static LRESULT __stdcall WndProc(HWND, UINT, WPARAM, LPARAM);	// Window Message handler
};

// Typedef to make accessing types nicer 
typedef Win32Window Window;