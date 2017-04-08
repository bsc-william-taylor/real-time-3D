
#pragma once

#include "GL_Renderer.h"
#include "GL_Texture.h"
#include "Scene.h"

class Options : public Scene
{
private:

	GL_Renderer * m_pRenderer;
	GL_Texture * m_pTexture;
	GL_Text * m_pFooter;
	GL_Text * m_pHeader;

public:

	Options();
	~Options();

	void Motion(GLfloat, GLfloat);
	void KeyPress(GLint, GLint);
	void Update();
	void Render();
	void Enter();
};