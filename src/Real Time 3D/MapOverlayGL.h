
#pragma once

#include "TextureManagerGL.h"
#include "ProgramGL.h"

class MapOverlayGL
{
private:

	GL_Sprite * m_pSprite;
	GL_Sprite * m_pMap;

public:

	MapOverlayGL();
	~MapOverlayGL();

	GLvoid SetOverlayImage(const std::string&);
	GLvoid SetOverlayMap(const std::string&);
	GLvoid PrepareShader(GL_Program *);

	GLuint GetID();
};