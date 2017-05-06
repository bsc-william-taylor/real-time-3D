
/* -------------------------------------------------
  
 @Filename  : GL_Shader_Manager.cpp
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: Class implementation

 ------------------------------------------------- */

#include "ShaderManagerGL.h"

ShaderManagerGL * ShaderManagerGL::m_pInstance = NULL;

// Constructor & Deconstructor
ShaderManagerGL::ShaderManagerGL()
{
	m_Programs.reserve(10);
}

ShaderManagerGL::~ShaderManagerGL()
{
	auto begin = m_Programs.cbegin();
	auto end = m_Programs.cend();

	for(auto i = m_Programs.begin(); i != m_Programs.cend();i++)
	{
		SAFE_RELEASE(*i);
	}
	
	m_Programs.clear();
}

// Member Functions
GL_Program * ShaderManagerGL::GetShader(const std::string& vs, const std::string& fs)
{
	for(unsigned int i = 0; i < m_Programs.size(); i++)
	{
		if(m_Programs[i]->getVS() == vs && m_Programs[i]->getFS() == fs)
		{
			return m_Programs[i];
		}
	}

	GL_Program * Program = new GL_Program();
	
	Program->Create();

	Program->Load(Shader::VERTEX_SHADER, vs);
	Program->Load(Shader::FRAG_SHADER, fs);
	Program->OutputLog(Shader::VERTEX_SHADER);
	Program->OutputLog(Shader::FRAG_SHADER);
	
	Program->Link();

	m_Programs.push_back(Program);
	return m_Programs[m_Programs.size() - 1];
}

// Set & Get Functions
ShaderManagerGL * ShaderManagerGL::get()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new ShaderManagerGL();
	}

	return m_pInstance;
}