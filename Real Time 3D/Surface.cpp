
#include "Surface.h"

Surface::Surface()
	: m_Draw (false)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(0);
}

Surface::~Surface()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	SAFE_RELEASE(m_pMatrix);
	m_Draw = TRUE;
	FirstTime = true;
}

void Surface::Enable()
{
	m_Draw = GL_TRUE;
}

void Surface::Disable()
{
	m_Draw = GL_FALSE;
}

bool Surface::CheckForCollision(ICamera * camera)
{	
	if(!m_Surfaces.empty())
	{
		mat4 mat = m_pMatrix->getProjection() * m_pMatrix->getModel();
		vec3 position = camera->getPosition();
		for(unsigned int i = 0; i <  m_Surfaces.size(); i++)
		{
			if(m_Surfaces[i]->CollisionTest(mat, position))
			{
				return true;
			}
		}
	}

	return false;
}

bool Surface::CheckForCollision(SubSurface * surface, ICamera * camera)
{
	if(!m_Surfaces.empty())
	{
		vec3 point = vec3(sin(RAIDAN(camera->getRotation())), 0, cos(RAIDAN(camera->getRotation())));
		vec3 position =  camera->getPosition() + (point*= 5);
		mat4 mat = m_pMatrix->getProjection() * m_pMatrix->getModel();
		for(unsigned int i = 0; i < m_Surfaces.size(); i++)
		{
			if(m_Surfaces[i]->CollisionTest(mat, position))
			{
				return true;
			}
		}
	}

	return false;
}

void Surface::SetSize(vec3 position, vec3 size)
{
	this->m_Positions.push_back(position);
	this->m_Size.push_back(size);
}

void Surface::Render()
{
	m_pProgram->Use();

	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(0.1f);
	
	m_pProgram->setMatrix("Projection", m_pMatrix->getProjection());
	m_pProgram->setMatrix("Model", m_pMatrix->getModel());
	m_pProgram->setMatrix("View", m_pMatrix->getView());

	glDrawArrays(GL_TRIANGLES, 0, Count);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0f);
	glBindVertexArray(0);
	m_pProgram->Release();
}

void Surface::Setup()
{
	const GLchar * vs = "data/shaders/box.vert";
	const GLchar * fs = "data/shaders/box.frag";

	m_pProgram = GL_Shader_Manager::get()->GetShader(vs, fs);

	vector<vec3> m_Faces;

	m_Faces.reserve(24 * m_Surfaces.size());

	for(GLuint i = 0; i < m_Surfaces.size(); i++)
	{
		vec3 p = m_Surfaces[i]->getMeshPosition();
		vec3 s = m_Surfaces[i]->getMeshSize();

		// Front
		m_Faces.push_back(vec3(p.x, p.y, p.z));	
		m_Faces.push_back(vec3(p.x, s.y, p.z));
		m_Faces.push_back(vec3(s.x, s.y, p.z));	
		m_Faces.push_back(vec3(p.x, p.y, p.z));	
		m_Faces.push_back(vec3(s.x, p.y, p.z));
		m_Faces.push_back(vec3(s.x, s.y, p.z));	

		// Back
		m_Faces.push_back(vec3(p.x, p.y, s.z));	
		m_Faces.push_back(vec3(p.x, s.y, s.z));
		m_Faces.push_back(vec3(s.x, s.y, s.z));	
		m_Faces.push_back(vec3(p.x, p.y, s.z));	
		m_Faces.push_back(vec3(s.x, p.y, s.z));
		m_Faces.push_back(vec3(s.x, s.y, s.z));	

		// Front & Back Sides
		m_Faces.push_back(vec3(p.x, p.y, p.z));	
		m_Faces.push_back(vec3(p.x, p.y, s.z));
		m_Faces.push_back(vec3(p.x, s.y, s.z));	
		m_Faces.push_back(vec3(p.x, p.y, p.z));	
		m_Faces.push_back(vec3(p.x, s.y, p.z));
		m_Faces.push_back(vec3(p.x, s.y, s.z));	

		m_Faces.push_back(vec3(s.x, p.y, p.z));	
		m_Faces.push_back(vec3(s.x, p.y, s.z));
		m_Faces.push_back(vec3(s.x, s.y, s.z));	
		m_Faces.push_back(vec3(s.x, p.y, p.z));	
		m_Faces.push_back(vec3(s.x, s.y, p.z));
		m_Faces.push_back(vec3(s.x, s.y, s.z));
	}
	
	Count = m_Faces.size();

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_Faces.size(), &m_Faces[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}

void Surface::Update(GL_Matrix * matrix)
{
	m_pMatrix = matrix;

	if(FirstTime)
	{
		SubSurface * NewSurface = new SubSurface();
		unsigned int MeshNumber = 0;

		for(unsigned int i = 0; i < m_Positions.size(); i++)
		{
			vec3 p = m_Positions[i];
			vec3 s = m_Size[i];
			
			if(!NewSurface->PassPoint(p, s) || MeshNumber != -1 && i >= m_Max[MeshNumber])
			{
				m_Surfaces.push_back(NewSurface);
				NewSurface = new SubSurface();

				if(MeshNumber + 1 < m_Max.size())
					MeshNumber++;
				else
					MeshNumber = -1;
			}
		}

		Setup();
		
		FirstTime = false;
	}	
}

GL_Matrix * Surface::getMatrix()
{
	return m_pMatrix;
}

void Surface::AddMaxMeshes(int max)
{
	this->m_Max.push_back(max);
}