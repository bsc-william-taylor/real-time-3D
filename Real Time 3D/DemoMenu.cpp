
#include "DemoMenu.h"
#include "Win32Codes.h"
#include "SceneManager.h"

DemoMenu::DemoMenu()
	: m_pMenuRenderer(new GL_Renderer()),
	  m_pBackground(new GL_Texture()),
	  m_pTimer(new Win32Timer()),
	  m_Header(new GL_Text()),
	  m_Footer(new GL_Text())
{
	m_pBackground->setTexture("data/img/back.png", GL_CLAMP_TO_EDGE);
	m_pBackground->getMatrix()->Ortho(vec2(0, 1600), vec2(0, 900), vec2(-1, 1));;
	m_pBackground->setPosition(vec3(0, 0, 0), vec3(1600, 900, 0));
	
	m_Header->setText("Real Time 3D - B00235610");
	m_Header->setFont("data/img/MavenPro-Regular.ttf");
	m_Header->setPosition(vec2(30, 800));
	m_Header->setSize(100);

	m_Footer->setText("Please be patient while the demo loads...");
	m_Footer->setFont("data/img/MavenPro-Regular.ttf");
	m_Footer->setPosition(vec2(1150, 10));
	m_Footer->setSize(25);

	m_pMenuRenderer->PushTexture(m_pBackground);
	m_pMenuRenderer->Prepare();

	m_NextScene = FALSE;
}

DemoMenu::~DemoMenu()
{
}

void DemoMenu::Update()
{
	m_pTimer->Stop();

	if(m_pTimer->Difference(TimeType::MS) > 32)
	{
		m_NextScene = TRUE;
	}
	else
	{
		m_pMenuRenderer->Update();
		m_Header->Update();
		m_Footer->Update();
	}
}

void DemoMenu::Exit()
{
	SAFE_RELEASE(m_pMenuRenderer);
	SAFE_RELEASE(m_pTimer);	
	SAFE_RELEASE(m_Header);
	SAFE_RELEASE(m_Footer);
}

void DemoMenu::Enter() 
{
	m_pTimer->Start();
}

void DemoMenu::Render()
{
	glDisable(GL_DEPTH_TEST);
	
	m_pMenuRenderer->Render();
	m_Header->Render();
	m_Footer->Render();
	
	glEnable(GL_DEPTH_TEST);

	if(m_NextScene)
	{
		SceneManager::get()->SwitchTo(1);
	}
}