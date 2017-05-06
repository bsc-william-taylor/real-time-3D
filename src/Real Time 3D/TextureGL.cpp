
/* -------------------------------------------------
  
 @Filename  : GL_Texture.cpp
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: Class implementation

 ------------------------------------------------- */

#include "TextureGL.h"
#include "TextureManagerGL.h"

// Constructor & Deconstructor
TextureGL::TextureGL()
	: m_Matrix(new GL_Matrix()),
	  m_Filename("")
{	
	m_Shade = vec4(1.0, 1.0, 1.0, 1.0);
	m_Setting = GL_CLAMP_TO_EDGE;
	m_UV = vec4(0, 0, 1, 1);

}

TextureGL::~TextureGL()
{
	delete m_Matrix;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

// Member Functions
GLvoid TextureGL::SurfacePlacements(GLuint m)
{
	setTexturePositions(vec2(0.0, 0.0), vec2(m, m));
}

void TextureGL::Prepare() 
{
	GLchar * vs = "data/shaders/texture.vert";
	GLchar * fs = "data/shaders/texture.frag";
	vec3 p = m_Position;
	vec3 s = m_Size;

	m_Texture = GL_Textures::get()->CreateTexture(m_Filename, m_Setting);
	m_pShader = ShaderManagerGL::get()->GetShader(vs, fs);

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

vec4 TextureGL::getShade()
{
	return this->m_Shade;
}

// Get & Set Functions
const std::string& TextureGL::getPath()
{
	return m_Filename;
}

GLvoid TextureGL::setPosition(vec3 p, vec3 s)
{
	m_Position = p;
	m_Size = p + s;
}

GLvoid TextureGL::setShade(vec4 vec)
{
	this->m_Shade = vec;
}

void TextureGL::setTexture(std::string filename, GLenum e)
{
	m_Filename = filename;
	m_Setting = e;
}

GLvoid TextureGL::setTexturePositions(vec2 a, vec2 b)
{
	m_UV = vec4(a, b);
}

GLuint TextureGL::getID()
{
	return m_Texture->m_ID;
}