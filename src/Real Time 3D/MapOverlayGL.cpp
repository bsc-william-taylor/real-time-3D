
#include "MapOverlayGL.h"

MapOverlayGL::MapOverlayGL()
	: m_pSprite(NULL),
	  m_pMap(NULL)
{
}

MapOverlayGL::~MapOverlayGL()
{
}

GLvoid MapOverlayGL::SetOverlayImage(const std::string& filename)
{
	m_pSprite = TextureManagerGL::get()->CreateTexture(filename, GL_REPEAT);
}

GLvoid MapOverlayGL::SetOverlayMap(const std::string& filename)
{
	m_pMap = TextureManagerGL::get()->CreateTexture(filename, GL_CLAMP_TO_EDGE);
}

GLvoid MapOverlayGL::PrepareShader(GL_Program * program)
{
	GLint Overlay = glGetUniformLocation(program->getID(), "Overlay");

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_pMap->m_ID);
	glUniform1i(Overlay, 1);

	GLint Texture = glGetUniformLocation(program->getID(), "Texture");

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_pSprite->m_ID);
	glUniform1i(Texture, 2);
}

GLuint MapOverlayGL::GetID()
{
	return m_pSprite->m_ID;
}