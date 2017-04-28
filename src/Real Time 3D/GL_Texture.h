
/* -------------------------------------------------
  
 @Filename  : GL_Texture.h
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: Simple GL_Texture object that sets up 
			  a texture, it can be drawn using the 
			  draw texture method in the GL_Renderer 
			  Class.

 ------------------------------------------------- */

#pragma once

#include "GL_Texture_Manager.h"
#include "GL_Shader_Manager.h"
#include "GL_Matrix.h"

class GL_Texture
{
private:	

	GL_Program * m_pShader;
	GL_Sprite * m_Texture;	
	GL_Matrix * m_Matrix;
							
	GLuint VAO;
	GLuint VBO;

	vec3 m_Position;
	vec4 m_Shade;
	vec3 m_Size;
	vec4 m_UV;

	std::string m_Filename;	
	GLenum m_Setting;	
		
public:

	// Constructor & Deconstructor
	GL_Texture();
	~GL_Texture();

	// Member Functions
	GLvoid SurfacePlacements(GLuint);
	GLvoid update(){}
	GLvoid Prepare();

	// Get & Set Function
	GLvoid setTexturePositions(vec2, vec2);
	GLvoid setTexture(std::string, GLenum);
	GLvoid setPosition(vec3, vec3);

	const std::string& getPath();
	GL_Matrix * getMatrix(){ return m_Matrix; }
	GL_Program * getProgram(){ return m_pShader; }
	GLuint getVAO(){ return VAO; }
	GLuint getID();

	GLvoid setShade(vec4);
	vec4 getShade();
};
