
#pragma once

#include "GL_Texture.h"
#include "Surface.h"
#include "IModel.h"

class StaticModel : public IModel
{
private:

	Assimp::Importer m_Importer;

	vector<GL_Texture *> m_Textures;
	Surface * m_BoundingBox;

	GLint * m_MatIndices,* m_MeshStart, * m_MeshSizes;
	GLuint VAO,	VBO, Size, MeshNumber;

	GLfloat m_Rotation;
	GLint m_NumMaterials;

	vec3 m_RotateNormal, m_Translate, m_Scale;

	vector<aiVector3D> m_Data;

	GL_Program * m_pShader;		
	GL_Matrix * m_Matrix;    
	
public:

	StaticModel();
	~StaticModel();

	bool isDynamic() { return false; }


	GLvoid Load(const std::string&, const std::string&, bool);
	GLvoid Prepare();
	GLvoid Update();

	GLvoid Forward();
	GLvoid Translate(vec3);
	GLvoid SetScale(vec3);
	GLvoid SetScale(GLfloat);
	GLvoid Rotate(GLfloat, vec3);

	GLuint getMaterialIndex(GLuint);
	GLuint getMeshStart(GLuint);
	GLuint getTextureID(GLuint);
	GLuint getMeshEnd(GLuint);
	GLuint getMeshNumber();

	GL_Program * getProgram() { return m_pShader; }
	GL_Matrix * getMatrix() { return m_Matrix; }
	GLuint getVAO(){ return VAO; }

private:

	std::string GetDirectoryPath(std::string);
};