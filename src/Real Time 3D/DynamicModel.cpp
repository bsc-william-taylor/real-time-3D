#include "DynamicModel.h"
#include "SurfaceBuilder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

/* Table of precalculated normals */
md2vec3 anorms_table[162] = {
#include "anorms.h"
};

// Table of animation begin/end frames
static int animFrameList[40] = {
	0, 39, // stand
	40, 45, // run
	46, 53, // attack
	54, 57, //pain1
	58, 61, //pain2
	62, 65, //pain3
	66, 71, //jump
	72, 83, //flip
	84, 94, //salute
	95, 111, //taunt
	112, 122, //wave
	123, 134, //point
	135, 153, //crstnd
	154, 159, //crwalk
	160, 168, //crattak
	169, 172, //crpain
	173, 177, //crdeath
	178, 183, //death1
	184, 189, //death2
	190, 196 //death3
};

DynamicModel::DynamicModel()
{
	CurrentFrame = 0;
	CurrentAnim = 0;
	NextFrame = 1;
	interp = 0.0f;
    Matrix = new GL_Matrix();
}

DynamicModel::~DynamicModel()
{
	FreeModel();

	for(int i=0;i<mdl.header.num_frames;++i) 
	{
		delete[] vertData[i];
	}
	
	delete[] animVerts;
}

GLvoid DynamicModel::ReadTexture(const GLchar * filename) 
{
	m_Texture = GL_Textures::get()->CreateTexture(filename, GL_REPEAT);
}

GLvoid DynamicModel::ReadMD2Model(const GLchar *filename, GLboolean bound)
{
	FILE *fp;
	int i;

	fopen_s(&fp, filename, "rb");
	if (!fp)
	{
		fprintf (stderr, "Error: couldn't open \"%s\"!\n", filename);
		return;
	}

	/* Read header */
	fread (&mdl.header, 1, sizeof (struct md2_header_t), fp);

	if ((mdl.header.ident != 844121161) ||
		(mdl.header.version != 8))
	{
		/* Error! */
		fprintf (stderr, "Error: bad version or identifier\n");
		fclose (fp);
		return;
	}

	/* Memory allocations */
	mdl.skins = (struct md2_skin_t *)
		malloc (sizeof (struct md2_skin_t) * mdl.header.num_skins);
	mdl.texcoords = (struct md2_texCoord_t *)
		malloc (sizeof (struct md2_texCoord_t) * mdl.header.num_st);
	mdl.triangles = (struct md2_triangle_t *)
		malloc (sizeof (struct md2_triangle_t) * mdl.header.num_tris);
	mdl.frames = (struct md2_frame_t *)
		malloc (sizeof (struct md2_frame_t) * mdl.header.num_frames);
	mdl.glcmds = (int *)malloc (sizeof (int) * mdl.header.num_glcmds);

	/* Read model data */
	fseek (fp, mdl.header.offset_skins, SEEK_SET);
	fread (mdl.skins, sizeof (struct md2_skin_t),
		mdl.header.num_skins, fp);

	fseek (fp, mdl.header.offset_st, SEEK_SET);
	fread (mdl.texcoords, sizeof (struct md2_texCoord_t),
		mdl.header.num_st, fp);

	fseek (fp, mdl.header.offset_tris, SEEK_SET);
	fread (mdl.triangles, sizeof (struct md2_triangle_t),
		mdl.header.num_tris, fp);

	fseek (fp, mdl.header.offset_glcmds, SEEK_SET);
	fread (mdl.glcmds, sizeof (int), mdl.header.num_glcmds, fp);

	/* Read frames */
	fseek (fp, mdl.header.offset_frames, SEEK_SET);
	for (i = 0; i < mdl.header.num_frames; ++i)
	{
		/* Memory allocation for vertices of this frame */
		mdl.frames[i].verts = (struct md2_vertex_t *)
			malloc (sizeof (struct md2_vertex_t) * mdl.header.num_vertices);

		/* Read frame data */
		fread (mdl.frames[i].scale, sizeof (md2vec3), 1, fp);
		fread (mdl.frames[i].translate, sizeof (md2vec3), 1, fp);
		fread (mdl.frames[i].name, sizeof (char), 16, fp);
		fread (mdl.frames[i].verts, sizeof (struct md2_vertex_t),
			mdl.header.num_vertices, fp);
	}

	fclose (fp);

	// now generate VBO data and create mesh
	// then save the data we actually need and free all the stuff we no longer need
	// this is required to allow the correct generation of normals etc

	int j;
	GLfloat s, t;
	md2vec3 v, *norm;
	struct md2_frame_t *pframe;
	struct md2_vertex_t *pvert;

	
	std::vector<GLfloat> tex_coords;
	std::vector<GLfloat> norms;
	std::vector<GLuint> indices;

	pframe = &mdl.frames[0]; // first frame


	for (i = 0; i < mdl.header.num_tris; ++i)
	{
		// For each vertex 
		for (j = 0; j < 3; ++j)
		{
			// Get texture coordinates 
			tex_coords.push_back( (GLfloat)mdl.texcoords[mdl.triangles[i].st[j]].s / mdl.header.skinwidth );
			tex_coords.push_back( (GLfloat)mdl.texcoords[mdl.triangles[i].st[j]].t / mdl.header.skinheight );

			// get current vertex
			pvert = &pframe->verts[mdl.triangles[i].vertex[j]];

			// Get normals 
			//norm = anorms_table[pvert->normalIndex][0];
			norms.push_back(anorms_table[pvert->normalIndex][0]);
			norms.push_back(anorms_table[pvert->normalIndex][1]);
			norms.push_back(anorms_table[pvert->normalIndex][2]);

		}
	}
	

	int k = 0;
	GLfloat *verts;
	vertDataSize = mdl.header.num_tris * 9;
	for (k=0;k<mdl.header.num_frames;++k) {
		verts = new GLfloat[vertDataSize];
		pframe = &mdl.frames[k];
		for (i = 0; i < mdl.header.num_tris; ++i)
		{
			// For each vertex 
			for (j = 0; j < 3; ++j)
			{
				// get current vertex
				pvert = &pframe->verts[mdl.triangles[i].vertex[j]];
				verts[(i*3 + j)*3] = GLfloat(pframe->scale[0] * pvert->v[0] + pframe->translate[0]);
				verts[(i*3 + j)*3+1] = GLfloat(pframe->scale[1] * pvert->v[1] + pframe->translate[1]);
				verts[(i*3 + j)*3+2] = GLfloat(pframe->scale[2] * pvert->v[2] + pframe->translate[2]);
			}
		}
		vertData.push_back(verts);
	}

	animVerts = new GLfloat[vertDataSize];
	memcpy(animVerts,vertData[0],vertDataSize*sizeof(float));

	Program = GL_Shader_Manager::get()->GetShader("data/shaders/model.vert", "data/shaders/model.frag");


	// generate and set up a VAO for the mesh
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	std::cout << tex_coords.size() << std::endl;

	// generate and set up the VBOs for the data
	GLuint VBO;
	
	int numVerts = mdl.header.num_tris * 3;

	// VBO for vertex data
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 3*numVerts*sizeof(GLfloat), vertData[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(0);

	VertexBuffer = VBO;


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 3*numVerts*sizeof(GLfloat), norms.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	NormalBuffer = VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 2*numVerts*sizeof(GLfloat), tex_coords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	TextureBuffer = VBO;

	// unbind vertex array
	glBindVertexArray(0);
	
	
	Matrix->Perspective(70.0f, vec2(16, 9), vec2(0.1, 1000));

	if(bound)
	{
		SurfaceBuilder * builder = new SurfaceBuilder();
		for(unsigned int i = 0; i < vertData.size(); i++) {
			aiVector3D point;
	
			point.x = vertData[i][0];
			point.y = vertData[i][1];
			point.z = vertData[i][2];
		
			builder->PushPoint(point);
		}

		builder->Ignore();
		builder->PushSurface(Matrix);
		builder->EndOfMesh(0);
		m_BoundingBox = builder->Release();
		delete builder;
	}
	
	FreeModel();
}

GLvoid DynamicModel::update()
{
	
}

void DynamicModel::render(mat4 m)
{
	Program->Use();
	Program->setMatrix("Projection", Matrix->getProjection());
	Program->setMatrix("NormalMat", glm::transpose(m));
	Program->setMatrix("Model", Matrix->getModel());
	Program->setMatrix("View", Matrix->getView());

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, m_Texture->m_ID);
	glDrawArrays(GL_TRIANGLES, 0, getVertDataCount());
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	Program->Release();
}

