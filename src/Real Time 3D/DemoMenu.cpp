
/* -------------------------------------------------
  
 @Filename  : DemoMenu.cpp
 @author	: William Taylor
 @date		: 23/03/2014
 @purpose	: Class implementation

 ------------------------------------------------- */


#include "SceneManager.h"
#include "Win32Codes.h"
#include "DemoMenu.h"

// Constructor & Deconstructor
DemoMenu::DemoMenu()
{
	m_pMenuRenderer = new GL_Renderer();
	m_pBackground = new GL_Texture();
	m_pTimer = new Win32Timer();
	m_Footer = new GL_Text();
	m_Header = new GL_Text();

	m_pBackground->setTexture("data/img/back.png", GL_CLAMP_TO_EDGE);
	m_pBackground->getMatrix()->Ortho(vec2(0, 1280), vec2(0, 720), vec2(-1, 1));
	m_pBackground->setPosition(vec3(0, 0, 0), vec3(1280, 720, 0));

	m_Header->setText("Real Time 3D - B00235610");
	m_Header->setFont("data/img/MavenPro-Regular.ttf");
	m_Header->setPosition(vec2(30, 625));
	m_Header->setSize(75);
	
	m_Footer->setText("Please be patient while the demo loads...");
	m_Footer->setFont("data/img/MavenPro-Regular.ttf");
	m_Footer->setPosition(vec2(800, 25));
	m_Footer->setSize(25);

	m_pMenuRenderer->PushTexture(m_pBackground);
	m_pMenuRenderer->Prepare();
	m_Alpha = 0.0f;
}

DemoMenu::~DemoMenu()
{
	SAFE_RELEASE(m_pMenuRenderer);
	SAFE_RELEASE(m_pTimer);	
	SAFE_RELEASE(m_Header);
	SAFE_RELEASE(m_Footer);
}

// Member Functions
void DemoMenu::Update()
{
	m_pBackground->setShade(vec4(1, 1, 1, m_Alpha));
	m_pTimer->Stop();

	m_pMenuRenderer->Update();
	m_Header->Update();
	m_Footer->Update();

	m_Alpha += 0.05f;
}

void DemoMenu::Enter() 
{
	m_pTimer->Start();
}

void DemoMenu::Render()
{

	m_pMenuRenderer->Render2D(GL_FALSE);
	m_pMenuRenderer->Render();
	m_Header->Render();
	m_Footer->Render();
	m_pMenuRenderer->Render3D(GL_FALSE);

	if(m_pTimer->Difference(TimeType::MS) > 1000)
	{
		SceneManager::get()->SwitchTo(1);
	}
}