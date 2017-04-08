
#include "StaticModel.h"
#include "GL_Shader_Manager.h"
#include "SurfaceBuilder.h"
#include "SurfaceManager.h"

StaticModel::StaticModel()
{
	m_Matrix = new GL_Matrix();
	m_RotateNormal = vec3(1.0, 0.0, 0.0);
	m_Rotation = 0.0f;
	m_Scale = vec3(1.0, 1.0, 1.0);
	Size = 0;

	m_Textures.reserve(12);
}

StaticModel::~StaticModel()
{
	delete[] m_MatIndices;
	delete[] m_MeshStart;
	delete[] m_MeshSizes;
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

std::string StaticModel::GetDirectoryPath(std::string filename)
{
	// Get directory path
	std::string Directory = filename;

	for(int i = filename.size() - 1; i >= 0; i--)
	{
		if(filename[i] == '\\' || filename[i] == '/')
		{
			Directory = filename.substr(i+1, filename.size());
			break;
		}
	}
	
	return Directory;
}

GLvoid StaticModel::Load(const std::string& sFilePath, const std::string& sTexture,  bool bound)
{
	const aiScene * scene = m_Importer.ReadFile(sFilePath, aiProcessPreset_TargetRealtime_Fast);
	
	if(!scene)
	{
		MessageBox(NULL, "Couldn't load model ", "Error Importing Asset", MB_OK);
	}
	else
	{	
		GLint VertexSize	= sizeof(aiVector3D)*2+sizeof(aiVector2D);
		GLint NumberFaces	= NULL;
		GLint SizeBefore	= NULL;
		GLint MeshCount		= NULL;
		GLint Vertices		= NULL;

		m_MatIndices = new GLint[scene->mNumMeshes];
		m_MeshStart	= new GLint[scene->mNumMeshes];
		m_MeshSizes	= new GLint[scene->mNumMeshes];
		m_Data.reserve(scene->mNumMeshes * 12);

		SurfaceBuilder * Builder = NULL;
		aiMesh * Mesh = NULL;
		if(bound) {
			Builder = new SurfaceBuilder();
		}

		for(unsigned int i = 0; i < scene->mNumMeshes; i++)
		{		
			Mesh = scene->mMeshes[i];
			NumberFaces = Mesh->mNumFaces;
			SizeBefore = Size;
			// Rest of loading
			m_MatIndices[i] = Mesh->mMaterialIndex;
			m_MeshStart[i] = SizeBefore/VertexSize;
		
			for(GLint j = 0; j < NumberFaces; j++ && MeshCount++)
			{
				const aiFace& face = Mesh->mFaces[j];
			
				for(GLint k = 0; k < 3; k++)
				{
					aiVector3D Normals;
				
					if(Mesh->HasNormals()) {
						Normals = Mesh->mNormals[face.mIndices[k]];
					}
					else {
						Normals = aiVector3D(1, 1, 1);
					}

					if(bound) Builder->PushPoint(Mesh->mVertices[face.mIndices[k]]);

					m_Data.push_back(Mesh->mVertices[face.mIndices[k]]);
					m_Data.push_back(Mesh->mTextureCoords[0][face.mIndices[k]]);
					m_Data.push_back(Normals);
				
					Size += VertexSize;
				}

				if(bound) Builder->PushSurface(this->getMatrix());
			}

			if(bound) Builder->EndOfMesh(MeshCount);
			Vertices += Mesh->mNumVertices;
			m_MeshSizes[i] = (Size-SizeBefore)/VertexSize;
		}

		GLint * MaterialMap = new GLint[scene->mNumMaterials];	
	
		for(GLuint i = 0; i < scene->mNumMaterials; i++)
		{
			const aiMaterial * Material = scene->mMaterials[i];
			MaterialMap[i] = NULL;
			aiString Path;
	
			if(Material->GetTexture(aiTextureType_DIFFUSE, NULL, &Path) == AI_SUCCESS)
			{
				std::string FullPath = sTexture + GetDirectoryPath(Path.data);
			
				GLint iTexFound = -1;

				for(GLuint j = 0; j < m_Textures.size(); j++)
				{
					if(FullPath == m_Textures[j]->getPath())
					{
						iTexFound = j;
						break;
					}
				}

				if(iTexFound != -1)
				{
					MaterialMap[i] = iTexFound;
				}
				else
				{
					GL_Texture * Texture = new GL_Texture();
					Texture->setTexture(FullPath, GL_REPEAT);
					Texture->Prepare();
					//std::cout << FullPath.c_str() << std::endl;
					MaterialMap[i] = m_Textures.size();
					m_Textures.push_back(Texture);
				}
			}
		}

		for(GLuint i = 0; i < scene->mNumMeshes; i++)
		{
			GLint iOldIndex = m_MatIndices[i];
			m_MatIndices[i] = MaterialMap[iOldIndex];
		}

		if(bound) m_BoundingBox = Builder->Release();
		else m_BoundingBox = NULL;

		MeshNumber = scene->mNumMeshes;
		m_Importer.FreeScene();
	
		if(bound) delete Builder;
		delete[] MaterialMap;
	}


}

GLvoid StaticModel::Prepare()
{
	size_t size =  sizeof(aiVector3D);
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * m_Data.size(), &m_Data[0], GL_STATIC_DRAW);
	
	m_Data.clear();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1); 
	glEnableVertexAttribArray(2); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*size+size, 0); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2*size+size, (void*)size); 
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2*size+size, (void*)(size+size));

	GLchar * vs = "data/shaders/model.vert";
	GLchar * fs = "data/shaders/model.frag";

	m_pShader = GL_Shader_Manager::get()->GetShader(vs, fs);

	glBindVertexArray(0);
}

GLvoid StaticModel::Translate(vec3 v)
{
	m_Translate = v;
}

GLvoid StaticModel::SetScale(vec3 v)
{
	m_Scale = v;
}

GLvoid StaticModel::Update()
{
	m_Matrix->LoadIdenditity();
	m_Matrix->Scale(m_Scale);
	m_Matrix->Translate(m_Translate);
	m_Matrix->Rotate(m_Rotation, m_RotateNormal);
	
	if(m_BoundingBox != NULL)
	{
		m_BoundingBox->Update(m_Matrix);
	}
}

GLvoid StaticModel::Forward()
{
	m_Translate += vec3(0.0, 0.0, 1.0f);
}

GLvoid StaticModel::Rotate(GLfloat f, vec3 vec)
{
	m_RotateNormal = vec;
	m_Rotation = f;
}

GLvoid StaticModel::SetScale(GLfloat scale)
{
	this->m_Scale = vec3(scale, scale, scale);
}

GLuint StaticModel::getTextureID(GLuint i)
{
	if(m_Textures.size() > i)
	{
		return m_Textures[i]->getID();
	} 
	else
	{
		return -1;
	}
}

GLuint StaticModel::getMaterialIndex(GLuint index)
{
	return m_MatIndices[index];
}

GLuint StaticModel::getMeshStart(GLuint index)
{
	return m_MeshStart[index];
}

GLuint StaticModel::getMeshEnd(GLuint index)
{
	return m_MeshSizes[index];
}

GLuint StaticModel::getMeshNumber()
{
	return(MeshNumber);
}