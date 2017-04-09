
/* -------------------------------------------------
  
 @Filename  : GL_Shader_Manager.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: A Manager for all shaders in the
			  scene.

 ------------------------------------------------- */

#pragma once

#include "GL_Program.h" 

class GL_Shader_Manager
{
private:

	static GL_Shader_Manager * m_pInstance;
	vector<GL_Program *> m_Programs;

public:

	// Deconstructor
	~GL_Shader_Manager();

	// Member Functions
	GL_Program * GetShader(const std::string&, const std::string&);
	GLvoid ReleaseShaders();

	// Get Functions
	static GL_Shader_Manager * get();

private:

	// Constructor
	GL_Shader_Manager();
};