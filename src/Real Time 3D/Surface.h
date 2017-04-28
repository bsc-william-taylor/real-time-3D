
#pragma once

#include "SubSurface.h"

#include "GL_Shader_Manager.h"
#include "GL_Matrix.h"

class Surface
{
private:

	GL_Program * m_pProgram;
	GL_Matrix * m_pMatrix;

	vector<SubSurface *> m_Surfaces;
	vector<vec3> m_Positions;
	vector<vec3> m_Size;
	vector<int> m_Max;

	GLuint Count;
	GLuint VAO;
	GLuint VBO;

	bool FirstTime;
	bool m_Draw;

public:

	Surface();
	~Surface();

	bool CheckForCollision(SubSurface *, ICamera *);
	bool CheckForCollision(ICamera *);
	
	void SetSize(vec3, vec3);
	void update(GL_Matrix *);
	void AddMaxMeshes(int);
	void Disable();
	void Enable();
	void render();
	void Setup();

	
	vector<SubSurface *>& getSubSurface(){ return m_Surfaces; }
	GL_Matrix * getMatrix();
};