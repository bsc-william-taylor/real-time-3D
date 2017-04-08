
#pragma once

#define GLM_FORCE_RADIANS

#include "Win32Header.h"

#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/glm/gtc/type_ptr.hpp"
#include "lib/glm/glm.hpp"

#include "include/freeimage/freeimage.h"
#include "include/assimp/Importer.hpp"
#include "include/assimp/PostProcess.h"
#include "include/assimp/Scene.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#pragma comment(lib, "lib/freeimage/freeimage.lib")
#pragma comment(lib, "lib/assimp/assimp.lib")
#pragma comment(lib, "freetype252_D.lib")
#pragma comment(lib, "glew32.lib")

#define PI 3.14159265359f
#define RAIDAN(v)(v / 180.0f) * PI

using namespace glm;

using std::vector;
using std::map;

#define GET(var) \
{ \
	if(var) return var; else return 0; \
} 

#define SET(var, value) \
{ \
	if(value) var = value; \
} 