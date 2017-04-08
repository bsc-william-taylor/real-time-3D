
#pragma once

#include "GL_Renderer.h"
#include "DynamicModel.h"
#include "Win32Codes.h"
#include "ICamera.h"

class ThirdPersonCamera : public ICamera
{
private:
	
	GL_Renderer * m_pWorld;
	
	GLfloat m_AnimationStep;
	GLfloat m_Animation;
	GLfloat m_Rotation;
	GLfloat m_Pitch;
	GLfloat m_Y;

	vec3 m_CameraTranslate;
	vec3 m_CameraSpeed;
	vec3 m_Movement;

	DynamicModel * m_Model;

public:

	ThirdPersonCamera();
	~ThirdPersonCamera();

	GLvoid Initialise(GL_Renderer *);
	GLvoid KeyPress(int, int);
	GLvoid Motion(float, float);
	GLvoid CancelMovement();
	GLvoid Update();
	GLvoid Reset();

	GLvoid setPlayerModel(DynamicModel *);
	GLvoid setRotation(GLfloat);
	GLvoid setPitch(GLfloat);
	GLvoid setPosition(vec3);
	
	GLfloat getRotation();
	GLfloat getPitch();

	vec3 getTranslate();
	vec3 getPosition(vec3);
	vec3 getPosition();
};