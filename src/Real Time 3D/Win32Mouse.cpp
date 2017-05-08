
#include "SceneManager.h"
#include "Win32Mouse.h"
#include "Win32Codes.h"

Win32Mouse::Win32Mouse() :
    position({0, 0})
{
	clearInput();
	removeMsgs();
}

Win32Mouse::~Win32Mouse()
{
	if(mouse != nullptr)
	{
		mouse->Unacquire();
		mouse->Release();
		mouse = nullptr;
	}
}

void Win32Mouse::initialiseInput(HWND* hWnd)
{
	DWORD settings = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
	mouse->SetDataFormat(&c_dfDIMouse2);
	mouse->SetCooperativeLevel(*hWnd, settings);
	mouse->Acquire();
	hwnd = *hWnd;
}

void Win32Mouse::updateInput()
{
	mouse->Acquire();
	mouse->GetDeviceState(sizeof(state), &state);
}

void Win32Mouse::outputInput(Scene * scene)
{
	FloatPoint pos = getMousePosition();
	
	if(pos.x != 0 || pos.y != 0)
	{
		scene->onMotion(pos.x, pos.y);
	}
	
	POINT info;
	RECT rect;

	GetCursorPos(&info);
	ScreenToClient(hwnd, &info);
	GetClientRect(hwnd, &rect);

	for (auto i = 0; i < 3; i++)
	{
		if((state.rgbButtons[i] & 0x80) && !mouseRelease[i])
		{
			scene->mousePress(i, PRESSED, info.x, rect.bottom - info.y);
			mouseRelease[i] = true;
			releaseMsg[i] = false;
		}

		if((state.rgbButtons[i] & 0x80) && mouseRelease[i])
		{
			scene->mousePress(i, HOLDING, info.x, rect.bottom - info.y);
			releaseMsg[i] = false;
		}

		if(!(state.rgbButtons[i] & 0x80) && mouseRelease[i])
		{
			scene->mousePress(i, RELEASED, info.x, rect.bottom - info.y);
			mouseRelease[i] = false;
			releaseMsg[i] = true;
		}
	}
}

void Win32Mouse::clearInput()
{
	for(int i = 0; i < 3; i++)
	{
		mouseRelease[i] = false;
	}
}

void Win32Mouse::removeMsgs()
{
	for(int i = 0; i < 3; i++)
	{
		releaseMsg[i] = false;
	}
}

Win32Mouse::FloatPoint Win32Mouse::getMousePosition()
{
	return { float(state.lX),  float(state.lY) };
}