
#pragma once

#include "GL_Renderer.h"
#include "Win32Codes.h"
#include "ICamera.h"

class FirstPersonCamera : public ICamera
{
private:
	
	GL_Renderer * m_pWorld;
	
	GLfloat m_Rotation;
	GLfloat m_Pitch;

	vec3 m_CameraTranslate;
	vec3 m_CameraSpeed;
	vec3 m_Movement;

public:

	FirstPersonCamera();
	~FirstPersonCamera();

	GLvoid Initialise(GL_Renderer *);
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