
#pragma once

#include "MajorInclude.h"

class Camera
{
public:
    virtual GLvoid onKeyPress(int, int) = 0;
    virtual GLvoid onMotion(float, float) = 0;
    virtual GLvoid onUpdate() {}

    virtual GLvoid cancelMovement() = 0;
    virtual GLvoid setRotation(GLfloat) = 0;
    virtual GLvoid setPitch(GLfloat) = 0;
    virtual GLvoid setPosition(vec3) = 0;

    virtual GLfloat getRotation() = 0;
    virtual GLfloat getPitch() = 0;

    virtual vec3 getTranslate() = 0;
    virtual vec3 getPosition(vec3) { return vec3(); }
    virtual vec3 getPosition() = 0;
};