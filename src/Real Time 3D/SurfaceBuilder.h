
#pragma once

#include "MajorInclude.h"
#include "Surface.h"

class SurfaceBuilder
{
    MatrixGL* matrix;
    Surface* surface;

    aiVector3D point;
    aiVector3D size;

    bool ignoreArea;
public:

    SurfaceBuilder();
    ~SurfaceBuilder();

    void pushSurface(MatrixGL *);
    void pushPoint(aiVector3D);
    void endOfMesh(int);
    void ignore();

    Surface* release();
};