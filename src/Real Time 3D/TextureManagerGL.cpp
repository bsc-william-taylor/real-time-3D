
/* -------------------------------------------------
  
 @Filename  : GL_Texture_Manager.cpp
 @author	: William Taylor
 @date		: 14/02/2014

 @purpose	: Class implementation

 ------------------------------------------------- */

#include "TextureManagerGL.h"

TextureManagerGL * TextureManagerGL::m_pManager = NULL;

// Constructor & Deconstructor
TextureManagerGL::TextureManagerGL()
{
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

TextureManagerGL::~TextureManagerGL()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	FreeTextures();
}

// Member Functions
GL_Sprite * TextureManagerGL::CreateTexture(const std::string& filename, GLenum e)
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		if(m_Textures[i]->m_TextureName == filename)
		{
			return m_Textures[i];
		}
	}

	GL_Sprite * Tex = LoadTexture(filename, e);
		
	if(Tex != NULL)
	{
		m_Textures.push_back(Tex);
	}

	return Tex;
}

GLuint TextureManagerGL::getTextureCount()
{
	return(m_Textures.size());
}


GL_Sprite * TextureManagerGL::CreateTexture(GLubyte * data, GLuint width, GLuint height, GLenum format)
{
	GL_Sprite * Sprite = new GL_Sprite();

	Sprite->Height = height;
	Sprite->Width = width;

	glGenTextures(1, &Sprite->m_ID);
	glBindTexture(GL_TEXTURE_2D, Sprite->m_ID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)data);

	return Sprite;
}

GL_Sprite * TextureManagerGL::CreateGlyph(FT_Face face, GLenum format)
{
	GL_Sprite * Sprite = new GL_Sprite();
	
	Sprite->Height = face->glyph->bitmap.rows;
	Sprite->Width = face->glyph->bitmap.width;

	glGenTextures(1, &Sprite->m_ID);
	glBindTexture(GL_TEXTURE_2D, Sprite->m_ID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, Sprite->Width, Sprite->Height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, (GLvoid*)face->glyph->bitmap.buffer);
	return Sprite;
}

GL_Sprite * TextureManagerGL::LoadTexture(const std::string& Location, GLenum e)
{
	GL_Sprite * Sprite = new GL_Sprite();

	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(Location.c_str(), 0);
		
	FIBITMAP * Texture = FreeImage_Load(formato, Location.c_str());
	FIBITMAP * Temp    = FreeImage_ConvertTo32Bits(Texture);
		
	GLuint Height = FreeImage_GetHeight(Temp);
	GLuint Width = FreeImage_GetWidth(Temp);

	BYTE * NewBits	= new BYTE[Height * Width * 4];
	BYTE * Bits		= FreeImage_GetBits(Temp);

	Sprite->Height = Height;
	Sprite->Width = Width;

	for (GLuint i = 0; i < Width * Height; i++)
	{
        NewBits[i * 4 + 0] = Bits[i * 4 + 2];
        NewBits[i * 4 + 1] = Bits[i * 4 + 1];
        NewBits[i * 4 + 2] = Bits[i * 4 + 0];
        NewBits[i * 4 + 3] = Bits[i * 4 + 3];
    }		

	RGBQUAD Colour;
	BOOL reserve = false;

	Sprite->Colour.reserve(Width);
	Sprite->Colour.resize(Width);

	for(GLuint i = 0; i < Width; i++) 
	{
		for(GLuint z = 0; z < Height; z++)
		{
			if(!reserve)
			{
				Sprite->Colour[i].reserve(Height);
				reserve = true;
			}

			FreeImage_GetPixelColor(Temp, i, z, &Colour);
			Sprite->Colour[i].push_back(Colour);
		}

		reserve = false;
	}

	glGenTextures(1, &Sprite->m_ID);
	glBindTexture(GL_TEXTURE_2D, Sprite->m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, e);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, e);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid *)NewBits);

	FreeImage_Unload(Texture);
	FreeImage_Unload(Temp);
	
	delete[] NewBits;
	return Sprite;
}

GLvoid TextureManagerGL::FreeTextures()
{
	for(GLuint i = 0; i < m_Textures.size(); i++)
	{
		glDeleteTextures(1, &m_Textures[i]->m_ID);
	}
}

// Get Functions
TextureManagerGL * TextureManagerGL::get()
{
	if(m_pManager == NULL) 
	{
		m_pManager = new TextureManagerGL();
	}

	return m_pManager;
}