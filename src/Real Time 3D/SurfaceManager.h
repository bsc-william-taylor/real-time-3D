
#pragma once

#include "Camera.h"
#include "Surface.h"

class SurfaceManager
{
    static SurfaceManager* manager;
    vector<Surface*> surfaces;
    Surface* cameraSurface;
    Camera* sceneCamera;
public:
    SurfaceManager();
    ~SurfaceManager();

    vector<Surface*>& getSurfaces();

    void pushCameraObject(Surface*);
    void pushCamera(Camera*);
    void pushSurface(Surface*);
    void checkForCollision();
    void renderSurfaces();

    static SurfaceManager* get();
};