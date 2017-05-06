
#pragma once

#include "MajorInclude.h"
#include "MinimapGL.h"
#include "ICamera.h"


class SubSurface
{
private:

	unsigned int count;

	GLboolean positionCalculated;

	vec3 m_RealPosition;
	vec3 m_RealSize;
	vec3 m_Position;
	vec3 m_Size;

public:

	SubSurface();
	~SubSurface();

	bool CollisionTest(GL_Matrix *, vec3, vec3);
	bool CollisionTest(mat4, vec3);
	bool PassPoint(vec3, vec3);
	
	void PrintSurfaceData();

	vec3 getMeshPosition();
	vec3 getMeshSize();

private:

	bool isConnected(vec3, vec3);
};