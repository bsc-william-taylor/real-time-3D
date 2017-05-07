
#pragma once

#include "ShaderManagerGL.h"
#include "MatrixGL.h"
#include "Camera.h"

class MinimapGL
{
    ProgramGL* shader;
    MatrixGL matrix;
    Camera* camera;

    GLuint colourBuffer;
    GLuint frameBuffer;
    GLuint depthBuffer;
    GLuint vertexArray;
    GLuint vertexBuffer;

    GLfloat previousRotation;
    GLfloat previousPitch;

    vec3 previousPosition;
public:
    MinimapGL();
    ~MinimapGL();

    GLvoid initialise(Camera *);
    GLvoid renderToBuffer();
    GLvoid renderToScreen();
};