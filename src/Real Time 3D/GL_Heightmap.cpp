
#include "GL_Shader_Manager.h"
#include "GL_Heightmap.h"

GL_Heightmap::GL_Heightmap()
	: m_Filename(""), 
	  m_Scale(50),
	   m_Matrix (new GL_Matrix())
{
	m_Matrix->Perspective(70, vec2(16, 9), vec2(0.1, 1000));
	m_pPositions.reserve(2000);

	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	glGenBuffers(1, &PositionBuffer);
	glGenBuffers(1, &OverlayBuffer);
	glGenBuffers(1, &UvBuffer);
	glGenBuffers(1, &NormalBuffer);
	
	glBindVertexArray(0);
}

GL_Heightmap::~GL_Heightmap()
{
	
}

GLfloat GL_Heightmap::getY(GLuint x, GLuint z)
{
	GLfloat y = 0.0f;

	if(x < m_HeightMap->Colour.size() && z < m_HeightMap->Colour[x].size()) 
	{
		RGBQUAD Colour = m_HeightMap->Colour[x][z];
	
		y += ((GLfloat)Colour.rgbReserved) / 255.0f;
		y += ((GLfloat)Colour.rgbGreen) / 255.0f;
		y += ((GLfloat)Colour.rgbBlue) / 255.0f;
		y += ((GLfloat)Colour.rgbRed) / 255.0f;
	}

	return(y);
}

GLvoid GL_Heightmap::setScale(GLuint scale)
{
	m_Scale = scale;
}

GLvoid GL_Heightmap::Prepare()
{
	m_HeightMap = GL_Textures::get()->CreateTexture(m_Filename, GL_CLAMP_TO_EDGE);
	m_Texture = GL_Textures::get()->CreateTexture(m_TexFiles, GL_REPEAT);
	
	GLfloat y2 = 1.0f / (float)m_HeightMap->Height;
	GLfloat x2 = 1.0f / (float)m_HeightMap->Width;
	GLfloat TextureX = 0.0f;
	GLfloat TextureY = 0.0f;
	
	GLint x = -m_HeightMap->Width/2;

	m_pPositions.reserve(m_HeightMap->Width * m_HeightMap->Width * 6);
	m_pOverlay.reserve(m_HeightMap->Width * m_HeightMap->Width * 6);
	m_pNormals.reserve(m_HeightMap->Width * m_HeightMap->Width * 6);
	m_pUv.reserve(m_HeightMap->Width * m_HeightMap->Width * 6);

	for(GLint c = 0; c < m_HeightMap->Width; c++, x++)
	{
		GLint z = -m_HeightMap->Width/2;
		for(GLint i = 0; i < m_HeightMap->Height; i++, z++)
		{
			vec3 v1 = vec3(x, getY(c, i), z);
			vec3 v2 = vec3(x, getY(c, i+1), z+1);
			vec3 v3 = vec3(x+1, getY(c+1, i+1), z+1);
		
			m_pPositions.push_back(v1);
			m_pPositions.push_back(v2);
			m_pPositions.push_back(v3);

			m_pOverlay.push_back(vec3(x, z, 0));
			m_pOverlay.push_back(vec3(x, z+1, 0));
			m_pOverlay.push_back(vec3(x+1, z+1, 0));

			m_pUv.push_back(vec3(TextureX , TextureY, 0));
			m_pUv.push_back(vec3(TextureX, TextureY + y2, 0));
			m_pUv.push_back(vec3(TextureX + x2, TextureY + y2, 0));
			
			m_pNormals.push_back(getNormal(v1, v3, v2));
			m_pNormals.push_back(getNormal(v2, v1, v3));
			m_pNormals.push_back(getNormal(v3, v2, v1));
			
			v1 = vec3(x, getY(c, i), z);
			v2 = vec3(x+1, getY(c+1, i), z);
			v3 = vec3(x+1, getY(c+1, i+1), z+1);

			m_pPositions.push_back(v1);
			m_pPositions.push_back(v2);
			m_pPositions.push_back(v3);

			m_pOverlay.push_back(vec3(x, z, 0));
			m_pOverlay.push_back(vec3(x+1, z, 0));			
			m_pOverlay.push_back(vec3(x+1, z+1, 0));

			m_pUv.push_back(vec3(TextureX, TextureY, 0));
			m_pUv.push_back(vec3(TextureX + x2, TextureY, 0));
			m_pUv.push_back(vec3(TextureX + x2, TextureY + y2, 0));

			m_pNormals.push_back(getNormal(v1, v2, v3));
			m_pNormals.push_back(getNormal(v2, v3, v1));
			m_pNormals.push_back(getNormal(v3, v1, v2));

			TextureY += y2;
		}

		TextureY = 0.0f;
		TextureX += x2;
	}

	for(unsigned int i = 0; i < m_pNormals.size() - 24; i++)
	{
		vec3 average = vec3(0.0, 0.0, 0.0);
		for(unsigned int b = i; b < i + 24; b++)
		{
			average += m_pNormals[b];
		}

		average /= 24;

		for(unsigned int b = i; b < i + 24; b++)
		{
			m_pNormals[b] = average;
		}
	}

	glBindVertexArray(VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, PositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_pPositions.size(), &m_pPositions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, UvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_pUv.size(), &m_pUv[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, OverlayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_pOverlay.size(), &m_pOverlay[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_pNormals.size(), &m_pNormals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glLineWidth(0.1f);

	GLchar * vs = "data/shaders/heightmap.vert";
	GLchar * fs = "data/shaders/heightmap.frag";
	
	m_pShader = GL_Shader_Manager::get()->GetShader(vs, fs);
}

GLfloat GL_Heightmap::getMapY(vec3 camera)
{
	m_HeightMap->Height;
	m_HeightMap->Width;
	return 0;
}

GLvoid GL_Heightmap::Update()
{
	m_Matrix->LoadIdenditity();
	m_Matrix->Translate(vec3(0, -59.5, 0));
	m_Matrix->Scale(vec3(24, 1, 24));
}

vec3 GL_Heightmap::getNormal(vec3 v1, vec3 v2, vec3 v3)
{
	vec3 Normal = glm::cross(v2 - v1, v3 - v1);
	Normal = glm::normalize(Normal);
	return(Normal);
}

GLvoid GL_Heightmap::setMapTexture(std::string m_file)
{
	m_TexFiles = m_file;
}

GLvoid GL_Heightmap::PushOverlay(GL_MapOverlay * overlay)
{
	m_Overlays.push_back(overlay);
}

GLvoid GL_Heightmap::Draw()
{
	m_pShader->Use();
	glBindVertexArray(VertexArrayObject);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture->m_ID);
	
	GLint Sampler = glGetUniformLocation(m_pShader->getID(), "ID");
	glUniform1i(Sampler, 0);

	for(GLuint i = 0; i < m_Overlays.size(); i++)
	{
		m_Overlays[i]->PrepareShader(m_pShader);
	}

	m_pShader->setMatrix("Projection", m_Matrix->getProjection());
	m_pShader->setMatrix("Model", m_Matrix->getModel());
	m_pShader->setMatrix("View", m_Matrix->getView());

	GLint loc = glGetUniformLocation(m_pShader->getID(), "Scale");
	glUniform1i(loc, m_Scale);
	glDrawArrays(GL_TRIANGLES, 0, 6 * (m_HeightMap->Height * m_HeightMap->Width));

	m_pShader->Release();
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLvoid GL_Heightmap::setHeightMap(std::string filename)
{
	m_Filename = filename;
}