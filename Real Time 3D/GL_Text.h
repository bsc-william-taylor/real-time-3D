
/* -------------------------------------------------
  
 @Filename  : GL_Text.h
 @author	: William Taylor
 @date		: 04/02/2014
 @purpose	: OpenGL class that can render 
			  text using the FreeType lib.

 ------------------------------------------------- */

#pragma once

#include "GL_Texture_Manager.h"
#include "GL_Texture.h"

class GL_Text
{
private:

	FT_Library m_Library;					// Ptr to the library
	FT_Face m_Face;							// Ptr to the face
 
	std::string m_Fontname;					// Font Filename
	std::string m_Text;						// Text To Render

	GLuint m_FontSize;						// Font Size
	vec2 m_Position;						// Position to render from.

	GLuint VBO;
	GLuint VAO;

	GL_Program * m_pShader;		
	GL_Matrix * m_Matrix;


public:

	// Constructor & Deconstructor
	GL_Text();
	~GL_Text();

	// Member Functions
	GLvoid Render();
	GLvoid Prepare();
	GLvoid Update();

	// Set & Get Functions
	GLvoid setPosition(vec2);
	GLvoid setFont(std::string);
	GLvoid setText(std::string);
	GLvoid setSize(GLuint);

	GLuint getHeight();
	GLuint getWidth();

	GL_Program * getProgram() { return m_pShader; }
	GL_Matrix * getMatrix() { return m_Matrix; }
};