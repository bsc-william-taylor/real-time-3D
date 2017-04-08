
#include "SurfaceManager.h"

SurfaceManager * SurfaceManager::m_pInstance = 0;

SurfaceManager::SurfaceManager()
{
	m_pCameraSurface = NULL;
	m_pSceneCamera = NULL;
}

SurfaceManager::~SurfaceManager()
{
	for(auto i = m_pSurfaces.begin(); i != m_pSurfaces.end(); ++i)
	{
		SAFE_RELEASE((*i));
	}
}

vector<Surface *>& SurfaceManager::getSurfaces()
{
	return m_pSurfaces;
}

SurfaceManager * SurfaceManager::get()
{
	if(m_pInstance == 0)
	{
		m_pInstance = new SurfaceManager();
	}

	return m_pInstance;
}

void SurfaceManager::PushSurface(Surface * surface)
{
	if(surface != NULL)
	{
		m_pSurfaces.push_back(surface);
	}
}

void SurfaceManager::PushCamera(ICamera * camera)
{
	m_pSceneCamera = camera;
}

void SurfaceManager::PushCameraObject(Surface * surface)
{
	this->m_pCameraSurface = surface;
}

void SurfaceManager::CheckForCollision()
{
	if(m_pSceneCamera != NULL)
	{
		SubSurface * surface = m_pCameraSurface->getSubSurface()[0];
		for(int i = 0; i < m_pSurfaces.size(); ++i)
		{
			if(m_pSurfaces[i]->CheckForCollision(surface, m_pSceneCamera) ||
			   m_pSurfaces[i]->CheckForCollision(m_pSceneCamera))
			{
				m_pSceneCamera->CancelMovement();
				break;
			}			
		}
	}
}

void SurfaceManager::RenderSurfaces()
{
	for(auto i = m_pSurfaces.begin(); i != m_pSurfaces.end(); ++i)
	{
		(*i)->Render();
	}
}