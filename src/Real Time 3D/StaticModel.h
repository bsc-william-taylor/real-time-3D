
#pragma once

#include "TextureGL.h"
#include "Surface.h"
#include "Model.h"

class StaticModel : public Model
{
    Assimp::Importer assimp;

    vector<TextureGL*> textures;
    Surface* boundingBox;

    GLint* matrixIndices;
    GLint* meshStart;
    GLint* meshSizes;

    GLuint materialCount;
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint meshNumber;
    GLuint size;

    GLfloat rotation;

    vector<aiVector3D> data;
    vec3 rotateNormal;
    vec3 translate;
    vec3 scale;

    ProgramGL* shader;
    MatrixGL matrix;
public:
    StaticModel();
    ~StaticModel();

    bool isDynamic();

    GLvoid prepare();
    GLvoid onUpdate();
    GLvoid load(const std::string&, const std::string&, bool);
    GLvoid setTranslate(vec3);
    GLvoid setScale(vec3);
    GLvoid setScale(GLfloat);
    GLvoid setRotate(GLfloat, vec3);

    GLuint getMaterialIndex(GLuint);
    GLuint getMeshStart(GLuint);
    GLuint getTextureID(GLuint);
    GLuint getMeshEnd(GLuint);
    GLuint getMeshNumber();
    GLuint getVAO();

    ProgramGL* getProgram();
    MatrixGL* getMatrix();

    std::string getDirectoryPath(std::string);
};