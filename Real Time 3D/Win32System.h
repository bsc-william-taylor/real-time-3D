
#pragma once

#include "Win32Window.h"
#include "Win32Driver.h"

class Win32System
{
private:

	Win32Window * m_pWindow;
	Win32Driver * m_pInput;

	BOOL m_Quit;

public:

	Win32System();
	~Win32System();

	bool WindowRunning();

	void SetWindowTraits(CHAR *, SIZES);
	void SwapWindowBuffers();
	void Initialise();
	void Update();

	Win32Window * VGetWindow();

	Win32Driver * getInput(){ return m_pInput; }
};