
#include "PostProcessorGL.h"

PostProcessorGL::PostProcessorGL()
	: m_pMatrix(new GL_Matrix())
{
	colour = vec4(1.0, 1.0, 1.0, 1.0);
	Passes = 1;
}

PostProcessorGL::~PostProcessorGL()
{
	SAFE_RELEASE(m_pMatrix);
}

GLvoid PostProcessorGL::Enable()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

GLvoid PostProcessorGL::execute()
{
	m_pProgram->Use();
	m_pProgram->setMatrix("Projection", m_pMatrix->getProjection());
	m_pProgram->setMatrix("Model", m_pMatrix->getModel());
	m_pProgram->setMatrix("View", m_pMatrix->getView());

	glDisable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glUniform4fv(m_pProgram->getUniform("overlay"), 1, glm::value_ptr(colour));
	glBindVertexArray(VertexArrayObject);
	glBindTexture(GL_TEXTURE_2D, TextureBuffer);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glViewport(0, 0, 1280, 720);
	glBindVertexArray(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);

	m_pProgram->Release();
}

GLvoid PostProcessorGL::Initialise(GLuint w, GLuint h)
{
	VertexArrayObject = NULL;

	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	GLfloat Positions[] = 
	{
	    0, 0, 0, 0,
	    0, h, 0, 1,
	    w, 0, 1, 0,
		w, h, 1, 1
	};

	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, Positions, GL_STATIC_DRAW);
	  
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	GLchar * vs = "data/shaders/postprocessor.vert";
	GLchar * fs = "data/shaders/postprocessor.frag";
	 
	m_pProgram = ShaderManagerGL::get()->GetShader(vs, fs);

	m_pMatrix->Ortho(vec2(0, w), vec2(0, h));

	glGenTextures(1, &TextureBuffer);
	glBindTexture(GL_TEXTURE_2D, TextureBuffer);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	FrameBuffer = NULL;

	glGenFramebuffers(1, &FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TextureBuffer, 0);

	DepthBuffer = NULL;

	glGenRenderbuffers(1, &DepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, DepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
	
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthBuffer);

	glBindVertexArray(0);
}

GLvoid PostProcessorGL::setColourChannels(vec4 vec)
{
	colour = vec;
}