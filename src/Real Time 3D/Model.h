

#pragma once

#include "MinimapGL.h"

class Model
{
public:
    virtual void onUpdate() = 0;
    virtual void prepare() = 0;
    virtual bool isDynamic() = 0;
    virtual MatrixGL* getMatrix() = 0;
};