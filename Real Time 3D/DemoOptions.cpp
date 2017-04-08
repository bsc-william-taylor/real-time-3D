
/* -------------------------------------------------
  
 @Filename  : DemoOptions.cpp
 @author	: William Taylor
 @date		: 23/03/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "SceneManager.h"
#include "Win32Codes.h"
#include "DemoOptions.h"
#include "Demo.h"

// Constructor & Deconstructor
DemoOptions::DemoOptions()
	: m_pShowCollisionBoxes(new Button()),
	  m_pEnablePostEffects(new Button()),
	  m_pEnableWireframe(new Button()),
	  m_pBackButton(new Button()),
	  m_pRenderer(new GL_Renderer()),
	  m_pTexture(new GL_Texture()),
	  m_pHeader(new GL_Text())
{
	/* Load all assets and initialise them */
	m_pTexture->setTexture("data/img/back.png", GL_CLAMP_TO_EDGE);
	m_pTexture->getMatrix()->Ortho(vec2(0, 1280), vec2(0, 720), vec2(-1, 1));;
	m_pTexture->setPosition(vec3(0, 0, 0), vec3(1280, 720, 0));
	m_pTexture->Prepare();

	m_pHeader->setText("Demo Options");
	m_pHeader->setFont("data/img/MavenPro-Regular.ttf");
	m_pHeader->setPosition(vec2(400, 550));
	m_pHeader->setSize(100);

	m_pShowCollisionBoxes->SetPosition("Show Collision Boxes?", vec2(450, 400), vec2(400, 100));
	m_pEnablePostEffects->SetPosition("Enable Post FX Effects", vec2(450, 250), vec2(400, 100));
	m_pEnableWireframe->SetPosition("Enable Wireframe", vec2(450, 100), vec2(400, 100));
	m_pBackButton->SetPosition("Back", vec2(10, 625), vec2(200, 50));
}

DemoOptions::~DemoOptions()
{
	// Memory cleanup
	SAFE_RELEASE(m_pShowCollisionBoxes);
	SAFE_RELEASE(m_pEnablePostEffects);
	SAFE_RELEASE(m_pEnableWireframe);
	SAFE_RELEASE(m_pBackButton);

	SAFE_RELEASE(m_pRenderer);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pHeader);
}

// Member Functions
void DemoOptions::MousePress(int Key, int State, int x, int y)
{
	/* Check to see if a button was pressed and then change settings */
	if(m_pEnableWireframe->MouseState(Key, State, x, y))
	{
		if(Demo::m_gSettings.FX) {
			ActivateButton(m_pEnablePostEffects);
		}

		Demo::m_gSettings.Wireframe = !Demo::m_gSettings.Wireframe;
		Demo::m_gSettings.FX = false;
		ActivateButton(m_pEnableWireframe);
	}

	if(m_pShowCollisionBoxes->MouseState(Key, State, x, y))
	{
		Demo::m_gSettings.Boxes = !Demo::m_gSettings.Boxes;
		ActivateButton(m_pShowCollisionBoxes);
	}

	if(m_pEnablePostEffects->MouseState(Key, State, x, y))
	{
		Demo::m_gSettings.FX = !Demo::m_gSettings.FX;
		ActivateButton(m_pEnablePostEffects);
	}

	// If pressed go back to the scene manager
	if(m_pBackButton->MouseState(Key, State, x, y))
		SceneManager::get()->SwitchTo(1);
}

void DemoOptions::ActivateButton(Button * button)
{
	auto t = button->getTexture();
	vec4 v = t->getShade();
		
	if(v == vec4(0.0, 1.0, 0.0, 1.0)) 
	{
		v = vec4(1.0, 1.0, 1.0, 1.0);
	} 
	else 
	{
		v = vec4(0.0, 1.0, 0.0, 1.0);
	}
		
	t->setShade(v);
}

void DemoOptions::Update()
{
	m_pTexture->Update();
	m_pHeader->Update();
}

void DemoOptions::Render()
{
	m_pRenderer->Render2D(GL_FALSE);

	glDisable(GL_DEPTH_TEST);

	m_pRenderer->RenderTexture(m_pTexture);

	m_pShowCollisionBoxes->Render(m_pRenderer);
	m_pEnablePostEffects->Render(m_pRenderer);
	m_pEnableWireframe->Render(m_pRenderer);
	m_pBackButton->Render(m_pRenderer);
	m_pHeader->Render();

	glEnable(GL_DEPTH_TEST);
	m_pRenderer->Render2D(Demo::m_gSettings.Wireframe);
}