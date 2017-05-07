
#include "SurfaceManager.h"
#include "SurfaceBuilder.h"

SurfaceBuilder::SurfaceBuilder() :
    surface(new Surface())
{
    point = aiVector3D(0, 0, 0);
    size = aiVector3D(0, 0, 0);
    ignoreArea = false;
}

SurfaceBuilder::~SurfaceBuilder()
{
    surface->onUpdate(matrix);
    SurfaceManager::get()->pushSurface(surface);
}

void SurfaceBuilder::pushPoint(aiVector3D p)
{
    if (point == aiVector3D(0, 0, 0))
    {
        point = p;
        size = p;
    }

    if (p.x < point.x)
        point.x = p.x;
    if (p.y < point.y)
        point.y = p.y;
    if (p.z < point.z)
        point.z = p.z;

    if (size.x < p.x)
        size.x = p.x;
    if (size.y < p.y)
        size.y = p.y;
    if (size.z < p.z)
        size.z = p.z;
}

Surface * SurfaceBuilder::release()
{
    Surface * temp = surface;
    return temp;
}

void SurfaceBuilder::pushSurface(MatrixGL * matrix)
{
    GLfloat x = size.x - point.x;
    GLfloat y = size.y - point.y;
    GLfloat z = size.z - point.z;
    GLfloat area = (x*x) + (y*y) + (z*z);

    this->matrix = matrix;

    if (ignoreArea || area >= 150.0 && area <= 5000.0)
    {
        vec3 glmPosition = vec3(point.x, point.y, point.z);
        vec3 glmSize = vec3(size.x, size.y, size.z);
        surface->setSize(glmPosition, glmSize);
        surface->enable();
    }

    point = aiVector3D(0, 0, 0);
    size = aiVector3D(0, 0, 0);
}

void SurfaceBuilder::endOfMesh(int i)
{
    surface->addMaxMeshes(i);
}

void SurfaceBuilder::ignore()
{
    ignoreArea = true;
}