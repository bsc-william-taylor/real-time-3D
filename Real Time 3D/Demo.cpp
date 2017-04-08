
/* -------------------------------------------------
  
 @Filename  : Demo.cpp
 @author	: William Taylor
 @date		: 23/03/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "GL_Texture_Manager.h"
#include "GL_Shader_Manager.h"
#include "DemoOptions.h"
#include "Win32Codes.h"
#include "SceneManager.h"
#include "DemoMenu.h"
#include "DemoScene.h"
#include "Demo.h"
#include "Memory.h"

// Initialise Settings
Demo::DemoSettings Demo::m_gSettings;

// Constructor & Deconstructor
Demo::Demo()
	: m_FPS(60)
{
	// Get scene manager
	m_pScenes = SceneManager::get();
	m_pScenes->PassEngine(this);

	// Set global settings
	m_gSettings.Wireframe = false;
	m_gSettings.Boxes = false;
	m_gSettings.FX = false;
}

Demo::~Demo()
{
	// Delete managers
	delete GL_TextureManager::get();
	delete GL_Shader_Manager::get();
	delete SceneManager::get();

	// Release all variables
	SAFE_RELEASE(m_pTimer);
	SAFE_RELEASE(m_pWin32);
}

// Member Functions
void Demo::Execute()
{
	// Initialise the demo
	Init_Scenes();
	Init_OpenGL();

	// Game Loop
	while(m_pWin32->WindowRunning()) 
	{		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_pWin32->Update();
		m_TimeLeft = 0;

		m_pScenes->UpdateManager();		
		m_pWin32->SwapWindowBuffers();

		while(m_TimeLeft < (GLfloat)1.0e9/m_FPS)
		{
			m_pTimer->Stop();
			m_TimeLeft = m_pTimer->Difference(TimeType::NS);
		}
		
		m_pTimer->Start();
	}
}

void Demo::HideConsole()
{
	// Hide console & report any error
	if(FreeConsole() != NULL) {
		return;
	} 
	
	printf("Error cant hide console");
}

// Private Functions
void Demo::Init_OpenGL()
{
	// Enable GL States
	glEnable(GL_DEPTH_TEST);
	
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	// Set GL Hints
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void Demo::Init_Scenes()
{
	// Initialise Scenes
	m_pScenes = SceneManager::get();
	m_pScenes->PushState(new DemoMenu());
	m_pScenes->PushState(new DemoScene());
	m_pScenes->PushState(new DemoOptions());
	m_pScenes->StartFrom(0);

	m_pScenes->getCurrent()->Enter();
	
	// Init timer for controlling window redraw rate
	m_pTimer = new Win32Timer();
	m_pTimer->Start();

}

// Set & Get Functions
void Demo::WindowSize(int x, int y, int w, int h)
{
	// Set window sizes
	Win32Window::SIZES WindowSizes;

	WindowSizes.w = w;
	WindowSizes.h = h;
	WindowSizes.x = x;
	WindowSizes.y = y;

	// Initialise the windows system
	m_pWin32 = new Win32System();
	m_pWin32->setWindowTraits("Real Time 3D", WindowSizes);
	m_pWin32->setWindowType(Win32Window::Type::WINDOWED);
	m_pWin32->Initialise();
	m_pWin32->Show();
}

void Demo::RedrawRate(int FPS)
{
	m_FPS = FPS;
}