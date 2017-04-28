
/* -------------------------------------------------
  
 @Filename  : Win32Window.cpp
 @author	: William Taylor
 @date		: 12/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "Win32Window.h"

// Constructor & Deconstructor
Win32Window::Win32Window() 
{
	// Setup a default size for the window
	HWND HandleDesktop = GetDesktopWindow();																
	RECT DesktopSize;

	GetWindowRect(HandleDesktop, &DesktopSize);															

	m_Sizes.h = DesktopSize.bottom/2;
	m_Sizes.w = DesktopSize.right/2;
	m_Title = "Default Title";
	m_Sizes.x = NULL;
	m_Sizes.y = NULL;
}

Win32Window::~Win32Window()
{
	// Destroy Context & Window
	wglDeleteContext(m_Context);
	wglMakeCurrent(NULL, NULL);
	DestroyWindow(m_Window);
}

void Win32Window::Initialise() 
{
	// Setup a simple window class
	WNDCLASSEX WindowClass;

	WindowClass.hCursor			= LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	WindowClass.hIcon			= LoadIcon(NULL, MAKEINTRESOURCE(IDI_WINLOGO));
	WindowClass.hbrBackground   = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WindowClass.style		    = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	WindowClass.cbSize			= sizeof(WNDCLASSEX);	
	WindowClass.lpszClassName	= "W";															
	WindowClass.hInstance		= GetModuleHandle(NULL);												
	WindowClass.lpfnWndProc		= WndProc;																
	WindowClass.hIconSm			= NULL;
	WindowClass.lpszMenuName	= 0;	
	WindowClass.cbClsExtra		= 0;		
	WindowClass.cbWndExtra		= 0;

	// Register the class
	RegisterClassEx(&WindowClass);
}

bool Win32Window::update()
{
	// Peek to see a WM_QUIT message
	PeekMessage(&GetMsg(), NULL, NULL, NULL, PM_REMOVE);
	
	// if found tell the program to quit
	if(GetMsg().message == WM_QUIT) 
	{
		return FALSE;
	}

	// Translate & Dispatch mess
	TranslateMessage(&GetMsg());
	DispatchMessage(&GetMsg());
	return TRUE;
}

LRESULT CALLBACK Win32Window::WndProc(HWND Hwnd, UINT Message, WPARAM wParam, LPARAM lParam) 
{
	// Handle Destroy callback event nothing more
	switch(Message)
	{
		case WM_DESTROY: PostQuitMessage(0); return NULL;
		
		default:
			return DefWindowProc(Hwnd, Message, wParam, lParam);
	}	
}

void Win32Window::Display(Type type) 
{
	// Get window instance
	HINSTANCE Inst = GetModuleHandle(NULL);
	DWORD Set = WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX;

	// Make fullscreen if need be
	if(type == Win32Window::FULLSCREEN)
	{
		DEVMODE Screen;

		ZeroMemory(&Screen, sizeof(DEVMODE));

		Screen.dmSize			= sizeof(DEVMODE);
		Screen.dmPelsHeight		= m_Sizes.h;
		Screen.dmPelsWidth		= m_Sizes.w;
		Screen.dmBitsPerPel		= 32;
		Screen.dmFields			= DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		if (ChangeDisplaySettings(&Screen, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
		{
			RECT rect;
		
			rect.bottom = m_Sizes.h;
			rect.right = m_Sizes.w;
			rect.left = NULL;
			rect.top = NULL;

			AdjustWindowRectEx(&rect, WS_POPUP, false, WS_EX_APPWINDOW);
		}

		m_Window = CreateWindowEx(0, "W", m_Title, WS_POPUP, m_Sizes.x, m_Sizes.y, m_Sizes.w, m_Sizes.h, 0, 0, Inst, 0);
	} 
	else
	{
		m_Window = CreateWindowEx(0, "W", m_Title, Set, m_Sizes.x, m_Sizes.y, m_Sizes.w, m_Sizes.h, 0, 0, Inst, 0);
	}

}

void Win32Window::EnableOpenGL()
{
	// Setup a new format descriptor that allows opengl
	PIXELFORMATDESCRIPTOR pfd;

	HDC hDC = GetDC(m_Window);
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize			= sizeof(pfd);
	pfd.nVersion		= 1;
	pfd.cColorBits		= 32;
	pfd.cDepthBits		= 32;
	pfd.iLayerType		= PFD_MAIN_PLANE;
	pfd.dwFlags			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType		= PFD_TYPE_RGBA;

	int iFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, iFormat, &pfd);

	m_Context = wglCreateContext(hDC);

	// Set the new format to current
	wglMakeCurrent(hDC, m_Context);
}

// Get & Set Functions
HWND& Win32Window::GetHandle()
{ 
	return m_Window; 
}

MSG& Win32Window::GetMsg()
{ 
	return m_Msg; 
}

void Win32Window::setTraits(TCHAR * Title, int x, int y, int Width, int Height)
{
	m_Title = Title;

	m_Sizes.h = Height;
	m_Sizes.w = Width;
	m_Sizes.x = x;
	m_Sizes.y = y;
}

