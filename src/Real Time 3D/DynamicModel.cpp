#include "DynamicModel.h"
#include "SurfaceBuilder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

md2vec3 anorms_table[162] = {
    #include "anorms.h"
};

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
    currentFrame = 0;
    currentAnim = 0;
    nextFrame = 1;
    interp = 0.0f;
}

DynamicModel::~DynamicModel()
{
    freeModel();

    for (int i = 0; i < mdl.header.num_frames; ++i)
    {
        delete[] vertData[i];
    }

    delete[] animVerts;
}

GLvoid DynamicModel::readTexture(const GLchar * filename)
{
    texture = TextureManagerGL::get()->createTexture(filename, GL_REPEAT);
}

GLvoid DynamicModel::readMD2Model(const GLchar *filename, GLboolean bound)
{
    FILE *fp;
    int i;

    fopen_s(&fp, filename, "rb");
    if (!fp)
    {
        fprintf(stderr, "Error: couldn't open \"%s\"!\n", filename);
        return;
    }

    fread(&mdl.header, 1, sizeof(struct md2_header_t), fp);

    if ((mdl.header.ident != 844121161) || (mdl.header.version != 8))
    {
        fprintf(stderr, "Error: bad version or identifier\n");
        fclose(fp);
        return;
    }

    mdl.skins = (struct md2_skin_t *)
        malloc(sizeof(struct md2_skin_t) * mdl.header.num_skins);
    mdl.texcoords = (struct md2_texCoord_t *)
        malloc(sizeof(struct md2_texCoord_t) * mdl.header.num_st);
    mdl.triangles = (struct md2_triangle_t *)
        malloc(sizeof(struct md2_triangle_t) * mdl.header.num_tris);
    mdl.frames = (struct md2_frame_t *)
        malloc(sizeof(struct md2_frame_t) * mdl.header.num_frames);
    mdl.glcmds = (int *)malloc(sizeof(int) * mdl.header.num_glcmds);

    fseek(fp, mdl.header.offset_skins, SEEK_SET);
    fread(mdl.skins, sizeof(struct md2_skin_t), mdl.header.num_skins, fp);

    fseek(fp, mdl.header.offset_st, SEEK_SET);
    fread(mdl.texcoords, sizeof(struct md2_texCoord_t), mdl.header.num_st, fp);

    fseek(fp, mdl.header.offset_tris, SEEK_SET);
    fread(mdl.triangles, sizeof(struct md2_triangle_t), mdl.header.num_tris, fp);

    fseek(fp, mdl.header.offset_glcmds, SEEK_SET);
    fread(mdl.glcmds, sizeof(int), mdl.header.num_glcmds, fp);

    fseek(fp, mdl.header.offset_frames, SEEK_SET);
    for (i = 0; i < mdl.header.num_frames; ++i)
    {
        mdl.frames[i].verts = (struct md2_vertex_t *)
            malloc(sizeof(struct md2_vertex_t) * mdl.header.num_vertices);

        fread(mdl.frames[i].scale, sizeof(md2vec3), 1, fp);
        fread(mdl.frames[i].translate, sizeof(md2vec3), 1, fp);
        fread(mdl.frames[i].name, sizeof(char), 16, fp);
        fread(mdl.frames[i].verts, sizeof(struct md2_vertex_t),
            mdl.header.num_vertices, fp);
    }

    fclose(fp);

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
            tex_coords.push_back((GLfloat)mdl.texcoords[mdl.triangles[i].st[j]].s / mdl.header.skinwidth);
            tex_coords.push_back((GLfloat)mdl.texcoords[mdl.triangles[i].st[j]].t / mdl.header.skinheight);

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
    for (k = 0; k < mdl.header.num_frames; ++k) {
        verts = new GLfloat[vertDataSize];
        pframe = &mdl.frames[k];
        for (i = 0; i < mdl.header.num_tris; ++i)
        {
            // For each vertex 
            for (j = 0; j < 3; ++j)
            {
                // get current vertex
                pvert = &pframe->verts[mdl.triangles[i].vertex[j]];
                verts[(i * 3 + j) * 3] = GLfloat(pframe->scale[0] * pvert->v[0] + pframe->translate[0]);
                verts[(i * 3 + j) * 3 + 1] = GLfloat(pframe->scale[1] * pvert->v[1] + pframe->translate[1]);
                verts[(i * 3 + j) * 3 + 2] = GLfloat(pframe->scale[2] * pvert->v[2] + pframe->translate[2]);
            }
        }
        vertData.push_back(verts);
    }

    animVerts = new GLfloat[vertDataSize];
    memcpy(animVerts, vertData[0], vertDataSize * sizeof(float));

    program = ShaderManagerGL::get()->getShader("data/shaders/model.vert", "data/shaders/model.frag");


    // generate and set up a VAO for the mesh
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    std::cout << tex_coords.size() << std::endl;

    int numVerts = mdl.header.num_tris * 3;

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), vertData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * numVerts * sizeof(GLfloat), norms.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, 2 * numVerts * sizeof(GLfloat), tex_coords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    matrix.perspective(70.0f, vec2(16, 9), vec2(0.1, 1000));

    if (bound)
    {
        SurfaceBuilder * builder = new SurfaceBuilder();
        for (unsigned int i = 0; i < vertData.size(); i++) {
            aiVector3D point;

            point.x = vertData[i][0];
            point.y = vertData[i][1];
            point.z = vertData[i][2];

            builder->pushPoint(point);
        }

        builder->ignore();
        builder->pushSurface(&matrix);
        builder->endOfMesh(0);
        boundingBox = builder->release();
        delete builder;
    }

    freeModel();
}

