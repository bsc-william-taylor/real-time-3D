
/* -------------------------------------------------
  
 @Filename  : GL_Program.h
 @purpose	: Main Definition
 @author	: William Taylor
 @date		: 04/02/2014

 ------------------------------------------------- */

#include "ProgramGL.h"

// Constructor & Deconstructor
GL_Program::GL_Program() 
{
	VertexFilename = "";
	FragFilename = "";
	Program = NULL;
	Shaders[0] = 0;
	Shaders[1] = 0;
}

GL_Program::~GL_Program() 
{
}

// Member Functions
void GL_Program::OutputLog(Types types) 
{
	GLint progress = NULL;
	
	// Check to see if it compiled without errors
	glGetShaderiv(Shaders[types], GL_COMPILE_STATUS, &progress);

	// if so.
	if(progress == GL_FALSE) 
	{
		// Write errors to the console
		std::cout << "\nErrors with ";
		types ? std::cout << "Fragment " : std::cout << "Vertex ";
		std::cout << "Shader \n" << std::endl;
		
		GLint Length = 0;
		glGetShaderiv(Shaders[types], GL_INFO_LOG_LENGTH, &Length);

		GLchar * Log = new GLchar[Length + 1];
		glGetShaderInfoLog(Shaders[types], Length, NULL, Log); 

		// Delete log for clean up
		std::cerr << Log << std::endl;
		delete[] Log;
		Log = NULL;
	}
}

std::string GL_Program::ReadFile(const std::string& Filename) 
{
	// Read shader file into a string
	std::ifstream File(Filename);
    std::string Data = "";

	// I dont think i really need to explain this.
    if(File.is_open()) 
	{
		std::string line = "";

        while(!File.eof()) 
		{
			getline(File, line);
			Data.append(line + "\n");
		}

		std::cout << Filename << " : Shader Loaded" << std::endl;
		File.close();
    }
	else
	{
		std::string str = Filename;
		str += "Error opening this file";
		printf(str.c_str());
	}

    return(Data);
}

GLvoid GL_Program::setTexture(GLuint ID)
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

GLvoid GL_Program::setMatrix(const std::string& name, mat4 m)
{
	// get Uniform & set the matrix
	GLuint matrix = getUniform(name);
	glUniformMatrix4fv(matrix, 1, false, glm::value_ptr(m));
}

void GL_Program::Create()
{
	// Create ID for the program
	Program = glCreateProgram();
}

void GL_Program::Link()
{
	// Attach and link shaders
	glAttachShader(Program, Shaders[0]);
	glAttachShader(Program, Shaders[1]);
	glLinkProgram(Program);
}

void GL_Program::Load(Types type, const std::string& Source) 
{	
	GLuint i = 0;

	if(type == VERTEX_SHADER) 
	{
		Shaders[0] = glCreateShader(GL_VERTEX_SHADER);
		VertexFilename = Source;
	}
	else 
	{
		Shaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
		FragFilename = Source;
		i = 1;
	}

	std::string ShaderString = ReadFile(Source);

	const char * ShaderChar = ShaderString.c_str();

	glShaderSource(Shaders[i], 1, &ShaderChar, NULL);
    glCompileShader(Shaders[i]);
}

void GL_Program::Release() 
{
	glUseProgram(NULL);
}

void GL_Program::Use() 
{
	glUseProgram(Program);
}

GLuint GL_Program::getAttribute(const std::string& name)
{
	return glGetAttribLocation(this->Program, name.c_str());
}

GLuint GL_Program::getUniform(const std::string& name)
{
	return glGetUniformLocation(this->Program, name.c_str());
}

