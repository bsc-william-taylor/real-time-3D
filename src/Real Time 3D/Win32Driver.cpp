
/* -------------------------------------------------
  
 @Filename  : Win32Driver.cpp
 @author	: William Taylor
 @date		: 12/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "Win32Driver.h"
#include "SceneManager.h"

// Constructor & Deconstructor
Win32Driver::Win32Driver()
	: m_pKeyboard (new Win32Keyboard()),
	  m_pMouse (new Win32Mouse())
{
}

Win32Driver::~Win32Driver()
{
	SAFE_RELEASE(m_pKeyboard);
	SAFE_RELEASE(m_pMouse);
}

// Member Functions
void Win32Driver::Initialise(HWND * Handle)
{
	// Get applications instance
	HINSTANCE Inst = GetModuleHandle(NULL);
	
	// Create the direct input driver
	DirectInput8Create(Inst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pDriver,NULL);

	// Set the handle
	m_pHandle = Handle;

	// Create both input devices
	m_pDriver->CreateDevice(GUID_SysKeyboard, (Win32Device *)m_pKeyboard, NULL);
	m_pDriver->CreateDevice(GUID_SysMouse, (Win32Device *)m_pMouse, NULL);

	// Initialise input
	m_pKeyboard->InitialiseInput(m_pHandle);
	m_pMouse->InitialiseInput(m_pHandle);
}

void Win32Driver::Update()
{
	// Get current scene
	auto Scene = SceneManager::get()->getCurrent();

	// Update & Present data to the scene
	m_pKeyboard->UpdateInput();
	m_pKeyboard->OutputInput(Scene);
	m_pKeyboard->RemoveMsgs();

	m_pMouse->UpdateInput();
	m_pMouse->OutputInput(Scene);
	m_pMouse->RemoveMsgs();
}

// Get & Set Functions
Win32Driver::Win32Controller Win32Driver::getDirectInput()
{
	return m_pDriver;
}

Win32Keyboard * Win32Driver::getKeyboard()
{
	return m_pKeyboard;
}

Win32Mouse * Win32Driver::getMouse()
{
	return m_pMouse;
}

HWND * Win32Driver::getWindowHandle()
{
	return m_pHandle;
}
