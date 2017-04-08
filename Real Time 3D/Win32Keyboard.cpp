
#include "Win32Keyboard.h"
#include "Win32Codes.h"
#include "Demo.h"

Win32Keyboard::Win32Keyboard()
{
	ClearInput();

	m_Hwnd = NULL;
}

void Win32Keyboard::InitialiseInput(HWND * Hwnd)
{
	DWORD Settings = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;

	m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	m_Keyboard->SetCooperativeLevel(*Hwnd, Settings);
	m_Keyboard->Acquire();
	m_Hwnd = Hwnd;
}

void Win32Keyboard::UpdateInput()
{
	size_t Size = sizeof(m_KeyBuffer);

	m_Keyboard->Acquire();
	m_Keyboard->GetDeviceState(Size, &m_KeyBuffer);
}

void Win32Keyboard::OutputInput(Demo * Demo, Scene * CurrentState)
{
	for (int i = 0; i < 255; i++)
	{
		if (m_KeyBuffer[i] & 0x80 && !m_KeyRelease[i])
		{
			CurrentState->KeyPress(i, PRESSED);
			Demo->KeyPress(i, PRESSED);
			m_ReleaseMsg[i] = false;
			m_KeyRelease[i] = true;
		}

		if (m_KeyRelease[i] && m_KeyBuffer[i] & 0x80)
		{
			CurrentState->KeyPress(i, HOLDING);
			Demo->KeyPress(i, HOLDING);
			m_ReleaseMsg[i] = false;
		}

		if (!(m_KeyBuffer[i] & 0x80) && m_KeyRelease[i])
		{
			CurrentState->KeyPress(i, RELEASED);
			Demo->KeyPress(i, RELEASED);
			m_KeyRelease[i] = false;
			m_ReleaseMsg[i] = true;
		}
	}
}


void Win32Keyboard::ClearInput()
{
	for(int i = 0; i < 255; i++)
	{
		m_KeyRelease[i] = false;
		m_ReleaseMsg[i] = false;
	}
}

void Win32Keyboard::RemoveMsgs()
{
	for(int i = 0; i < 255; i++)
	{
		m_ReleaseMsg[i] = false;
	}
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