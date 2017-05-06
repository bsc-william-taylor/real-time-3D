
#pragma once

#include "ProgramGL.h"
#include "TextureGL.h"
#include "SubSurface.h"
#include "Surface.h"
#include "IModel.h"

#pragma region STD
#define MD2_STAND	0
#define MD2_RUN		1
#define MD2_ATTACK	2
#define MD2_PAIN1	3
#define MD2_PAIN2	4
#define MD2_PAIN3	5
#define MD2_JUMP	6
#define MD2_FLIP	7
#define MD2_SALUTE	8
#define MD2_TAUNT	9
#define MD2_WAVE	10
#define MD2_POINT	11
#define MD2_CRSTAND	12
#define MD2_CRWALK	13
#define MD2_CRATTACK	14
#define MD2_CRPAIN	15
#define MD2_CRDEATH	16
#define MD2_DEATH1	17
#define MD2_DEATH2	18
#define MD2_DEATH3	19

typedef GLfloat md2vec3[3];

/* MD2 header */
struct md2_header_t
{
  int ident;
  int version;

  int skinwidth;
  int skinheight;

  int framesize;

  int num_skins;
  int num_vertices;
  int num_st;
  int num_tris;
  int num_glcmds;
  int num_frames;

  int offset_skins;
  int offset_st;
  int offset_tris;
  int offset_frames;
  int offset_glcmds;
  int offset_end;
};

/* Texture name */
struct md2_skin_t
{
  char name[64];
};

/* Texture coords */
struct md2_texCoord_t
{
  short s;
  short t;
};

/* Triangle info */
struct md2_triangle_t
{
  unsigned short vertex[3];
  unsigned short st[3];
};

/* Compressed vertex */
struct md2_vertex_t
{
  unsigned char v[3];
  unsigned char normalIndex;
};

/* Model frame */
struct md2_frame_t
{
  md2vec3 scale;
  md2vec3 translate;
  char name[16];
  struct md2_vertex_t *verts;
};

/* GL command packet */
struct md2_glcmd_t
{
  float s;
  float t;
  int index;
};


/* MD2 model structure */
struct md2_model_t
{
  struct md2_header_t header;

  struct md2_skin_t *skins;
  struct md2_texCoord_t *texcoords;
  struct md2_triangle_t *triangles;
  struct md2_frame_t *frames;
  int *glcmds;

  GLuint tex_id;
};

#pragma endregion

class DynamicModel : public IModel
{
private:

	md2_model_t mdl;
	GLfloat interp;
	std::vector<GLfloat *> vertData;
	GLuint vertDataSize;
	GLfloat *animVerts;

	GL_Sprite * m_Texture;
	GL_Program * Program;
	GL_Matrix * Matrix;

	GLuint CurrentAnim;
	GLuint CurrentFrame;
	GLuint NextFrame;

	GLuint VertexBuffer, TextureBuffer, NormalBuffer;
	GLuint VAO;

	Surface * m_BoundingBox;

public:
	
	DynamicModel();
	~DynamicModel();

	GLvoid update();
	void Prepare(){}
	bool isDynamic() { return true; }

	GL_Matrix * getMatrix( ) { return Matrix; }
	GLvoid ReadMD2Model(const GLchar *, GLboolean bb);
	GLvoid ReadTexture(const GLchar *);
	GLvoid Animate(GLuint, GLfloat);
	GLvoid Animate(GLfloat);
	GLvoid FreeModel();
	GLvoid render(mat4);
	
	GLuint setCurrentAnim(int n);
	GLuint getVertDataCount();
	GLuint getVertDataSize();
	GLuint getCurrentAnim();

	GLfloat* getAnimVerts();

	Surface * getSurface(){ return m_BoundingBox; }
};