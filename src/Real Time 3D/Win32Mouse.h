
/* -------------------------------------------------
  
 @Filename  : Win32Mouse.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: A mouse class that grabs mouse data
			  from a direct input driver and outputs
			  data to a set state.

 ------------------------------------------------- */

#pragma once

#include "Win32Header.h"
#include "SceneManager.h"

// Simple implementation could be expanded
class Win32Mouse
{
private:

	struct FLOAT_POINT					// Custom struct for position
	{
		FLOAT x; 
		FLOAT y;
	};

private:

	LPDIRECTINPUTDEVICE8 m_Mouse;		// Pointer to device
	DIMOUSESTATE2 m_State;				// Mouse State var

	FLOAT_POINT m_Position;				// Cursor Velocity
	HWND m_Hwnd;						// Handle to window

	bool m_MouseRelease[3];				// Track Current state arrays
	bool m_ReleaseMsg[3];				// Track Current state arrays

public:

	// Constructor & Deconstructor
	Win32Mouse();
	~Win32Mouse();

	// Member Functions
	void InitialiseInput(HWND * hWnd);
	void OutputInput(Scene * scene);
	void UpdateInput();
	void ClearInput();
	void RemoveMsgs();

	// Rather this that another get function
	operator LPDIRECTINPUTDEVICE8()
	{
		return m_Mouse;
	}

	// Get & Set Functions
	FLOAT_POINT getMousePosition();
};

// END