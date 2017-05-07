
#include "ShaderManagerGL.h"

ShaderManagerGL * ShaderManagerGL::manager = nullptr;

ShaderManagerGL::ShaderManagerGL()
{
    shaders.reserve(10);
}

ShaderManagerGL::~ShaderManagerGL()
{
    auto begin = shaders.cbegin();
    auto end = shaders.cend();

    for (auto i = shaders.begin(); i != shaders.cend(); i++)
    {
        SAFE_RELEASE(*i);
    }

    shaders.clear();
}

ProgramGL* ShaderManagerGL::getShader(const std::string& vs, const std::string& fs)
{
    for (auto i = 0; i < shaders.size(); i++)
    {
        if (shaders[i]->getVertexShader() == vs && shaders[i]->getFragmentShader() == fs)
        {
            return shaders[i];
        }
    }

    auto program = new ProgramGL();
    program->create();
    program->load(VERTEX_SHADER, vs);
    program->load(FRAG_SHADER, fs);
    program->outputLog(VERTEX_SHADER);
    program->outputLog(FRAG_SHADER);
    program->link();

    shaders.push_back(program);
    return shaders.back();
}

ShaderManagerGL * ShaderManagerGL::get()
{
    if (manager == nullptr)
    {
        manager = new ShaderManagerGL();
    }

    return manager;
}