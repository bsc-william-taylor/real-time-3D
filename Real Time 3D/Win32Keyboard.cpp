
/* -------------------------------------------------
  
 @Filename  : Win32Keyboard.cpp
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: A keyboard class that grabs keyboard data
			  from a direct input driver and outputs
			  data to a set state.

 ------------------------------------------------- */

#include "Win32Keyboard.h"
#include "Win32Codes.h"

// Constructor & Deconstructor
Win32Keyboard::Win32Keyboard()
{
	ClearInput();

	m_Hwnd = NULL;
}

Win32Keyboard::~Win32Keyboard()
{
	if(m_Keyboard != NULL)
	{
		 m_Keyboard->Unacquire();
		 m_Keyboard->Release();
		 m_Keyboard = NULL;
	}
}

// Member Functions
void Win32Keyboard::InitialiseInput(HWND * Hwnd)
{
	// Set device settings for grabbing data
	DWORD Settings = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;

	// Set settings and aquire device.
	m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	m_Keyboard->SetCooperativeLevel(*Hwnd, Settings);
	m_Keyboard->Acquire();
	m_Hwnd = Hwnd;
}

void Win32Keyboard::UpdateInput()
{
	// Aquire device and get the state
	m_Keyboard->Acquire();
	m_Keyboard->GetDeviceState(sizeof(m_KeyBuffer), &m_KeyBuffer);
}

void Win32Keyboard::OutputInput(Scene * CurrentState)
{
	// Check each key
	for (int i = 0; i < 255; i++)
	{
		// If pressed send state to state
		if(m_KeyBuffer[i] & 0x80 && !m_KeyRelease[i])
		{
			CurrentState->KeyPress(i, PRESSED);
			m_ReleaseMsg[i] = false;
			m_KeyRelease[i] = true;
		}

		// If held send state to state
		if(m_KeyRelease[i] && m_KeyBuffer[i] & 0x80)
		{
			CurrentState->KeyPress(i, HOLDING);
			m_ReleaseMsg[i] = false;
		}

		// If released send state to state
		if(!(m_KeyBuffer[i] & 0x80) && m_KeyRelease[i])
		{
			CurrentState->KeyPress(i, RELEASED);
			m_KeyRelease[i] = false;
			m_ReleaseMsg[i] = true;
		}
	}
}


void Win32Keyboard::ClearInput()
{
	// Reset arrays to initial value
	for(int i = 0; i < 255; i++)
	{
		m_KeyRelease[i] = false;
		m_ReleaseMsg[i] = false;
	}
}

void Win32Keyboard::RemoveMsgs()
{
	// Reset array to stop recording release messages
	for(int i = 0; i < 255; i++)
	{
		m_ReleaseMsg[i] = false;
	}
}