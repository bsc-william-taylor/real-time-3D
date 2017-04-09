
/* -------------------------------------------------
  
 @Filename  : GL_Texture.cpp
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: Class implementation

 ------------------------------------------------- */

#include "GL_Texture.h"
#include "GL_Texture_Manager.h"

// Constructor & Deconstructor
GL_Texture::GL_Texture()
	: m_Matrix(new GL_Matrix()),
	  m_Filename("")
{	
	m_Shade = vec4(1.0, 1.0, 1.0, 1.0);
	m_Setting = GL_CLAMP_TO_EDGE;
	m_UV = vec4(0, 0, 1, 1);

}

GL_Texture::~GL_Texture()
{
	delete m_Matrix;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

// Member Functions
GLvoid GL_Texture::SurfacePlacements(GLuint m)
{
	setTexturePositions(vec2(0.0, 0.0), vec2(m, m));
}

void GL_Texture::Prepare() 
{
	GLchar * vs = "data/shaders/texture.vert";
	GLchar * fs = "data/shaders/texture.frag";
	vec3 p = m_Position;
	vec3 s = m_Size;

	m_Texture = GL_Textures::get()->CreateTexture(m_Filename, m_Setting);
	m_pShader = GL_Shader_Manager::get()->GetShader(vs, fs);

	GLfloat data[] =  {
		p.x, p.y, p.z, m_UV.x, m_UV.y,
		p.x, s.y, s.z, m_UV.x, m_UV.w,
		s.x, p.y, p.z, m_UV.z, m_UV.y,
		s.x, s.y, s.z, m_UV.z, m_UV.w
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 20, data, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, 0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (GLvoid*)12);
	
	glBindVertexArray(0);
}

vec4 GL_Texture::getShade()
{
	return this->m_Shade;
}

// Get & Set Functions
const std::string& GL_Texture::getPath()
{
	return m_Filename;
}

GLvoid GL_Texture::setPosition(vec3 p, vec3 s)
{
	m_Position = p;
	m_Size = p + s;
}

GLvoid GL_Texture::setShade(vec4 vec)
{
	this->m_Shade = vec;
}

void GL_Texture::setTexture(std::string filename, GLenum e)
{
	m_Filename = filename;
	m_Setting = e;
}

GLvoid GL_Texture::setTexturePositions(vec2 a, vec2 b)
{
	m_UV = vec4(a, b);
}

GLuint GL_Texture::getID()
{
	return m_Texture->m_ID;
}