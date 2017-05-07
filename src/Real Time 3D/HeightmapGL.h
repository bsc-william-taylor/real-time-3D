
#pragma once

#include "TextureManagerGL.h"
#include "MapOverlayGL.h"
#include "TextureGL.h"

class HeightmapGL
{
    SpriteGL* heightmap;
    ProgramGL* shader;
    SpriteGL* texture;
    MatrixGL* matrix;

    vector<MapOverlayGL*> overlays;
    vector<vec3> positions;
    vector<vec3> overlay;
    vector<vec3> normals;
    vector<vec3> uvs;

    GLuint vertexArrayObject;
    GLuint positionBuffer;
    GLuint overlayBuffer;
    GLuint normalBuffer;
    GLuint uvBuffer;

    std::string textureFilename;
    std::string filename;
    int scale;
public:
    HeightmapGL();
    ~HeightmapGL();

    GLfloat getMapY(vec3);
    GLfloat getY(GLuint, GLuint);


    GLvoid PushOverlay(MapOverlayGL *);
    GLvoid prepare();
    GLvoid onUpdate();
    GLvoid Draw();

    GLvoid setMapTexture(std::string);
    GLvoid setHeightMap(std::string);
    GLvoid setScale(GLuint);

    ProgramGL * getProgram();
    MatrixGL * getMatrix();

    vec3 getNormal(vec3, vec3, vec3);
};