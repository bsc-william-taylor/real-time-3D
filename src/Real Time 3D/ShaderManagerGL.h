
/* -------------------------------------------------
  
 @Filename  : GL_Shader_Manager.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: A Manager for all shaders in the
			  scene.

 ------------------------------------------------- */

#pragma once

#include "ProgramGL.h" 

class ShaderManagerGL
{
private:

	static ShaderManagerGL * m_pInstance;
	vector<GL_Program *> m_Programs;

public:

	// Deconstructor
	~ShaderManagerGL();

	// Member Functions
	GL_Program * GetShader(const std::string&, const std::string&);
	GLvoid ReleaseShaders();

	// Get Functions
	static ShaderManagerGL * get();

private:

	// Constructor
	ShaderManagerGL();
};