GLvoid DynamicModel::onUpdate()
{

}

void DynamicModel::render(mat4 m)
{
    program->use();
    program->setMatrix("Projection", matrix.getProjection());
    program->setMatrix("NormalMat", glm::transpose(m));
    program->setMatrix("Model", matrix.getModel());
    program->setMatrix("View", matrix.getView());

    glBindVertexArray(vertexArray);
    glBindTexture(GL_TEXTURE_2D, texture->textureID);
    glDrawArrays(GL_TRIANGLES, 0, getVertDataCount());
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

    program->release();
}

void DynamicModel::freeModel()
{
    int i;

    if (mdl.skins)
    {
        free(mdl.skins);
        mdl.skins = NULL;
    }

    if (mdl.texcoords)
    {
        free(mdl.texcoords);
        mdl.texcoords = NULL;
    }

    if (mdl.triangles)
    {
        free(mdl.triangles);
        mdl.triangles = NULL;
    }

    if (mdl.glcmds)
    {
        free(mdl.glcmds);
        mdl.glcmds = NULL;
    }

    if (mdl.frames)
    {
        for (i = 0; i < mdl.header.num_frames; ++i)
        {
            free(mdl.frames[i].verts);
            mdl.frames[i].verts = NULL;
        }

        free(mdl.frames);
        mdl.frames = NULL;
    }
}

void DynamicModel::animate(GLuint animation, GLfloat dt)
{
    GLint start = animFrameList[animation * 2];
    GLint end = animFrameList[animation * 2 + 1];

    if ((currentFrame < start) || (currentFrame > end))
    {
        currentFrame = start;
        nextFrame = start + 1;
    }

    interp += dt;

    if (interp >= 1.0f)
    {
        interp = 0.0f;
        currentFrame = nextFrame;
        nextFrame++;

        if (nextFrame >= end + 1)
        {
            nextFrame = start;
        }
    }

    if (interp == 0.0f)
    {
        memcpy(animVerts, vertData[currentFrame], vertDataSize * sizeof(float));
    }
    else
    {
        for (int i = 0; i < vertDataSize; i++)
        {
            animVerts[i] = vertData[currentFrame][i];
            animVerts[i] += interp*(vertData[nextFrame][i] - vertData[currentFrame][i]);
        }
    }

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, getVertDataSize() * sizeof(GLfloat), getAnimVerts(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

GLvoid DynamicModel::animate(float dt)
{
    animate(currentAnim, dt);
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
    return currentAnim;
}

GLfloat* DynamicModel::getAnimVerts()
{
    return animVerts;
}

GLvoid DynamicModel::prepare()
{
}

Surface* DynamicModel::getSurface()
{
    return boundingBox;
}

bool DynamicModel::isDynamic()
{
    return true;
}

MatrixGL* DynamicModel::getMatrix()
{
    return &matrix;
}