
#pragma once

#include "ShaderManagerGL.h"
#include "MatrixGL.h"

class PostProcessorGL
{
	ProgramGL* program;
	MatrixGL matrix;

	GLuint vertexArrayObject;
	GLuint textureBuffer;
	GLuint vertexBuffer;
	GLuint depthBuffer;
	GLuint frameBuffer;

	vec4 colour;
public:
	PostProcessorGL();
	~PostProcessorGL();

	GLvoid initialise(GLuint, GLuint);
	GLvoid execute();
	GLvoid enable();

	GLvoid setColourChannels(vec4);
};