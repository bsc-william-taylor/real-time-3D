
#include "StaticModel.h"
#include "ShaderManagerGL.h"
#include "SurfaceBuilder.h"
#include "SurfaceManager.h"

StaticModel::StaticModel()
{
    rotateNormal = vec3(1.0, 0.0, 0.0);
    rotation = 0.0f;
    scale = vec3(1.0, 1.0, 1.0);
    size = 0;

    textures.reserve(12);
}

StaticModel::~StaticModel()
{
    delete[] matrixIndices;
    delete[] meshStart;
    delete[] meshSizes;

    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
}

std::string StaticModel::getDirectoryPath(std::string filename)
{
    std::string directory = filename;

    for (int i = filename.size() - 1; i >= 0; i--)
    {
        if (filename[i] == '\\' || filename[i] == '/')
        {
            directory = filename.substr(i + 1, filename.size());
            break;
        }
    }

    return directory;
}

GLvoid StaticModel::load(const std::string& sFilePath, const std::string& sTexture, bool bound)
{
    const aiScene * scene = assimp.ReadFile(sFilePath, aiProcessPreset_TargetRealtime_Fast);

    if (!scene)
    {
        MessageBox(NULL, "Couldn't load model ", "Error Importing Asset", MB_OK);
    }
    else
    {
        GLint vertexSize = sizeof(aiVector3D) * 2 + sizeof(aiVector2D);
        GLint numberFaces = NULL;
        GLint sizeBefore = NULL;
        GLint meshCount = NULL;
        GLint vertices = NULL;

        matrixIndices = new GLint[scene->mNumMeshes];
        meshStart = new GLint[scene->mNumMeshes];
        meshSizes = new GLint[scene->mNumMeshes];
        data.reserve(scene->mNumMeshes * 12);

        SurfaceBuilder * builder = NULL;
        aiMesh * mesh = NULL;

        if (bound)
        {
            builder = new SurfaceBuilder();
        }

        for (auto i = 0; i < scene->mNumMeshes; i++)
        {
            mesh = scene->mMeshes[i];
            numberFaces = mesh->mNumFaces;
            sizeBefore = size;
            matrixIndices[i] = mesh->mMaterialIndex;
            meshStart[i] = sizeBefore / vertexSize;

            for (GLint j = 0; j < numberFaces; j++ && meshCount++)
            {
                const aiFace& face = mesh->mFaces[j];

                for (GLint k = 0; k < 3; k++)
                {
                    aiVector3D normals;

                    if (mesh->HasNormals())
                    {
                        normals = mesh->mNormals[face.mIndices[k]];
                    }
                    else
                    {
                        normals = aiVector3D(1, 1, 1);
                    }

                    if (bound)
                    {
                        builder->pushPoint(mesh->mVertices[face.mIndices[k]]);
                    }

                    data.push_back(mesh->mVertices[face.mIndices[k]]);
                    data.push_back(mesh->mTextureCoords[0][face.mIndices[k]]);
                    data.push_back(normals);

                    size += vertexSize;
                }

                if (bound)
                {
                    builder->pushSurface(this->getMatrix());
                }
            }

            if (bound)
            {
                builder->endOfMesh(meshCount);
            }

            vertices += mesh->mNumVertices;
            meshSizes[i] = (size - sizeBefore) / vertexSize;
        }

        GLint* materialMap = new GLint[scene->mNumMaterials];

        for (GLuint i = 0; i < scene->mNumMaterials; i++)
        {
            const aiMaterial* Material = scene->mMaterials[i];
            materialMap[i] = NULL;
            aiString path;

            if (Material->GetTexture(aiTextureType_DIFFUSE, NULL, &path) == AI_SUCCESS)
            {
                std::string fullPath = sTexture + getDirectoryPath(path.data);

                GLint textureFound = -1;

                for (GLuint j = 0; j < textures.size(); j++)
                {
                    if (fullPath == textures[j]->getPath())
                    {
                        textureFound = j;
                        break;
                    }
                }

                if (textureFound != -1)
                {
                    materialMap[i] = textureFound;
                }
                else
                {
                    auto texture = new TextureGL();
                    texture->setTexture(fullPath, GL_REPEAT);
                    texture->prepare();

                    materialMap[i] = textures.size();
                    textures.push_back(texture);
                }
            }
        }

        for (GLuint i = 0; i < scene->mNumMeshes; i++)
        {
            GLint iOldIndex = matrixIndices[i];
            matrixIndices[i] = materialMap[iOldIndex];
        }

        if (bound)
        {
            boundingBox = builder->release();
        }
        else
        {
            boundingBox = NULL;
        }

        meshNumber = scene->mNumMeshes;
        assimp.FreeScene();

        if (bound) delete builder;
        delete[] materialMap;
    }


}

GLvoid StaticModel::prepare()
{
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * data.size(), &data[0], GL_STATIC_DRAW);

    data.clear();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    size_t vecSize = sizeof(aiVector3D);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vecSize * 3, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vecSize * 3, (void*)vecSize);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vecSize * 3, (void*)(vecSize * 2));

    GLchar * vs = "data/shaders/model.vert";
    GLchar * fs = "data/shaders/model.frag";
    shader = ShaderManagerGL::get()->getShader(vs, fs);
    glBindVertexArray(0);
}

GLvoid StaticModel::setTranslate(vec3 v)
{
    translate = v;
}

GLvoid StaticModel::setScale(vec3 v)
{
    scale = v;
}

GLvoid StaticModel::onUpdate()
{
    matrix.loadIdenditity();
    matrix.scale(scale);
    matrix.translate(this->translate);
    matrix.rotate(rotation, rotateNormal);

    if (boundingBox != nullptr)
    {
        boundingBox->onUpdate(&matrix);
    }
}

GLvoid StaticModel::setRotate(GLfloat f, vec3 vec)
{
    rotateNormal = vec;
    rotation = f;
}

GLvoid StaticModel::setScale(GLfloat value)
{
    scale = vec3(value, value, value);
}

GLuint StaticModel::getTextureID(GLuint i)
{
    if (textures.size() > i)
    {
        return textures[i]->getProgramID();
    }
    else
    {
        return 0;
    }
}

GLuint StaticModel::getMaterialIndex(GLuint index)
{
    return matrixIndices[index];
}

GLuint StaticModel::getMeshStart(GLuint index)
{
    return meshStart[index];
}

GLuint StaticModel::getMeshEnd(GLuint index)
{
    return meshSizes[index];
}

GLuint StaticModel::getMeshNumber()
{
    return(meshNumber);
}

ProgramGL * StaticModel::getProgram()
{
    return shader;
}

MatrixGL * StaticModel::getMatrix()
{
    return &matrix;
}

GLuint StaticModel::getVAO()
{
    return vertexArray;
}

bool StaticModel::isDynamic()
{
    return false;
}