
#include "SubSurface.h"

SubSurface::SubSurface()
{
    positionCalculated = false;
    position = vec3(0, 0, 0);
    size = vec3(0, 0, 0);
}

SubSurface::~SubSurface()
{
}

bool SubSurface::collisionTest(MatrixGL * matrix, vec3 position, vec3 size)
{
    auto mat = matrix->getProjection() * matrix->getModel();

    if (collisionTest(mat, position))
    {
        return true;
    }

    if (collisionTest(mat, size))
    {
        return true;
    }

    return false;
}

bool SubSurface::collisionTest(mat4 mat, vec3 position)
{
    if (!positionCalculated)
    {
        this->position = vec3(mat * (vec4(this->position, 1.0)));
        this->size = vec3(mat * (vec4(this->size, 1.0)));
        positionCalculated = true;
    }

    if (position.x >= this->position.x && position.x <= size.x)
    {
        if (position.z >= this->position.z && position.z <= size.z)
        {
            if (position.y >= this->position.y && position.y <= size.y)
            {
                return true;
            }
        }
    }

    return false;
}

vec3 SubSurface::getMeshPosition()
{
    return position;
}

vec3 SubSurface::getMeshSize()
{
    return size;
}

void SubSurface::printSurfaceData()
{
    std::cout << " : " << position.x << " : " << position.y << " : " << position.z << std::endl;
    std::cout << " : " << size.x << " : " << size.y << " : " << size.z << std::endl;
}

bool SubSurface::passPoint(vec3 p, vec3 s)
{
    if (position == vec3(0, 0, 0))
    {
        position = p;
        size = s;
        return true;
    }

    if (isConnected(p, s))
    {
        if (p.x < position.x)
            position.x = p.x;
        if (p.y < position.y)
            position.y = p.y;
        if (p.z < position.z)
            position.z = p.z;

        if (s.x > size.x)
            size.x = s.x;
        if (s.y > size.y)
            size.y = s.y;
        if (s.z > size.z)
            size.z = s.z;

        return true;
    }

    return false;
}

bool SubSurface::isConnected(vec3 p, vec3 s)
{
    if (p.x == position.x || p.y == position.y || p.z == position.z)
        return true;
    if (s.x == size.x || s.y == size.y || s.z == size.z)
        return true;
    return false;
}
