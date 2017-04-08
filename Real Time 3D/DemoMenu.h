
#pragma once

#include "Win32Timer.h"
#include "Scene.h"

#include "GL_Renderer.h"
#include "GL_Texture.h"
#include "GL_Text.h"

class DemoMenu : public Scene
{
private:

	GL_Renderer * m_pMenuRenderer;
	GL_Texture * m_pBackground;
	GL_Text * m_Header;
	GL_Text * m_Footer;

public:

	DemoMenu();
	~DemoMenu();

	void Update();
	void Render();
	void Enter();
	void Exit();

private:

	Win32Timer * m_pTimer;
	BOOL m_NextScene;

};