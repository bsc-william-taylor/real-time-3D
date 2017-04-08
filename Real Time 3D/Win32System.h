
/* -------------------------------------------------
  
 @Filename  : Win32System.h
 @author	: William Taylor
 @date		: 12/02/2014
 @purpose	: A simple interface class to simplify 
			  how a user would set up a window and 
			  input devices.

 ------------------------------------------------- */

#pragma once

#include "Win32Window.h"
#include "Win32Driver.h"

class Win32System
{
private:

	Win32Window::Type m_Type;			// The type of window to be set up
	Win32Window * m_pWindow;			// ptr to the window class
	Win32Driver * m_pInput;				// a ptr to the input class

	BOOL m_Quit;						// quit ?

public:

	// Constructor & Deconstructor
	Win32System();
	~Win32System();

	// Member Functions
	void SwapWindowBuffers();
	void Initialise();
	void Update();
	void Show();

	bool WindowRunning();

	// Set & Get Functions
	void setWindowTraits(CHAR *, Window::SIZES);
	void setWindowType(Window::Type);

	Win32Window * getWindow();
};