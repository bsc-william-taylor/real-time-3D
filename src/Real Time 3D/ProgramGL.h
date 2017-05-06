
/* -------------------------------------------------
  
 @Filename  : GL_Program.h
 @purpose	: Main Definition
 @author	: William Taylor
 @date		: 04/02/2014

 ------------------------------------------------- */

#pragma once

#include "MajorInclude.h"

class GL_Program 
{
private:

	std::string VertexFilename;
	std::string FragFilename;

	GLuint Shaders[2];	// Array for storing shader ID's.
	GLuint Program;		// ID for the current program.

public:

	// Simple ENUM so the user can load each shader easily.
	enum Types { VERTEX_SHADER,	FRAG_SHADER, };

public:

	// Constructor & Deconstructor
	GL_Program();
	~GL_Program();

	// Member Functions
	void Load(Types, const std::string&);
	void OutputLog(Types);
	void Release();
	void Create();
	void Link();
	void Use();

	// Set Functions
	GLvoid setMatrix(const std::string&, glm::mat4);
	GLvoid setTexture(GLuint);

	// Get Functions
	GLuint getAttribute(const std::string&);
	GLuint getUniform(const std::string&);
	GLuint getID(){ return Program; }

	std::string getVS() { return VertexFilename; }
	std::string getFS() { return FragFilename; }

private:

	// private read function file
	std::string ReadFile(const std::string&);
};

typedef GL_Program Shader;