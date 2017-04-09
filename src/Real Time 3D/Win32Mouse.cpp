
/* -------------------------------------------------
  
 @Filename  : Win32Mouse.cpp
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: Class implemntation

 ------------------------------------------------- */

#include "SceneManager.h"
#include "Win32Mouse.h"
#include "Win32Codes.h"

// Constructor & Deconstructor
Win32Mouse::Win32Mouse()
{
	m_Position.x = NULL;
	m_Position.y = NULL;

	ClearInput();
	RemoveMsgs();
}

Win32Mouse::~Win32Mouse()
{
	if(m_Mouse != NULL)
	{
		// Unacqure input device & do a memory cleanup
		m_Mouse->Unacquire();
		m_Mouse->Release();
		m_Mouse = NULL;
	}
}

// Member Functions
void Win32Mouse::InitialiseInput(HWND * hWnd)
{
	// Describe settings for monitoring input.
	DWORD Settings = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
	
	// Set the settings and aquire the device from the OS.
	m_Mouse->SetDataFormat(&c_dfDIMouse2);
	m_Mouse->SetCooperativeLevel(*hWnd, Settings);
	m_Mouse->Acquire();
	m_Hwnd = *hWnd;
}

void Win32Mouse::UpdateInput()
{
	// Aquire and grab the devices state
	m_Mouse->Acquire();
	m_Mouse->GetDeviceState(sizeof(m_State), &m_State);
}

void Win32Mouse::OutputInput(Scene * scene)
{
	FLOAT_POINT pos = getMousePosition();
	
	// Only pass if there is a velocity
	if(pos.x != 0 || pos.y != 0)
	{
		scene->Motion(pos.x, pos.y);
	}
	
	// Prepare to get real mouse position
	POINT Info;
	RECT Rect;

	// get and scale to window region
	GetCursorPos(&Info);
	ScreenToClient(m_Hwnd, &Info);
	GetClientRect(m_Hwnd, &Rect);

	// Check mouse buttons state
	for (int i = 0; i < 3; i++)
	{
		// Check for a pressed button
		if((m_State.rgbButtons[i] & 0x80) && !m_MouseRelease[i])
		{
			scene->MousePress(i, PRESSED, Info.x, Rect.bottom - Info.y);
			m_MouseRelease[i] = true;
			m_ReleaseMsg[i] = false;
		}

		// Check for a button being held
		if((m_State.rgbButtons[i] & 0x80) && m_MouseRelease[i])
		{
			scene->MousePress(i, HOLDING, Info.x, Rect.bottom - Info.y);
			m_ReleaseMsg[i] = false;
		}

		// Check for a released button
		if(!(m_State.rgbButtons[i] & 0x80) && m_MouseRelease[i])
		{
			scene->MousePress(i, RELEASED, Info.x, Rect.bottom - Info.y);
			m_MouseRelease[i] = false;
			m_ReleaseMsg[i] = true;
		}
	}
}

void Win32Mouse::ClearInput()
{
	// Reset arrays holding information
	for(int i = 0; i < 3; i++)
	{
		m_MouseRelease[i] = false;
	}
}

void Win32Mouse::RemoveMsgs()
{
	// Reset arrays holding information
	for(int i = 0; i < 3; i++)
	{
		m_ReleaseMsg[i] = false;
	}
}

// Get & Set Functions
Win32Mouse::FLOAT_POINT Win32Mouse::getMousePosition()
{
	FLOAT_POINT Value;
	Value.x = FLOAT(m_State.lX);
	Value.y = FLOAT(m_State.lY);
	return Value;
}