
#include "SurfaceManager.h"
#include "SurfaceBuilder.h"

SurfaceBuilder::SurfaceBuilder()
{
	m_Point = aiVector3D(0, 0, 0); 
	m_Size = aiVector3D(0, 0, 0);
	surface = new Surface();
	IgnoreArea = false;
}

SurfaceBuilder::~SurfaceBuilder()
{
	surface->update(m_Matrix);
	SurfaceManager::get()->PushSurface(surface);
}

void SurfaceBuilder::PushPoint(aiVector3D p)
{
	if(m_Point == aiVector3D(0, 0, 0))
	{
		m_Point = p;
		m_Size = p;
	}
	
	// Look for position
	if(p.x < m_Point.x)
		m_Point.x = p.x;
	if(p.y < m_Point.y)
		m_Point.y = p.y;
	if(p.z < m_Point.z)
		m_Point.z = p.z;

	// Look for size
	if(m_Size.x < p.x)
		m_Size.x = p.x;
	if(m_Size.y < p.y)
		m_Size.y = p.y;
	if(m_Size.z < p.z)
		m_Size.z = p.z;
}

Surface * SurfaceBuilder::Release()
{
	Surface * temp = surface;
	return temp;
}

void SurfaceBuilder::PushSurface(GL_Matrix * matrix)
{
	m_Matrix = matrix;

	GLfloat x = m_Size.x - m_Point.x;
	GLfloat y = m_Size.y - m_Point.y;
	GLfloat z = m_Size.z - m_Point.z;

	GLfloat Area = (x*x) + (y*y) + (z*z);

	if(IgnoreArea || Area >= 150.0 && Area <= 5000.0)
	{
		vec3 glmPosition = vec3(m_Point.x, m_Point.y, m_Point.z);
		vec3 glmSize = vec3(m_Size.x, m_Size.y, m_Size.z);

		surface->SetSize(glmPosition, glmSize);
		surface->Enable();
	}

	m_Point = aiVector3D(0, 0, 0); 
	m_Size = aiVector3D(0, 0, 0);
}

void SurfaceBuilder::EndOfMesh(int i)
{
	surface->AddMaxMeshes(i);
}