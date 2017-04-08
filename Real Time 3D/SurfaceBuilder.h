
#pragma once

#include "GL_Header.h"
#include "Surface.h"

class SurfaceBuilder
{
private:

	Surface * surface;
	GL_Matrix * m_Matrix;
	aiVector3D m_Point;
	aiVector3D m_Size;
	bool IgnoreArea;

public:

	SurfaceBuilder();
	~SurfaceBuilder();

	void PushSurface(GL_Matrix *);
	void PushPoint(aiVector3D);
	void EndOfMesh(int);
	
	void Ignore() {
		IgnoreArea = true;
	}
	
	Surface * Release();
};