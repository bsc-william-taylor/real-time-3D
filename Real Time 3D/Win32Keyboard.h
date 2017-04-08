
/* -------------------------------------------------
  
 @Filename  : Win32Keyboard.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: A keyboard class that grabs keyboard data
			  from a direct input driver and outputs
			  data to a set state.

 ------------------------------------------------- */

#pragma once

#include "Win32Header.h"
#include "SceneManager.h"

// Simple implementation could be expanded
class Win32Keyboard
{
private:

	typedef LPDIRECTINPUTDEVICE8 Keyboard;		// Someone left cap lock on at microsoft

private:

	Keyboard m_Keyboard;						// Keyboard Device

	bool m_KeyRelease[256];						// Array to store state
	bool m_ReleaseMsg[256];						// More information
	char m_KeyBuffer[256];						// Data taken from device

	HWND * m_Hwnd;								// Handle to the window

public:

	// Constructor & Deconstructor
	Win32Keyboard();
	~Win32Keyboard();

	// Member Functions
	void InitialiseInput(HWND *);
	void OutputInput(Scene *);
	void UpdateInput();
	void ClearInput();
	void RemoveMsgs();

	// Simple alternative to a get function
	operator Keyboard()
	{
		return m_Keyboard;
	}
};