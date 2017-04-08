
/* -------------------------------------------------
  
 @Filename  : GL_Renderer.h
 @author	: William Taylor
 @date		: 14/02/2014
  @purpose	: Class Implementation

 ------------------------------------------------- */

#include "GL_Renderer.h"
#include "SurfaceManager.h"

// Constructor & Deconstructor
GL_Renderer::GL_Renderer()
{
	m_Textures.reserve(20);
	m_Heightmap = NULL;
}

GL_Renderer::~GL_Renderer()
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		delete m_Textures[i];
		m_Textures[i] = NULL;
	}
}

GLvoid GL_Renderer::PushAudioNode(AudioNode * node)
{
	if(node != NULL)
	{
		m_AudioNodes.push_back(node);
	}
}

GLvoid GL_Renderer::PushHeightmap(GL_Heightmap * object)
{
	if(object != NULL)
	{
		m_Heightmap = object;
	}
}

GLvoid GL_Renderer::PushSurface(Surface * surface)
{
	if(surface != NULL)
	{
		m_Surfaces.push_back(surface);
	}
}

// Member Functions
GLvoid GL_Renderer::RenderTexture(GL_Texture * texture)
{
	GL_Program * Program = texture->getProgram();
	GL_Matrix * Matrix = texture->getMatrix();

	Program->Use();	

	glBindVertexArray(texture->getVAO());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID());

	Program->setMatrix("Projection", Matrix->getProjection());
	Program->setMatrix("Model", Matrix->getModel());
	Program->setMatrix("View", Matrix->getView());

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

GLvoid GL_Renderer::RenderModel(IModel * model)
{
	if(!model->isDynamic())
	{
		StaticModel * Model = (StaticModel *)model;
		GL_Program * Program = Model->getProgram();
		GL_Matrix * Matrix = Model->getMatrix();
	
		glBindVertexArray(Model->getVAO());

		Program->Use();
		Program->setMatrix("Projection", Matrix->getProjection());
		Program->setMatrix("Model", Matrix->getModel());
		Program->setMatrix("View", Matrix->getView());

		for(int i = 0; i < Model->getMeshNumber(); i++)
		{
			GLuint Index = Model->getMaterialIndex(i);
			GLuint ID = Model->getTextureID(Index);

			if(ID != -1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, ID);
			}
		
			glDrawArrays(GL_TRIANGLES, Model->getMeshStart(i), Model->getMeshEnd(i));
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Program->Release();

		glBindVertexArray(0);
	}
	else
	{
		((DynamicModel *)model)->Render();
	}
}

GLvoid GL_Renderer::PushSkybox(GL_Skybox * object)
{
	m_Skybox = object;

	auto Textures = m_Skybox->getTextures();

	for(unsigned int i = 0; i < Textures.size(); i++)
	{
		PushTexture(Textures[i]);
	}
}

GLvoid GL_Renderer::PushTexture(GL_Texture * object)
{
	if(object != NULL) 
	{
		m_Textures.push_back(object);
	} 
}

GLvoid GL_Renderer::PushModel(IModel * object)
{
	if(object != NULL) 
	{
		m_Models.push_back(object);
	} 
}

GLvoid GL_Renderer::Ortho(const vec2 a, const vec2 b, const vec2 c)
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures[i]->getMatrix()->Ortho(a, b, c);
	}
}

GLvoid GL_Renderer::setSurfaceSize(vec4 vec)
{
	this->m_SurfaceSize = vec;
}

GLvoid GL_Renderer::LoadIdentity()
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures[i]->getMatrix()->LoadIdenditity();
	} 

	for(unsigned int i = 0; i < m_Labels.size(); i++)
	{
		GLint Height = (GLint)m_SurfaceSize.w;
		GLint Width = (GLint)m_SurfaceSize.z;

		m_Labels[i]->getMatrix()->LoadIdenditity();
		m_Labels[i]->getMatrix()->Ortho(vec2(0, Width), vec2(0, Height), vec2(-1, 1));
	} 

	for(unsigned int i = 0; i < m_Models.size(); i++)
	{
		m_Models[i]->getMatrix()->LoadIdenditity();
	} 

	for(unsigned int i = 0; i < m_AudioNodes.size(); i++)
	{
		m_AudioNodes[i]->getMatrix()->LoadIdenditity();
	} 

	if(m_Heightmap)
	{
		m_Heightmap->getMatrix()->LoadIdenditity();
	}
}

