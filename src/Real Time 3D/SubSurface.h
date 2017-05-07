
#pragma once

#include "MajorInclude.h"
#include "MinimapGL.h"
#include "Camera.h"

class SubSurface
{
    GLboolean positionCalculated;

    vec3 realPosition;
    vec3 realSize;
    vec3 position;
    vec3 size;
public:
    SubSurface();
    ~SubSurface();

    void printSurfaceData();

    bool collisionTest(MatrixGL *, vec3, vec3);
    bool collisionTest(mat4, vec3);
    bool passPoint(vec3, vec3);

    vec3 getMeshPosition();
    vec3 getMeshSize();

    bool isConnected(vec3, vec3);
};