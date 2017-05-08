
#pragma once

#include "SubSurface.h"
#include "ShaderManagerGL.h"
#include "MinimapGL.h"

class Surface
{
    ProgramGL* program;
    MatrixGL* matrix;

    vector<SubSurface *> surfaces;
    vector<vec3> positions;
    vector<vec3> size;
    vector<int> maxValues;

    GLuint vertexBuffer;
    GLuint vertexArray;
    GLuint count;

    bool firstTime;
    bool shouldDraw;
public:
    Surface();
    ~Surface();

    bool checkForCollision(SubSurface *, Camera *);
    bool checkForCollision(Camera *);

    vector<SubSurface *>& getSubSurface();

    void setSize(vec3, vec3);
    void onUpdate(MatrixGL*);
    void addMaxMeshes(int);
    void disable();
    void enable();
    void render();
    void setup();

    MatrixGL* getMatrix();
};