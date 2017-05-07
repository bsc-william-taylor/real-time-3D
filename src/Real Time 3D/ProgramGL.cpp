
#include "ProgramGL.h"

ProgramGL::ProgramGL()
{
    program = NULL;
    shaders[0] = 0;
    shaders[1] = 0;
}

ProgramGL::~ProgramGL()
{
}

void ProgramGL::outputLog(ShaderTypes types)
{
    GLint progress = 0;
    glGetShaderiv(shaders[types], GL_COMPILE_STATUS, &progress);

    if (progress == GL_FALSE)
    {
        std::cout << "\nErrors with " << (types ? "Fragment " : "Vertex ");
        std::cout << "Shader \n" << std::endl;

        GLint length = 0;
        glGetShaderiv(shaders[types], GL_INFO_LOG_LENGTH, &length);
        GLchar* log = new GLchar[length + 1];
        glGetShaderInfoLog(shaders[types], length, NULL, log);
        std::cerr << log << std::endl;
        delete[] log;
    }
}

std::string ProgramGL::readFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::string data = "";

    if (file.is_open())
    {
        while (!file.eof())
        {
            std::string line = "";
            getline(file, line);
            data.append(line + "\n");
        }

        std::cout << filename << " : Shader Loaded" << std::endl;
        file.close();
    }
    else
    {
        std::string str = filename;
        str += "Error opening this file";
        printf(str.c_str());
    }

    return(data);
}

GLvoid ProgramGL::setTexture(GLuint ID)
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

GLvoid ProgramGL::setMatrix(const std::string& name, mat4 m)
{
    GLuint matrix = getUniform(name);
    glUniformMatrix4fv(matrix, 1, false, glm::value_ptr(m));
}

void ProgramGL::create()
{
    program = glCreateProgram();
}

void ProgramGL::link()
{
    glAttachShader(program, shaders[0]);
    glAttachShader(program, shaders[1]);
    glLinkProgram(program);
}

void ProgramGL::load(ShaderTypes type, const std::string& source)
{
    filenames[type] = source;
    shaders[type] = glCreateShader(type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

    std::string shaderString = readFile(source);
    const char* charStr = shaderString.c_str();
    glShaderSource(shaders[type], 1, &charStr, NULL);
    glCompileShader(shaders[type]);
}

void ProgramGL::release()
{
    glUseProgram(0);
}

void ProgramGL::use()
{
    glUseProgram(program);
}

GLuint ProgramGL::getAttribute(const std::string& name)
{
    return glGetAttribLocation(this->program, name.c_str());
}

GLuint ProgramGL::getUniform(const std::string& name)
{
    return glGetUniformLocation(this->program, name.c_str());
}

std::string ProgramGL::getVertexShader()
{
    return filenames[VERTEX_SHADER];
}

std::string ProgramGL::getFragmentShader()
{
    return filenames[FRAG_SHADER];
}

GLuint ProgramGL::getProgramID()
{
    return program;
}