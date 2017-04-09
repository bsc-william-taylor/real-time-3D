
#pragma once

#include "GL_Texture_Manager.h"
#include "GL_Program.h"

class GL_MapOverlay
{
private:

	GL_Sprite * m_pSprite;
	GL_Sprite * m_pMap;

public:

	GL_MapOverlay();
	~GL_MapOverlay();

	GLvoid SetOverlayImage(const std::string&);
	GLvoid SetOverlayMap(const std::string&);
	GLvoid PrepareShader(GL_Program *);

	GLuint GetID();
};