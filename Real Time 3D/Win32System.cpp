
#include "Win32System.h"
#include <stdio.h>

Win32System::Win32System()
	: m_Quit (FALSE)
{
	if(FAILED(CoInitialize(NULL)))
	{
		MessageBox(NULL, "Error With Com", "Error !", MB_OK);
	}

	m_pWindow = new Win32Window();
	m_pInput = new Win32Driver();
}

Win32System::~Win32System()
{
	SAFE_RELEASE(m_pWindow);
	SAFE_RELEASE(m_pInput);
}

void Win32System::SetWindowTraits(CHAR * c, SIZES s)
{
	m_pWindow->SetTraits(c, s.x, s.y, s.w, s.h);
}

bool Win32System::WindowRunning() 
{
	return(m_pWindow->Update());
}

void Win32System::Initialise()
{
	m_pWindow->Initialise();
	m_pWindow->Display(Win32Window::WINDOWED);
	m_pWindow->EnableOpenGL();

	HWND Handle = m_pWindow->GetHandle();

	m_pInput->Initialise(&Handle);

	GLenum error = glewInit();
	
	glewExperimental = GL_TRUE;

	if(error != GLEW_OK) 
	{
		printf("Error: %s\n", glewGetErrorString(error));
		system("pause");
	}
}

Win32Window * Win32System::VGetWindow()
{
	return m_pWindow;
}

void Win32System::SwapWindowBuffers()
{
	SwapBuffers(GetDC(m_pWindow->GetHandle()));
}

void Win32System::Update()
{
	m_pWindow->Update();
	m_pInput->Update();
}
