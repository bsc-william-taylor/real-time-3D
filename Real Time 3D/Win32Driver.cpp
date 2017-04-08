
#include "Win32Driver.h"
#include "SceneManager.h"

HWND * Win32Driver::Handle = NULL;

Win32Driver::Win32Driver()
	: m_Disable(false)
{
	m_Keyboard = new Win32Keyboard();
	m_Mouse = new Win32Mouse();

}

void Win32Driver::Initialise(HWND * Handle)
{
	HINSTANCE Inst = GetModuleHandle(NULL);
	
	DirectInput8Create(Inst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_Driver,NULL);

	m_Driver->CreateDevice(GUID_SysKeyboard, (Win32Device *)m_Keyboard, NULL);
	m_Driver->CreateDevice(GUID_SysMouse, (Win32Device *)m_Mouse, NULL);

	this->Handle = Handle;

	m_Keyboard->InitialiseInput(this->Handle);
	m_Mouse->InitialiseInput(this->Handle);
}

void Win32Driver::Update()
{
	auto Scene = SceneManager::get()->getCurrent();
	auto e = SceneManager::get()->getEngine();

	m_Keyboard->UpdateInput();
	m_Mouse->UpdateInput();

	if(!m_Disable) 
	{
		m_Keyboard->OutputInput(e, Scene);
	} 

	if(!m_Disable) 
	{
		m_Mouse->OutputInput(Scene);
	}

	m_Keyboard->RemoveMsgs();
	m_Mouse->RemoveMsgs();
}

void Win32Driver::DisableInput() 
{
//	m_Disable = !m_Disable;
}

Win32Driver::~Win32Driver()
{
	SAFE_RELEASE(m_Keyboard);
	SAFE_RELEASE(m_Mouse);
}