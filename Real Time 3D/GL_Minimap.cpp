
#include "GL_Minimap.h"

GL_Minimap::GL_Minimap()
	: m_pMatrix(new GL_Matrix())
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(0);
}

GL_Minimap::~GL_Minimap()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

GLvoid GL_Minimap::Initialise(ICamera * camera)
{
	GLchar * vs = "data/shaders/postprocessor.vert";
	GLchar * fs = "data/shaders/postprocessor.frag";
	 
	GLfloat position[] = {
		 10,  650, 0,  0,
		 10,  850, 0,  1,
		 250, 650, 1,  0,
		 250, 850, 1,  1
	};

	m_pShader = GL_Shader_Manager::get()->GetShader(vs, fs);
	m_pMatrix->Ortho(vec2(0, 1600), vec2(0, 900));
	m_pCamera = camera;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, &position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glGenTextures(1, &ColourBuffer);
	glBindTexture(GL_TEXTURE_2D, ColourBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 240, 200, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColourBuffer, 0);

	glGenRenderbuffers(1, &DepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, DepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 240, 200);
	
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLvoid GL_Minimap::RenderToBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 240, 200);

	m_PreviousPosition = m_pCamera->getTranslate();
	m_PreviousRotation = m_pCamera->getRotation();
	m_PreviousPitch = m_pCamera->getPitch();

	m_pCamera->setPosition(vec3(m_PreviousPosition.x, -100, m_PreviousPosition.z));
	m_pCamera->setRotation(0);
	m_pCamera->setPitch(90);
}

GLvoid GL_Minimap::RenderToScreen()
{
	m_pShader->Use();
	m_pShader->setMatrix("Projection", m_pMatrix->getProjection());
	m_pShader->setMatrix("Model", m_pMatrix->getModel());
	m_pShader->setMatrix("View", m_pMatrix->getView());

	glViewport(0, 0, 1600, 900);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);	
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, ColourBuffer);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	m_pShader->Release();

	m_pCamera->setPosition(m_PreviousPosition);
	m_pCamera->setRotation(m_PreviousRotation);
	m_pCamera->setPitch(m_PreviousPitch);
}