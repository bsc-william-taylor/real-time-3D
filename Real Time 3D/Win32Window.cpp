
#include "Win32Window.h"

HWND Win32Window::m_Window = NULL;
CHAR Win32Window::m_Key = NULL;

Win32Window::Win32Window() 
{
	HWND HandleDesktop = GetDesktopWindow();																
	RECT DesktopSize;

	GetWindowRect(HandleDesktop, &DesktopSize);															

	m_Sizes.h = DesktopSize.bottom/2;
	m_Sizes.w = DesktopSize.right/2;
	m_Title = "Default Title";
	m_Sizes.x = NULL;
	m_Sizes.y = NULL;
	
	m_Fullscreen = false;
}

CHAR Win32Window::getLastKey()
{
	CHAR t = m_Key;
	m_Key = -1;
	return t;
}


void Win32Window::SetTraits(TCHAR * Title, int x, int y, int Width, int Height)
{
	m_Title = Title;

	m_Sizes.h = Height;
	m_Sizes.w = Width;
	m_Sizes.x = x;
	m_Sizes.y = y;
}

void Win32Window::MakeFullscreen()
{
	m_Fullscreen = true;
}

void Win32Window::Initialise() 
{
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

	RegisterClassEx(&WindowClass);
}

bool Win32Window::Update()
{
	PeekMessage(&GetMsg(), NULL, NULL, NULL, PM_REMOVE);

	if(GetMsg().message == WM_QUIT) 
	{
		return FALSE;
	}

	TranslateMessage(&GetMsg());
	DispatchMessage(&GetMsg());
	return TRUE;
}

LRESULT CALLBACK Win32Window::WndProc(HWND Hwnd, UINT Message, WPARAM wParam, LPARAM lParam) 
{
	switch (Message)
	{
		case WM_DESTROY: PostQuitMessage(0); return NULL;
		
		case WM_CHAR:
		{
			m_Key = (CHAR)wParam;
			break;
		}
	
		default:
			return DefWindowProc(Hwnd, Message, wParam, lParam);
	}	

	return NULL;
}

void Win32Window::Display(Type type) 
{
	HINSTANCE Inst = GetModuleHandle(NULL);
	DWORD Set = WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX;

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

	UpdateWindow(m_Window);
	ShowWindow(m_Window, SW_SHOW);
}

void Win32Window::EnableOpenGL()
{
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

	HGLRC hRC = wglCreateContext(hDC);

	wglMakeCurrent(hDC, hRC);
}

Win32Window::~Win32Window()
{
	wglMakeCurrent(NULL, NULL);
	DestroyWindow(m_Window);
}