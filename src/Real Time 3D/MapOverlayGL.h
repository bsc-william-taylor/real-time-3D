
#pragma once

#include "TextureManagerGL.h"
#include "ProgramGL.h"

class MapOverlayGL
{
	SpriteGL* sprite;
	SpriteGL* map;
public:
	MapOverlayGL();
	~MapOverlayGL();

	GLvoid setOverlayImage(const std::string&);
	GLvoid setOverlayMap(const std::string&);
	GLvoid prepareShader(ProgramGL *);

	GLuint getTextureID();
};