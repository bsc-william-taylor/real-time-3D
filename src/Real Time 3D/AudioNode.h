
#pragma once

#include "ShaderManagerGL.h"
#include "TextureGL.h"
#include "MatrixGL.h"

class AudioNode
{
    ProgramGL* shader;
    TextureGL sprite;
    MatrixGL matrix;

    GLuint textureBuffer;
    GLuint vertexBuffer;
    GLuint vertexArray;
public:
    AudioNode();
    ~AudioNode();

    GLvoid initialise(vec3, vec3);
    GLvoid render();

    MatrixGL* getMatrix();
};