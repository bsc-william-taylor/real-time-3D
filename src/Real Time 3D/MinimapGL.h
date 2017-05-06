
#pragma once

#include "ShaderManagerGL.h"
#include "MatrixGL.h"
#include "ICamera.h"

class MinimapGL
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

	MinimapGL();
	~MinimapGL();

	GLvoid Initialise(ICamera *);
	GLvoid RenderToBuffer();
	GLvoid RenderToScreen();
};