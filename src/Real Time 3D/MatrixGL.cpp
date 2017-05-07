
#include "MatrixGL.h"

MatrixGL::MatrixGL()
{
    projectionMatrix = mat4(1.0f);
}

MatrixGL::~MatrixGL()
{
}

GLvoid MatrixGL::perspective(const float fov, const vec2 v, const vec2 d)
{
    float aspectRatio = v.x / v.y;
    projectionMatrix = mat4(1.0f);
    projectionMatrix = glm::perspective(fov, aspectRatio, d.x, d.y);
}

GLvoid MatrixGL::copy(MatrixGL* matrix)
{
    projectionMatrix = matrix->getProjection();
    modelMatrix = matrix->getModel();
    viewMatrix = matrix->getView();
}

vec3 MatrixGL::getRealPosition(vec3 position)
{
    vec4 Real = projectionMatrix * modelMatrix * vec4(position, 1.0);
    return(vec3(Real.x, Real.y, Real.z));
}

GLvoid MatrixGL::loadIdenditity()
{
    modelMatrix = mat4(1.0f);
    viewMatrix = mat4(1.0f);
}

GLvoid MatrixGL::ortho(const vec2 w, const vec2 h, const vec2 d)
{
    projectionMatrix = mat4(1.0f);
    projectionMatrix = glm::ortho(w.x, w.y, h.x, h.y, d.x, d.y);
}

GLvoid MatrixGL::scale(const vec3 scale)
{
    modelMatrix = glm::scale(modelMatrix, scale);
}

GLvoid MatrixGL::rotateView(const float angle, const vec3 vec)
{
    viewMatrix = glm::rotate(viewMatrix, angle, vec);
}

GLvoid MatrixGL::ortho(const vec2 w, const vec2 h)
{
    viewMatrix = mat4(1.0f);
    viewMatrix = glm::ortho(w.x, w.y, h.x, h.y, -1.0f, 1.0f);
}

GLvoid MatrixGL::translate(const vec3 vector)
{
    modelMatrix = glm::translate(modelMatrix, vector);
}

GLvoid MatrixGL::translateView(const vec3 vector)
{
    viewMatrix = glm::translate(viewMatrix, vector);
}

GLvoid MatrixGL::rotate(const float angle, const vec3 vector)
{
    modelMatrix = glm::rotate(modelMatrix, angle, vector);
}

mat4 MatrixGL::getProjection()
{
    return projectionMatrix;
}

mat4 MatrixGL::getModel()
{
    return modelMatrix;
}

mat4 MatrixGL::getView()
{
    return(viewMatrix);
}