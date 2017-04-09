
/* -------------------------------------------------
  
 @Filename  : GL_Texture_Manager.h
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: A texture manager for opengl needs
              a lot of work done.

 ------------------------------------------------- */

#pragma once

#include "GL_Header.h"

#pragma region Custom Types
struct GL_Sprite
{
	vector<vector<RGBQUAD>> Colour;
	std::string m_TextureName;
	GLint Height;
	GLint Width;
	GLuint m_ID;

	~GL_Sprite() { glDeleteTextures(1, &m_ID); }
};

#pragma endregion

class GL_TextureManager
{
private:

	static GL_TextureManager * m_pManager;		// Singletons Instance
	vector<GL_Sprite *> m_Textures;				// Store all textures created for memory checking

public:

	// Deconstructor
	~GL_TextureManager();

	static GL_TextureManager * get();			// Static get function for accessing the class

	// Member Functions
	GL_Sprite * CreateTexture(GLubyte *, GLuint, GLuint, GLenum);
	GL_Sprite * CreateTexture(const std::string&, GLenum);
	GL_Sprite * CreateGlyph(FT_Face, GLenum);

	GLvoid FreeTextures();

	GLuint getTextureCount();

private:

	// Constructor
	GL_TextureManager();

	GL_Sprite * LoadTexture(const std::string&, GLenum e);
};

// Helps Reduce line length
typedef GL_TextureManager GL_Textures;