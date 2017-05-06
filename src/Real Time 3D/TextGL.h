
/* -------------------------------------------------
  
 @Filename  : GL_Text.h
 @author	: William Taylor
 @date		: 04/02/2014
 @purpose	: OpenGL class that can render 
			  text using the FreeType lib.

 ------------------------------------------------- */

#pragma once

#include "TextureManagerGL.h"
#include "TextureGL.h"

class TextGL
{
private:

	FT_Library m_Library;					// Ptr to the library
	FT_Face m_Face;							// Ptr to the face
 
	std::string m_Fontname;					// Font Filename
	std::string m_Text;						// Text To Render

	vec2 m_Position;						// Position to render from.

	GLboolean loaded;
	GLuint m_FontSize;						// Font Size
	
	GL_Program * m_pShader;		
	GL_Matrix * m_Matrix;

public:

	// Constructor & Deconstructor
	TextGL();
	~TextGL();

	// Member Functions
	GLvoid render();
	GLvoid Prepare();
	GLvoid update();

	// Set & Get Functions
	GLvoid setPosition(vec2);
	GLvoid setFont(std::string);
	GLvoid setText(std::string);
	GLvoid setSize(GLuint);

	GLuint getHeight();
	GLuint getWidth();

	GL_Program * getProgram() { return m_pShader; }
	GL_Matrix * getMatrix() { return m_Matrix; }

private:

	struct Character
	{
		GL_Sprite * Sprite;
		GLuint VBO;
	};

	vector<Character *> m_Characters;
};