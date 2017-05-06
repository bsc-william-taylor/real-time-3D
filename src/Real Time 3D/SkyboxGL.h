
#pragma once

#include "TextureGL.h"

class SkyboxGL
{
private:

	enum SIDES 
	{ 
		RIGHT,
		FRONT, 
		BACK, 
		LEFT,
		TOP, 
	};

private:

	vector<TextureGL *> m_SkyboxTextures;
	vector<std::string> m_Filenames;
	
	GLfloat m_Overdraw;
	GLfloat m_Distance;

public:

	SkyboxGL();
	~SkyboxGL();
	
	vector<TextureGL *>& getTextures();
	
	GLvoid SetOverdraw(GLfloat);
	GLvoid SetDistance(GLfloat);
	GLvoid Folder(std::string);
	GLvoid Translate(vec3);
	GLvoid update();
	GLvoid Setup();
};