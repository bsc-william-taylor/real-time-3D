
#include "SceneManager.h"
#include "Win32Codes.h"
#include "Options.h"

Options::Options()
{
	m_pRenderer = new GL_Renderer();

	m_pTexture = new GL_Texture();
	m_pTexture->setTexture("data/img/back.png", GL_CLAMP_TO_EDGE);
	m_pTexture->getMatrix()->Ortho(vec2(0, 1600), vec2(0, 900), vec2(-1, 1));;
	m_pTexture->setPosition(vec3(0, 0, 0), vec3(1600, 900, 0));
	m_pTexture->Prepare();

	m_pHeader = new GL_Text();
	m_pHeader->setText("Demo Options");
	m_pHeader->setFont("data/img/MavenPro-Regular.ttf");
	m_pHeader->setPosition(vec2(550, 750));
	m_pHeader->setSize(100);

	m_pFooter = new GL_Text();
	m_pFooter->setText("Press escape to go back");
	m_pFooter->setFont("data/img/MavenPro-Regular.ttf");
	m_pFooter->setPosition(vec2(550, 750));
	m_pFooter->setSize(100);
}

Options::~Options()
{

}

void Options::Motion(GLfloat, GLfloat)
{

}

void Options::KeyPress(GLint Key, GLint State)
{
	if(Key == ESCAPE && State == RELEASED)
	{
		SceneManager::get()->SwitchTo(1);
	}
}

void Options::Update()
{
	m_pTexture->Update();
	m_pHeader->Update();
}

void Options::Render()
{
	glDisable(GL_DEPTH_TEST);
	
	m_pRenderer->RenderTexture(m_pTexture);

	m_pHeader->Render();

	glDisable(GL_DEPTH_TEST);
	
}

void Options::Enter()
{

}