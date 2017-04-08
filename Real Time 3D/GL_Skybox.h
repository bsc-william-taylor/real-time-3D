
#pragma once

#include "GL_Texture.h"

class GL_Skybox
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

	vector<GL_Texture *> m_SkyboxTextures;
	vector<std::string> m_Filenames;
	
	GLfloat m_Overdraw;
	GLfloat m_Distance;

public:

	GL_Skybox();
	~GL_Skybox();
	
	vector<GL_Texture *>& getTextures();
	
	GLvoid SetOverdraw(GLfloat);
	GLvoid SetDistance(GLfloat);
	GLvoid Folder(std::string);
	GLvoid Translate(vec3);
	GLvoid Update();
	GLvoid Setup();
};