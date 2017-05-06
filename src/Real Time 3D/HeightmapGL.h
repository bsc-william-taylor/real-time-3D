
#pragma once

#include "TextureManagerGL.h"
#include "MapOverlayGL.h"
#include "TextureGL.h"

class HeightmapGL
{
private:

	GL_Program * m_pShader;		
	GL_Matrix * m_Matrix;
	GL_Sprite * m_HeightMap;
	GL_Sprite * m_Texture;

	vector<MapOverlayGL *> m_Overlays;
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

	HeightmapGL();
	~HeightmapGL();

	GLvoid PushOverlay(MapOverlayGL *);
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