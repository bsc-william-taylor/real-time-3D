
#pragma once

#include "GL_Shader_Manager.h"
#include "GL_Matrix.h"
#include "ICamera.h"

class GL_Minimap
{
private:

	GL_Program * m_pShader;
	GL_Matrix * m_pMatrix;

	ICamera * m_pCamera;

	GLuint ColourBuffer;
	GLuint FrameBuffer;
	GLuint DepthBuffer;

	GLfloat m_PreviousRotation;
	GLfloat m_PreviousPitch;
	vec3 m_PreviousPosition;

	GLuint VAO;
	GLuint VBO;

public:

	GL_Minimap();
	~GL_Minimap();

	GLvoid Initialise(ICamera *);
	GLvoid RenderToBuffer();
	GLvoid RenderToScreen();
};