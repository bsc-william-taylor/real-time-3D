
#pragma once

#include "ProgramGL.h" 

class ShaderManagerGL
{
    static ShaderManagerGL* manager;
    vector<ProgramGL*> shaders;
public:
    ShaderManagerGL();
    ~ShaderManagerGL();

    ProgramGL* getShader(const std::string&, const std::string&);
    GLvoid freeShaders();

    static ShaderManagerGL * get();
};