void DynamicModel::FreeModel ()
{
	int i;

	if (mdl.skins)
	{
		free (mdl.skins);
		mdl.skins = NULL;
	}

	if (mdl.texcoords)
	{
		free (mdl.texcoords);
		mdl.texcoords = NULL;
	}

	if (mdl.triangles)
	{
		free (mdl.triangles);
		mdl.triangles = NULL;
	}

	if (mdl.glcmds)
	{
		free (mdl.glcmds);
		mdl.glcmds = NULL;
	}

	if (mdl.frames)
	{
		for (i = 0; i < mdl.header.num_frames; ++i)
		{
			free (mdl.frames[i].verts);
			mdl.frames[i].verts = NULL;
		}

		free (mdl.frames);
		mdl.frames = NULL;
	}
}



/**
* Calculate the current frame in animation, based on
* selected animation and current frame. If current frame
* is not in selected animation sequence, new current frame
* is start of animation sequence. 
* If interpolation is past 1.0, move current frame to next
* and next frame = current frame + 1
*/

void DynamicModel::Animate(GLuint animation, GLfloat dt)
{
	GLint start = animFrameList[animation * 2];
	GLint end =  animFrameList[animation * 2 + 1];
	
	if((CurrentFrame < start) || (CurrentFrame > end))
	{
		CurrentFrame = start;
		NextFrame = start + 1;
	}

	interp += dt;
	
	if(interp >= 1.0f)
	{
		// Move to next frame 
		interp = 0.0f;
		CurrentFrame = NextFrame;
		NextFrame++;

		if(NextFrame >= end+1)
		{
			NextFrame = start;
		}
	}

	if(interp == 0.0f)
	{
		memcpy(animVerts,vertData[CurrentFrame],vertDataSize*sizeof(float));
	}
	else 
	{
		for(int i = 0; i < vertDataSize; i++)
		{
			animVerts[i] = vertData[CurrentFrame][i];
			animVerts[i] += interp*(vertData[NextFrame][i] - vertData[CurrentFrame][i]);
		}
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, getVertDataSize() * sizeof(GLfloat), getAnimVerts(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	
}

GLvoid DynamicModel::Animate(float dt) 
{ 
	Animate(CurrentAnim, dt); 
}

GLuint DynamicModel::getVertDataCount() 
{ 
	return vertDataSize; 
}

GLuint DynamicModel::getVertDataSize() 
{
	return vertDataSize; 
}

GLuint DynamicModel::getCurrentAnim() 
{ 
	return CurrentAnim; 
}

GLfloat* DynamicModel::getAnimVerts() 
{ 
	return animVerts; 
}