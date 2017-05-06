
#pragma once

#include "ShaderManagerGL.h"
#include "MatrixGL.h"

class PostProcessorGL
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

	PostProcessorGL();
	~PostProcessorGL();

	GLvoid Initialise(GLuint, GLuint);
	GLvoid execute();
	GLvoid Enable();

	GLvoid setColourChannels(vec4);
};