
#include "SurfaceManager.h"

SurfaceManager * SurfaceManager::manager = nullptr;

SurfaceManager::SurfaceManager()
{
    cameraSurface = nullptr;
    sceneCamera = nullptr;
}

SurfaceManager::~SurfaceManager()
{
    for (auto i = surfaces.begin(); i != surfaces.end(); ++i)
    {
        SAFE_RELEASE(*i);
    }
}

vector<Surface *>& SurfaceManager::getSurfaces()
{
    return surfaces;
}

SurfaceManager * SurfaceManager::get()
{
    if (manager == nullptr)
    {
        manager = new SurfaceManager();
    }

    return manager;
}

void SurfaceManager::pushSurface(Surface * surface)
{
    if (surface != nullptr)
    {
        surfaces.push_back(surface);
    }
}

void SurfaceManager::pushCamera(Camera * camera)
{
    sceneCamera = camera;
}

void SurfaceManager::pushCameraObject(Surface * surface)
{
    cameraSurface = surface;
}

void SurfaceManager::checkForCollision()
{
    if (cameraSurface != nullptr)
    {
        auto& cameraSurfaces = cameraSurface->getSubSurface();

        if (!cameraSurfaces.empty())
        {
            auto surface = cameraSurfaces.front();

            for (int i = 0; i < surfaces.size(); ++i)
            {
                if (surfaces[i]->checkForCollision(surface, sceneCamera) ||
                    surfaces[i]->checkForCollision(sceneCamera))
                {
                    sceneCamera->cancelMovement();
                    break;
                }
            }
        }
    }
}

void SurfaceManager::renderSurfaces()
{
    for (int i = 0; i < surfaces.size(); i++)
    {
        surfaces[i]->render();
    }
}