
#include "GL_Skybox.h"

GL_Skybox::GL_Skybox()
{
	m_Distance = 1000.0f;
	m_Overdraw = 0.0f;

	for(int i = 0; i < 5; i++)
	{
		m_SkyboxTextures.push_back(new GL_Texture());
	}
}

GL_Skybox::~GL_Skybox()
{
}

GLvoid GL_Skybox::Folder(std::string filename)
{
	m_Filenames.push_back(filename + "right.jpg");
	m_Filenames.push_back(filename + "front.jpg");
	m_Filenames.push_back(filename + "back.jpg");
	m_Filenames.push_back(filename + "left.jpg");
	m_Filenames.push_back(filename + "top.jpg");
}

void GL_Skybox::update()
{
	GLfloat position = (GLfloat)(m_Distance / 2.0f);

	auto Right = m_SkyboxTextures[RIGHT]->getMatrix();
	auto Left = m_SkyboxTextures[LEFT]->getMatrix();

	Right->Translate(vec3(position, 0, 0));
	Right->Rotate(-1.57079633f, vec3(0.0, 1.0, 0.0));

	Left->Translate(vec3(-position, 0, 0));
	Left->Rotate(1.57079633f, vec3(0.0, 1.0, 0.0));
}

GLvoid GL_Skybox::Translate(vec3 vector)
{
	for(GLint i = 0; i < 5; i++)
	{
		m_SkyboxTextures[i]->getMatrix()->TranslateView(-vector);
	}
}

void GL_Skybox::Setup()
{	
	vec3 Position[5];
	vec3 Size[5];

	GLfloat position = (GLfloat)(m_Distance / 2.0f);

	Position[RIGHT]	= vec3(-position, -position,  00000.0f);
	Position[FRONT]	= vec3(-position, -position,  position);	
	Position[BACK]	= vec3(-position, -position, -position);	
	Position[LEFT]	= vec3(-position, -position,  00000.0f);
	Position[TOP]	= vec3(-position, position, -position);	
	
	Size[RIGHT]	= vec3(m_Distance, m_Distance, 0000000.0f);
	Size[FRONT]	= vec3(m_Distance, m_Distance, 0000000.0f);	
	Size[BACK]	= vec3(m_Distance, m_Distance, 0000000.0f);
	Size[LEFT]	= vec3(m_Distance, m_Distance, 0000000.0f);
	Size[TOP]	= vec3(m_Distance, 0.0000000f, m_Distance);

	m_SkyboxTextures[FRONT]->setTexturePositions(vec2(1.0, 0.0), vec2(0.0, 1.0));
		
	for(GLint i = 0; i < 5; i++)
	{
		m_SkyboxTextures[i]->setPosition(Position[i], Size[i]);
		m_SkyboxTextures[i]->setTexture(m_Filenames[i], GL_CLAMP_TO_EDGE);
	}
}

vector<GL_Texture *>& GL_Skybox::getTextures()
{
	return m_SkyboxTextures;
}

GLvoid GL_Skybox::SetDistance(GLfloat distance)
{
	m_Distance = distance;
}

GLvoid GL_Skybox::SetOverdraw(GLfloat overdraw)
{
	m_Overdraw = overdraw;
}