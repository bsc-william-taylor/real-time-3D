
#pragma once

#include "GL_Shader_Manager.h"
#include "GL_Matrix.h"

class GL_PostProcessor
{
private:

	GL_Program * m_pProgram;
	GL_Matrix * m_pMatrix;

	GLuint VertexArrayObject;
	GLuint TextureBuffer;
	GLuint VertexBuffer;
	GLuint DepthBuffer;
	GLuint FrameBuffer;
	GLuint Passes;

	vec4 colour;

public:

	GL_PostProcessor();
	~GL_PostProcessor();

	GLvoid Initialise(GLuint, GLuint);
	GLvoid execute();
	GLvoid Enable();

	GLvoid setColourChannels(vec4);
};