
#pragma once

#include "MajorInclude.h"

enum ShaderTypes
{
    VERTEX_SHADER,
    FRAG_SHADER,
};

class ProgramGL
{
    std::string filenames[2];
    GLuint shaders[2];
    GLuint program;
public:
    ProgramGL();
    ~ProgramGL();

    void load(ShaderTypes, const std::string&);
    void outputLog(ShaderTypes);
    void release();
    void create();
    void link();
    void use();

    GLvoid setMatrix(const std::string&, glm::mat4);
    GLvoid setTexture(GLuint);

    GLuint getAttribute(const std::string&);
    GLuint getUniform(const std::string&);
    GLuint getProgramID();

    std::string getVertexShader();
    std::string getFragmentShader();
    std::string readFile(const std::string&);
};