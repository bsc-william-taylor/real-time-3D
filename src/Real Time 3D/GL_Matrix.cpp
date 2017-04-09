
/* -------------------------------------------------
  
 @Filename  : GL_Matrix.cpp
 @purpose	: Class implementation
 @author	: William Taylor
 @date		: 04/02/2014

 ------------------------------------------------- */

#include "GL_Matrix.h"

// Constructor & Deconstructor
GL_Matrix::GL_Matrix()
	: m_Tranformations (0)
{
	m_Projection = mat4(1.0f);
}

GL_Matrix::~GL_Matrix()
{ 
	
}

// Member Functions
GLvoid GL_Matrix::Perspective(const float fov, const vec2 v, const vec2 d)
{
	// Calculate screen apsect ratio
	float aspect_ratio = v.x / v.y;
	
	// Set idenditity just in case
	m_Projection = mat4(1.0f);
	m_Projection = perspective(fov, aspect_ratio, d.x, d.y);
}

GLvoid GL_Matrix::Copy(GL_Matrix* matrix)
{
	m_Projection = matrix->getProjection();
	m_Model = matrix->getModel();
	m_View = matrix->getView();
}

vec3 GL_Matrix::getRealPosition(vec3 position)
{
	vec4 Real = m_Projection * m_Model * vec4(position, 1.0);
	return(vec3(Real.x, Real.y, Real.z));
}

GLvoid GL_Matrix::LoadIdenditity()
{
	// Reset Model Matrix & Reset Counter
	m_Tranformations = 0;
	m_Model = mat4(1.0f);
	m_View = mat4(1.0f);
}

GLvoid GL_Matrix::Ortho(const vec2 w, const vec2 h, const vec2 d)
{
	// Set idenditity just in case
	m_Projection = mat4(1.0f);
	m_Projection = ortho(w.x, w.y, h.x, h.y, d.x, d.y);
}

GLvoid GL_Matrix::Scale(const vec3 scale)
{
	// Count the number of transformations (Debug tool)
	m_Tranformations++;

	// Apply approiate transformation
	m_Model = glm::scale(m_Model, scale);
}

GLvoid GL_Matrix::RotateView(const float angle, const vec3 vec)
{
	// Count the number of transformations (Debug tool)
	m_Tranformations++;
	m_View = rotate(m_View, angle, vec);
}

GLvoid GL_Matrix::Ortho(const vec2 w, const vec2 h)
{
	m_View = mat4(1.0f);
	m_View = ortho(w.x, w.y, h.x, h.y, -1.0f, 1.0f);
}

GLvoid GL_Matrix::Translate(const vec3 vector)
{
	// Count the number of transformations (Debug tool)
	m_Tranformations++;

	// Apply approiate transformation
	m_Model = translate(m_Model, vector);
}

GLvoid GL_Matrix::TranslateView(const vec3 vector)
{
	// Count the number of transformations (Debug tool)
	m_Tranformations++;

	// Apply approiate transformation
	m_View = translate(m_View, vector);
}

GLvoid GL_Matrix::Rotate(const float angle, const vec3 vector)
{
	// Count the number of transformations (Debug tool)
	m_Tranformations++;

	// Apply approiate transformation
	m_Model = rotate(m_Model, angle, vector);	
}

// Get & Set Functions
mat4 GL_Matrix::getProjection()
{
	/* Get methods are provided for each matrix as the data 
		will need to be inserted into the vertex shader */
	return m_Projection;
}

mat4 GL_Matrix::getModel()
{
	return m_Model;
}

mat4 GL_Matrix::getView()
{
	return(m_View);
}

uint GL_Matrix::getOperations()
{
	/* Can be used to check there arnt any accidental
		transformations going on in the background */
	return m_Tranformations;
}

// END