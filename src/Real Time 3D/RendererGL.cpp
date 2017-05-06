
/* -------------------------------------------------
  
 @Filename  : GL_Renderer.h
 @author	: William Taylor
 @date		: 14/02/2014
  @purpose	: Class Implementation

 ------------------------------------------------- */

#include "RendererGL.h"
#include "SurfaceManager.h"

// Constructor & Deconstructor
RendererGL::RendererGL()
{
	m_Textures.reserve(20);
	heightmap = NULL;
}

RendererGL::~RendererGL()
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		delete m_Textures[i];
		m_Textures[i] = NULL;
	}
}

GLvoid RendererGL::PushAudioNode(AudioNode * node)
{
	if(node != NULL)
	{
		m_AudioNodes.push_back(node);
	}
}

GLvoid RendererGL::PushHeightmap(HeightmapGL * object)
{
	if(object != NULL)
	{
		heightmap = object;
	}
}

GLvoid RendererGL::PushSurface(Surface * surface)
{
	if(surface != NULL)
	{
		m_Surfaces.push_back(surface);
	}
}

// Member Functions
GLvoid RendererGL::RenderTexture(TextureGL * texture)
{
	GL_Program * Program = texture->getProgram();
	GL_Matrix * Matrix = texture->getMatrix();

	Program->Use();	

	glBindVertexArray(texture->getVAO());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID());

	GLuint ID = glGetUniformLocation(Program->getID(), "shade");
	glUniform4fv(ID, 1, glm::value_ptr(texture->getShade()));
	Program->setMatrix("Projection", Matrix->getProjection());
	Program->setMatrix("Model", Matrix->getModel());
	Program->setMatrix("View", Matrix->getView());

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

GLvoid RendererGL::Render3D(GLboolean wireframe)
{
	glEnable(GL_DEPTH_TEST);

	if(!wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

GLvoid RendererGL::Render2D(GLboolean wireframe)
{
	glDisable(GL_DEPTH_TEST);

	if(!wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

GLvoid RendererGL::RenderModel(IModel * model, mat4 mat)
{
	if(!model->isDynamic())
	{
		StaticModel * Model = (StaticModel *)model;
		GL_Program * Program = Model->getProgram();
		GL_Matrix * Matrix = Model->getMatrix();
	
		glBindVertexArray(Model->getVAO());

		Program->Use();
		Program->setMatrix("Projection", Matrix->getProjection());
		Program->setMatrix("NormalMat", mat4(1.0));
		Program->setMatrix("Model", Matrix->getModel());
		Program->setMatrix("View", Matrix->getView());

		for(unsigned int i = 0; i < Model->getMeshNumber(); i++)
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
		((DynamicModel *)model)->render(mat);
	}
}

GLvoid RendererGL::PushSkybox(SkyboxGL * object)
{
	m_Skybox = object;

	auto Textures = m_Skybox->getTextures();

	for(unsigned int i = 0; i < Textures.size(); i++)
	{
		PushTexture(Textures[i]);
	}
}

GLvoid RendererGL::PushTexture(TextureGL * object)
{
	if(object != NULL) 
	{
		m_Textures.push_back(object);
	} 
}

GLvoid RendererGL::PushModel(IModel * object)
{
	if(object != NULL) 
	{
		m_Models.push_back(object);
	} 
}

GLvoid RendererGL::Ortho(const vec2 a, const vec2 b, const vec2 c)
{
	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures[i]->getMatrix()->Ortho(a, b, c);
	}
}

GLvoid RendererGL::setSurfaceSize(vec4 vec)
{
	this->m_SurfaceSize = vec;
}

GLvoid RendererGL::LoadIdentity()
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

	if(heightmap)
	{
		heightmap->getMatrix()->LoadIdenditity();
	}
}

GLvoid RendererGL::update()
{
	m_Skybox ? m_Skybox->update() : 0;
	if(heightmap)heightmap->update();
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->update();
	for(unsigned int i = 0; i < m_Labels.size(); i++)
		m_Labels[i]->update();
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->update();
}

GLvoid RendererGL::Prepare()
{

	if(heightmap)heightmap->Prepare();


	for(unsigned int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures[i]->Prepare();
	}


	for(unsigned int i = 0; i < m_Labels.size(); i++)
		m_Labels[i]->Prepare();


	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->Prepare();
}

GLvoid RendererGL::render()
{
	if(heightmap)heightmap->Draw();
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		RenderTexture(m_Textures[i]);
	for(unsigned int i = 0; i < m_Models.size(); i++)
		RenderModel(m_Models[i], mat4(1.0f));
	for(unsigned int i = 0; i < m_Labels.size(); i++)
		m_Labels[i]->render();
	for(unsigned int i = 0; i < m_Surfaces.size(); i++)
		m_Surfaces[i]->render();

	for(unsigned int i = 0; i < m_AudioNodes.size(); i++)
	{
		m_AudioNodes[i]->render();
	} 
}

GLvoid RendererGL::PushText(TextGL * textItem)
{
	if(textItem != NULL)
	{
		m_Labels.push_back(textItem);
	}
}

GLvoid RendererGL::Perspective(const float f, const vec2 v1, const vec2 v2)
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

	if(heightmap) {
		heightmap->getMatrix()->Perspective(f, v1, v2);
	}
}

GLvoid RendererGL::RotateView(GLfloat f, vec3 a)
{
	if(heightmap)heightmap->getMatrix()->RotateView(f, a);
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->getMatrix()->RotateView(f, a);
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->getMatrix()->RotateView(f, a);
	for(unsigned int i = 0; i < m_AudioNodes.size(); i++)
		m_AudioNodes[i]->getMatrix()->RotateView(f, a);
}

GLvoid RendererGL::Rotate(GLfloat f, vec3 a)
{
	if(heightmap)heightmap->getMatrix()->Rotate(f, a);
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->getMatrix()->Rotate(f, a);
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->getMatrix()->Rotate(f, a);
}

GLvoid RendererGL::TranslateView(vec3 v)
{
	if(heightmap)heightmap->getMatrix()->TranslateView(v);
	m_Skybox ? m_Skybox->Translate(v) : 0;
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->getMatrix()->TranslateView(v);
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->getMatrix()->TranslateView(v);
	for(unsigned int i = 0; i < m_AudioNodes.size(); i++)
		m_AudioNodes[i]->getMatrix()->TranslateView(v);
}

GLvoid RendererGL::Translate(vec3 v)
{
	if(heightmap)heightmap->getMatrix()->Translate(v);
	for(unsigned int i = 0; i < m_Textures.size(); i++)
		m_Textures[i]->getMatrix()->Translate(v);
	for(unsigned int i = 0; i < m_Labels.size(); i++)
		m_Labels[i]->getMatrix()->Translate(v);
	for(unsigned int i = 0; i < m_Models.size(); i++)
		m_Models[i]->getMatrix()->Translate(v);
}