
#include "SubSurface.h"

SubSurface::SubSurface()
{
	m_Position = vec3(0, 0, 0);
	m_Size = vec3(0, 0, 0);
	count = 0;
}

SubSurface::~SubSurface()
{
}

bool SubSurface::CollisionTest(GL_Matrix * matrix, vec3 position, vec3 size)
{
	mat4 mat = matrix->getProjection() * matrix->getModel();
	if(CollisionTest(mat, position)) {
		return true;
	}

	if(CollisionTest(mat, size)) {
		return true;
	}
	
	return false;
}

bool SubSurface::CollisionTest(mat4 mat, vec3 position)
{
	vec3 pos = vec3();//vec3(mat * (vec4(m_Position, 1.0)));
	vec3 sx = vec3();//vec3(mat * (vec4(m_Size, 1.0)));
	
	if(position.x >= pos.x && position.x <= sx.x)
	{
		if(position.z >= pos.z && position.z <= sx.z)
		{
			if(position.y >= pos.y && position.y <= sx.y)
			{
				return true;	
			}
		}
	}

	return false;
}

vec3 SubSurface::getMeshPosition()
{
	return m_Position;
}

vec3 SubSurface::getMeshSize()
{
	return m_Size;
}

void SubSurface::PrintSurfaceData()
{
	std::cout << " : " << m_Position.x << " : " << m_Position.y << " : " << m_Position.z << std::endl;
	std::cout << " : " << m_Size.x << " : " << m_Size.y << " : " << m_Size.z << std::endl;
}

bool SubSurface::PassPoint(vec3 p, vec3 s)
{
	if(m_Position == vec3(0, 0, 0))
	{
		m_Position = p;
		m_Size = s;
		return true;
	}

	if(isConnected(p, s))
	{
		if(p.x < m_Position.x)
			m_Position.x = p.x;
		if(p.y < m_Position.y)
			m_Position.y = p.y;	
		if(p.z < m_Position.z)
			m_Position.z = p.z;	

		if(s.x > m_Size.x)
			m_Size.x = s.x;		
		if(s.y > m_Size.y)
			m_Size.y = s.y; 
		if(s.z > m_Size.z)
			m_Size.z = s.z; 
		
		return true;
	}

	return false;
}

bool SubSurface::isConnected(vec3 p, vec3 s)
{
	if(p.x == m_Position.x || p.y == m_Position.y || p.z == m_Position.z)
	{
		return true;
	}
	if(s.x == m_Size.x || s.y == m_Size.y || s.z == m_Size.z)
		return true;
	else
		return false;
}
