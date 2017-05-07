
#pragma once

#include "MajorInclude.h"

class MatrixGL
{
    mat4 projectionMatrix;
    mat4 modelMatrix;
    mat4 viewMatrix;
public:
    MatrixGL();
    ~MatrixGL();

    mat4 getProjection();
    mat4 getModel();
    mat4 getView();

    GLvoid perspective(const float, const vec2, const vec2);
    GLvoid ortho(const vec2, const vec2, const vec2);
    GLvoid rotateView(const float, const vec3);
    GLvoid rotate(const float, const vec3);
    GLvoid ortho(const vec2, const vec2);
    GLvoid translateView(const vec3);
    GLvoid translate(const vec3);
    GLvoid scale(const vec3);
    GLvoid loadIdenditity();
    GLvoid copy(MatrixGL*);

    vec3 getRealPosition(vec3);
};