
#pragma once

#include "Win32Header.h"
#include "SceneManager.h"

class Win32Mouse
{
    struct FloatPoint
    {
        float x, y;
    };

	LPDIRECTINPUTDEVICE8 mouse;		
	DIMOUSESTATE2 state;				
	HWND hwnd;						

	bool mouseRelease[3];				
	bool releaseMsg[3];				
    FloatPoint position;			
public:
	Win32Mouse();
	~Win32Mouse();

    FloatPoint getMousePosition();

	void initialiseInput(HWND * hWnd);
	void outputInput(Scene * scene);
	void updateInput();
	void clearInput();
	void removeMsgs();

	operator LPDIRECTINPUTDEVICE8()
	{
		return mouse;
	}
};