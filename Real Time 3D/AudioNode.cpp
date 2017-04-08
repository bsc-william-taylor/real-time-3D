
#include "AudioNode.h"

AudioNode::AudioNode()
{
}

AudioNode::~AudioNode()
{
	SAFE_RELEASE(m_pMatrix);
}

GLvoid AudioNode::Initialise(vec3 p, vec3 s)
{	
	m_pShader = GL_Shader_Manager::get()->GetShader("cube.vert", "cube.frag");

	m_pSprite = new GL_Texture();
	m_pSprite->setTexture("data/img/audio.png", GL_CLAMP_TO_EDGE);
	m_pSprite->Prepare();

	m_pMatrix = new GL_Matrix();
	m_pMatrix->LoadIdenditity();
	m_pMatrix->Perspective(70.0f, vec2(16, 9), vec2(0.1, 10000));

	#pragma region Texture Positions
	GLfloat texpos[] = {
		0.0, 1.0,	1.0, 1.0, 
		1.0, 0.0,	1.0, 0.0, 
		0.0, 0.0,	0.0, 1.0, 
		0.0, 1.0,	1.0, 1.0, 
		1.0, 0.0,	1.0, 0.0, 
		0.0, 0.0,	0.0, 1.0,
		0.0, 0.0,	0.0, 0.0,
		0.0, 0.0,	0.0, 0.0,
		0.0, 0.0,	0.0, 0.0,
		0.0, 0.0,	0.0, 0.0,
		0.0, 0.0,	0.0, 0.0,
		0.0, 0.0,	0.0, 0.0,
		0.0, 0.0,	0.0, 0.0,
		0.0, 0.0,	0.0, 0.0,
		0.0, 0.0,	0.0, 0.0,
	};
	#pragma endregion
	#pragma region Position
	vec3 positions[] = 
	{
		// Back face
		vec3(p.x, s.y, s.z), vec3(s.x, s.y, s.z), vec3(s.x, p.y, s.z), 
		vec3(s.x, p.y, s.z), vec3(p.x, p.y, s.z), vec3(p.x, s.y, s.z),
		// Font face
		vec3(s.x, s.y, p.z), vec3(p.x, s.y, p.z), vec3(p.x, p.y, p.z), 
		vec3(p.x, p.y, p.z), vec3(s.x, p.y, p.z), vec3(s.x, s.y, p.z),
		
		// Left face
		vec3(p.x, s.y, p.z), vec3(p.x, s.y, s.z), vec3(p.x, p.y, s.z), 
		vec3(p.x, p.y, s.z), vec3(p.x, p.y, p.z), vec3(p.x, s.y, p.z),
		
		// Right face
		vec3(s.x, s.y, s.z), vec3(s.x, s.y, p.z), vec3(s.x, p.y, p.z), 
		vec3(s.x, p.y, p.z), vec3(s.x, p.y, s.z), vec3(s.x, s.y, s.z),

		// top 
		vec3(p.x, s.y, p.z), vec3(s.z, s.y, p.z), vec3(s.x, s.y, s.z), 
		vec3(s.x, s.y, s.z), vec3(p.x, s.y, s.y), vec3(p.x, s.y, p.z),

		// bottem
		vec3(p.x, p.y, s.z), vec3(s.x, p.y, s.z), vec3(s.x, p.y, p.z), 
		vec3(s.x, p.y, p.z), vec3(p.x, p.y, p.z), vec3(p.x, p.y, s.z),
	};
	#pragma endregion

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * 36, &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &VTBO);
	glBindBuffer(GL_ARRAY_BUFFER, VTBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * 12, &texpos, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}

GLvoid AudioNode::Render()
{
	m_pShader->Use();
	m_pShader->setMatrix("Projection", m_pMatrix->getProjection());
	m_pShader->setMatrix("Model", m_pMatrix->getModel());
	m_pShader->setMatrix("View", m_pMatrix->getView());

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, m_pSprite->getID());
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	m_pShader->Release();
}