
/* -------------------------------------------------
  
 @Filename  : GL_Matrix.h
 @purpose	: Main Definition
 @author	: William Taylor
 @date		: 04/02/2014

 ------------------------------------------------- */

#pragma once

#include "MajorInclude.h"

class GL_Matrix
{
private:

	GLuint m_Tranformations;	// Transformation Counter
	mat4 m_Projection;			// Projection Matrix
	mat4 m_Model;				// Model Matrix
	mat4 m_View;				// View Matrix

public:

	// Constructor & Deconstructor
	GL_Matrix();				
	~GL_Matrix();		

	// Basic get operations
	GLuint getOperations();
	vec3 getRealPosition(vec3);
	mat4 getProjection();
	mat4 getModel();	
	mat4 getView();

	// Member function have detailed doc in (GL_Matrix.cpp)
	GLvoid Perspective(const float, const vec2, const vec2);
	GLvoid Ortho(const vec2, const vec2, const vec2);
	GLvoid RotateView(const float, const vec3);
	GLvoid Rotate(const float, const vec3);
	GLvoid Ortho(const vec2, const vec2);
	GLvoid TranslateView(const vec3);
	GLvoid Translate(const vec3);
	GLvoid Scale(const vec3);
	GLvoid LoadIdenditity();
	GLvoid Copy(GL_Matrix*);
};

// END