
#include "GL_Texture_Manager.h"
#include "GL_Shader_Manager.h"
#include "Options.h"
#include "Win32Codes.h"
#include "SceneManager.h"
#include "DemoMenu.h"
#include "DemoScene.h"
#include "Demo.h"
#include "Memory.h"

Demo::Demo()
{
	SetConsoleTitle("Debug Console");
	m_pScenes = SceneManager::get();
	m_pScenes->PassEngine(this);
	m_FPS = 60;
}

Demo::~Demo()
{
	delete GL_TextureManager::get();
	delete GL_Shader_Manager::get();
	delete SceneManager::get();

	SAFE_RELEASE(m_pTimer);
	SAFE_RELEASE(m_pWin32);
}

void Demo::SetWindowSize(int x, int y, int w, int h)
{
	SIZES WindowSizes;

	WindowSizes.w = w;
	WindowSizes.h = h;
	WindowSizes.x = x;
	WindowSizes.y = y;

	m_pWin32 = new Win32System();
	m_pWin32->SetWindowTraits("Real Time 3D", WindowSizes);
	m_pWin32->Initialise();
}


void Demo::KeyPress(int Key, int State)
{
	if(Key == ARROW_UP && State == PRESSED) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} 
	
	if(Key == ARROW_DOWN && State == PRESSED) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Demo::SetRedrawRate(int FPS)
{
	m_FPS = FPS;
}

void Demo::Execute()
{
	Init_Scenes();
	Init_OpenGL();

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

void Demo::Init_OpenGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}


void Demo::Init_Scenes()
{
	m_pScenes = SceneManager::get();
	m_pScenes->PushState(new DemoMenu());
	m_pScenes->PushState(new DemoScene());
	m_pScenes->PushState(new Options());
	m_pScenes->StartFrom(0);

	m_pScenes->getCurrent()->Enter();

	m_pTimer = new Win32Timer();
	m_pTimer->Start();

}

void Demo::HideConsole()
{
	if(FreeConsole()) 
	{
		printf("Console Hidden");
	} 
	else
	{
		printf("Error Cant Hide Console");
	}
}