GLvoid GL_Renderer::Update()
{
	m_Skybox ? m_Skybox->Update() : 0;
	if(m_Heightmap)m_Heightmap->Update();
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->Update();
	for(unsigned int i = 0; i < m_Labels.size(); i++)
		m_Labels[i]->Update();
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->Update();
}

GLvoid GL_Renderer::Prepare()
{
	if(m_Heightmap)m_Heightmap->Prepare();
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->Prepare();
	for(unsigned int i = 0; i < m_Labels.size(); i++)
		m_Labels[i]->Prepare();
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->Prepare();
}

GLvoid GL_Renderer::Render()
{
	if(m_Heightmap)m_Heightmap->Draw();
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		RenderTexture(m_Textures[i]);
	for(unsigned int i = 0; i < m_Models.size(); i++)
		RenderModel(m_Models[i]);
	for(unsigned int i = 0; i < m_Labels.size(); i++)
		m_Labels[i]->Render();
	for(unsigned int i = 0; i < m_Surfaces.size(); i++)
		m_Surfaces[i]->Render();

	for(unsigned int i = 0; i < m_AudioNodes.size(); i++)
	{
		m_AudioNodes[i]->Render();
	} 
}

GLvoid GL_Renderer::PushText(GL_Text * textItem)
{
	if(textItem != NULL)
	{
		m_Labels.push_back(textItem);
	}
}

GLvoid GL_Renderer::Perspective(const float f, const vec2 v1, const vec2 v2)
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)	{
		m_Textures[i]->getMatrix()->Perspective(f, v1, v2);
	}

	for(unsigned int i = 0; i < m_Models.size(); i++) {
		m_Models[i]->getMatrix()->Perspective(f, v1, v2);
	}

	for(unsigned int i = 0; i < m_Labels.size(); i++) {
		m_Labels[i]->getMatrix()->Perspective(f, v1, v2);
	}

	if(m_Heightmap) {
		m_Heightmap->getMatrix()->Perspective(f, v1, v2);
	}
}

GLvoid GL_Renderer::RotateView(GLfloat f, vec3 a)
{
	if(m_Heightmap)m_Heightmap->getMatrix()->RotateView(f, a);
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->getMatrix()->RotateView(f, a);
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->getMatrix()->RotateView(f, a);
	for(unsigned int i = 0; i < m_AudioNodes.size(); i++)
		m_AudioNodes[i]->getMatrix()->RotateView(f, a);
}

GLvoid GL_Renderer::Rotate(GLfloat f, vec3 a)
{
	if(m_Heightmap)m_Heightmap->getMatrix()->Rotate(f, a);
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->getMatrix()->Rotate(f, a);
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->getMatrix()->Rotate(f, a);
}

GLvoid GL_Renderer::TranslateView(vec3 v)
{
	if(m_Heightmap)m_Heightmap->getMatrix()->TranslateView(v);
	m_Skybox ? m_Skybox->Translate(v) : 0;
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->getMatrix()->TranslateView(v);
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->getMatrix()->TranslateView(v);
	for(unsigned int i = 0; i < m_AudioNodes.size(); i++)
		m_AudioNodes[i]->getMatrix()->TranslateView(v);
}

GLvoid GL_Renderer::Translate(vec3 v)
{
	if(m_Heightmap)m_Heightmap->getMatrix()->Translate(v);
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->getMatrix()->Translate(v);
	for(unsigned int i = 0; i < m_Labels.size(); i++)
		m_Labels[i]->getMatrix()->Translate(v);
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->getMatrix()->Translate(v);
}