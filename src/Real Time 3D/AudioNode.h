
#pragma once

#include "GL_Shader_Manager.h"
#include "GL_Texture.h"
#include "GL_Matrix.h"

class AudioNode
{
private:

	GL_Program * m_pShader;
	GL_Texture * m_pSprite;
	GL_Matrix * m_pMatrix;

	GLuint VTBO;
	GLuint VBO;
	GLuint VAO;

public:

	AudioNode();
	~AudioNode();

	GLvoid Initialise(vec3, vec3);
	GLvoid Render();

	GL_Matrix * getMatrix() {
		return m_pMatrix;
	}
};