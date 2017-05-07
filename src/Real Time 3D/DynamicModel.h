
#pragma once

#include "ProgramGL.h"
#include "TextureGL.h"
#include "SubSurface.h"
#include "Surface.h"
#include "Model.h"

#define MD2_STAND	 0
#define MD2_RUN		 1
#define MD2_ATTACK	 2
#define MD2_PAIN1	 3
#define MD2_PAIN2	 4
#define MD2_PAIN3	 5
#define MD2_JUMP	 6
#define MD2_FLIP	 7
#define MD2_SALUTE	 8
#define MD2_TAUNT	 9
#define MD2_WAVE	 10
#define MD2_POINT	 11
#define MD2_CRSTAND	 12
#define MD2_CRWALK	 13
#define MD2_CRATTACK 14
#define MD2_CRPAIN	 15
#define MD2_CRDEATH	 16
#define MD2_DEATH1	 17
#define MD2_DEATH2	 18
#define MD2_DEATH3	 19

typedef GLfloat md2vec3[3];

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

struct md2_skin_t
{
    char name[64];
};

struct md2_texCoord_t
{
    short s;
    short t;
};

struct md2_triangle_t
{
    unsigned short vertex[3];
    unsigned short st[3];
};

struct md2_vertex_t
{
    unsigned char v[3];
    unsigned char normalIndex;
};

struct md2_frame_t
{
    md2vec3 scale;
    md2vec3 translate;
    char name[16];
    md2_vertex_t *verts;
};

struct md2_glcmd_t
{
    float s;
    float t;
    int index;
};

struct md2_model_t
{
    md2_header_t header;
    md2_skin_t *skins;
    md2_texCoord_t *texcoords;
    md2_triangle_t *triangles;
    md2_frame_t *frames;
    int *glcmds;
    GLuint tex_id;
};

class DynamicModel : public Model
{
    std::vector<GLfloat*> vertData;
    md2_model_t mdl;

    ProgramGL* program;
    SpriteGL* texture;
    MatrixGL* matrix;

    GLuint vertDataSize;
    GLuint vertexBuffer;
    GLuint textureBuffer;
    GLuint normalBuffer;
    GLuint vertexArray;
    GLuint currentAnim;
    GLuint currentFrame;
    GLuint nextFrame;

    Surface* boundingBox;
    GLfloat* animVerts;
    GLfloat interp;
public:
    DynamicModel();
    ~DynamicModel();

    bool isDynamic();

    GLvoid prepare();
    GLvoid onUpdate();
    GLvoid readMD2Model(const GLchar *, GLboolean bb);
    GLvoid readTexture(const GLchar *);
    GLvoid animate(GLuint, GLfloat);
    GLvoid animate(GLfloat);
    GLvoid freeModel();
    GLvoid render(mat4);

    GLfloat* getAnimVerts();

    GLuint setCurrentAnim(int n);
    GLuint getVertDataCount();
    GLuint getVertDataSize();
    GLuint getCurrentAnim();

    MatrixGL* getMatrix();
    Surface * getSurface();
};