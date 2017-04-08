
#include "Win32Mouse.h"
#include "SceneManager.h"

Win32Mouse::Win32Mouse()
{
	m_Position.x = NULL;
	m_Position.y = NULL;
	
}

void Win32Mouse::RemoveMsgs()
{
	
}

void Win32Mouse::InitialiseInput(HWND * hWnd)
{
	DWORD Settings = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
	
	m_Mouse->SetDataFormat(&c_dfDIMouse2);
	m_Mouse->SetCooperativeLevel(*hWnd, Settings);
	m_Mouse->Acquire();
	m_Hwnd = hWnd;
}

void Win32Mouse::UpdateInput()
{
	size_t Size = sizeof(m_State);

	m_Mouse->Acquire();
	m_Mouse->GetDeviceState(Size, &m_State);
}

void Win32Mouse::OutputInput(Scene * scene)
{
	CursorPoint pos = GetMousePosition();
	
	if(pos.x != 0 || pos.y != 0)
	{
		scene->Motion(pos.x, pos.y);
	}
}

void Win32Mouse::ClearInput()
{

}

Win32Mouse::CursorPoint Win32Mouse::GetMousePosition()
{
	CursorPoint Value;

	Value.x = float(m_State.lX);
	Value.y = float(m_State.lY);
	
	return Value;
}

Win32Mouse::~Win32Mouse()
{
	if(m_Mouse != NULL)
	{
		m_Mouse->Unacquire();
		m_Mouse->Release();
		m_Mouse = NULL;
	}
}