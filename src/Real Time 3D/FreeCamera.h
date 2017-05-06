
#pragma once

#include "RendererGL.h"
#include "Win32Codes.h"
#include "ICamera.h"

class FreeCamera : public ICamera
{
private:
	
	RendererGL * m_pWorld;
	
	GLfloat m_Rotation;
	GLfloat m_Pitch;

	vec3 m_CameraTranslate;
	vec3 m_CameraSpeed;
	vec3 m_Movement;

public:

	FreeCamera();
	~FreeCamera();

	GLvoid Initialise(RendererGL *);
	GLvoid keyPress(int, int);
	GLvoid motion(float, float);
	GLvoid CancelMovement();
	GLvoid update();

	GLvoid setRotation(GLfloat);
	GLvoid setPitch(GLfloat);
	GLvoid setPosition(vec3);
	
	GLfloat getRotation();
	GLfloat getPitch();

	vec3 getTranslate();
	vec3 getPosition();
};