
#pragma once

#include "GL_Texture_Manager.h"
#include "GL_MapOverlay.h"
#include "GL_Texture.h"

class GL_Heightmap
{
private:

	GL_Program * m_pShader;		
	GL_Matrix * m_Matrix;
	GL_Sprite * m_HeightMap;
	GL_Sprite * m_Texture;

	vector<GL_MapOverlay *> m_Overlays;
	vector<vec3> m_pPositions;
	vector<vec3> m_pOverlay;
	vector<vec3> m_pNormals;
	vector<vec3> m_pUv;

	GLuint VertexArrayObject;
	GLuint PositionBuffer;
	GLuint OverlayBuffer;
	GLuint NormalBuffer;
	GLuint UvBuffer;

	std::string m_TexFiles;
	std::string m_Filename;
	unsigned int m_Scale;

public:

	GL_Heightmap();
	~GL_Heightmap();

	GLvoid PushOverlay(GL_MapOverlay *);
	GLvoid Prepare();
	GLvoid update();
	GLvoid Draw();

	GLvoid setMapTexture(std::string);
	GLvoid setHeightMap(std::string);
	GLvoid setScale(GLuint);

	GL_Program * getProgram() { return m_pShader; }
	GL_Matrix * getMatrix() { return m_Matrix; }
	GLfloat getMapY(vec3);

private:

	GLfloat getY(GLuint, GLuint);
	vec3 getNormal(vec3, vec3, vec3);
};