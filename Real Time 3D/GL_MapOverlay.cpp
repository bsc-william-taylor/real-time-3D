
#include "GL_MapOverlay.h"

GL_MapOverlay::GL_MapOverlay()
	: m_pSprite(NULL),
	  m_pMap(NULL)
{
}

GL_MapOverlay::~GL_MapOverlay()
{
}

GLvoid GL_MapOverlay::SetOverlayImage(const std::string& filename)
{
	m_pSprite = GL_TextureManager::get()->CreateTexture(filename, GL_REPEAT);
}

GLvoid GL_MapOverlay::SetOverlayMap(const std::string& filename)
{
	m_pMap = GL_TextureManager::get()->CreateTexture(filename, GL_CLAMP_TO_EDGE);
}

GLvoid GL_MapOverlay::PrepareShader(GL_Program * program)
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

GLuint GL_MapOverlay::GetID()
{
	return m_pSprite->m_ID;
}