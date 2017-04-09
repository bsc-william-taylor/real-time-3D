

#pragma once

#include "GL_Matrix.h"

class IModel 
{
public:

	 virtual void Update() = 0;
	 virtual void Prepare() = 0;
	 virtual bool isDynamic() = 0;

	 virtual GL_Matrix *getMatrix() = 0;
};