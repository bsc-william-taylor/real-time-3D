
#pragma once

#include "RendererGL.h"
#include "DynamicModel.h"
#include "Win32Codes.h"
#include "Camera.h"

class ThirdPersonCamera : public Camera
{
    RendererGL* renderer;

    GLfloat animationStep;
    GLfloat animation;
    GLfloat rotation;
    GLfloat pitch;
    GLfloat y;

    vec3 cameraTranslate;
    vec3 cameraSpeed;
    vec3 movement;

    DynamicModel* animatedModel;
public:
    ThirdPersonCamera();
    ~ThirdPersonCamera();

    GLvoid initialise(RendererGL*);
    GLvoid onKeyPress(int, int);
    GLvoid onMotion(float, float);
    GLvoid cancelMovement();
    GLvoid onUpdate(bool);
    GLvoid Reset();

    GLvoid setPlayerModel(DynamicModel*);
    GLvoid setRotation(GLfloat);
    GLvoid setPitch(GLfloat);
    GLvoid setPosition(vec3);

    GLfloat getRotation();
    GLfloat getPitch();

    vec3 getTranslate();
    vec3 getPosition(vec3);
    vec3 getPosition();
};