
/* -------------------------------------------------
  
 @Filename  : GL_Text.cpp
 @author	: William Taylor
 @date		: 14/02/2014
 @purpose	: Class implementation

 ------------------------------------------------- */

#include "GL_Text.h"

// Constructor & Deconstructor
GL_Text::GL_Text()
	: m_FontSize(12), 
	  m_Face(NULL),
	  m_Matrix (new GL_Matrix())
{
	if(FT_Init_FreeType(&m_Library)) 
	{
		std::cout <<  "Could not init freetype library\n" << std::endl;
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindVertexArray(0);
}

GL_Text::~GL_Text()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	FT_Done_Face(m_Face);
	FT_Done_FreeType(m_Library);
}

GLvoid GL_Text::Prepare()
{
	
}

GLvoid GL_Text::Update()
{
	m_Matrix->LoadIdenditity();
	m_Matrix->Ortho(vec2(0, 1600), vec2(0, 900));
}

GLvoid GL_Text::Render()
{
	m_pShader->Use();

	m_pShader->setMatrix("ModelMatrix", m_Matrix->getModel());
	m_pShader->setMatrix("ViewMatrix", m_Matrix->getView());

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	vec2 PreviousPosition = m_Position;

	for(GLuint i = 0; i < m_Text.size(); i++)
	{
		if(FT_Load_Char(m_Face, m_Text[i], FT_LOAD_RENDER) || m_Text[i] == ' ')
		{
			m_Position.x += 10;
		}
		else
		{
			auto Sprite = GL_Textures::get()->CreateGlyph(m_Face, GL_ALPHA);

			GLubyte * BitmapData = m_Face->glyph->bitmap.buffer;
			GLuint BitmapHeight = m_Face->glyph->bitmap.rows;
			GLuint BitmapWidth = m_Face->glyph->bitmap.width;

			m_Position.y -= BitmapHeight - m_Face->glyph->bitmap_top;			
		
			GLfloat units[] = 
			{
				m_Position.x, m_Position.y, 0, 1,
				m_Position.x + BitmapWidth, m_Position.y, 1, 1,
				m_Position.x, m_Position.y + BitmapHeight, 0, 0,
				m_Position.x + BitmapWidth, m_Position.y + BitmapHeight, 1, 0,
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*16, units, GL_DYNAMIC_DRAW);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			m_Position.x += m_Face->glyph->bitmap.width + 2;
			m_Position.y = PreviousPosition.y;
			delete Sprite;
		}
	}

	m_Position = PreviousPosition;
	m_pShader->Release();

	glBindVertexArray(0);
}

// Set & Get Functions
GLvoid GL_Text::setSize(GLuint size)
{
	if(m_Face == NULL)
	{
		if(FT_New_Face(m_Library, m_Fontname.c_str(), 0, &m_Face)) 
		{
			std::cout <<  "Could not open font " + m_Fontname << std::endl;
		}
	}

	FT_Set_Pixel_Sizes(m_Face, 0, size);
	m_FontSize = size;

	const char * vs = "data/shaders/text.vert";
	const char * fs = "data/shaders/text.frag";

	m_pShader = GL_Shader_Manager::get()->GetShader(vs, fs);
}

GLuint GL_Text::getHeight()
{
	GLuint Height = NULL;
	for(GLuint i = 0; i < m_Text.size(); i++)
	{
		FT_Load_Char(m_Face, m_Text[i], FT_LOAD_RENDER);
		
		Height += m_Face->glyph->bitmap.rows;
	}

	return(Height/m_Text.size());
}

GLuint GL_Text::getWidth()
{
	GLuint Width = NULL;
	for(GLuint i = 0; i < m_Text.size(); i++)
	{
		FT_Load_Char(m_Face, m_Text[i], FT_LOAD_RENDER);
		
		Width += m_Face->glyph->bitmap.width;
		Width += 2;
	}

	return Width;
}

GLvoid GL_Text::setPosition(vec2 pos)
{
	m_Position = pos;
}

GLvoid GL_Text::setFont(std::string filename)
{
	m_Fontname = filename;
}

GLvoid GL_Text::setText(std::string text)
{
	m_Text = text;
}