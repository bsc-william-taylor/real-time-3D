
#pragma once

#include "ShaderManagerGL.h"
#include "TextureGL.h"
#include "MatrixGL.h"

class AudioNode
{
	GL_Program * m_pShader;
	TextureGL * m_pSprite;
	GL_Matrix * m_pMatrix;

	GLuint VTBO;
	GLuint VBO;
	GLuint VAO;
public:
	AudioNode();
	~AudioNode();

	GLvoid Initialise(vec3, vec3);
	GLvoid render();

	GL_Matrix * getMatrix();
};