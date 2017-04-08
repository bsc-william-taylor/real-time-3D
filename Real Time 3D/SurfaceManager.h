
#pragma once

#include "ICamera.h"
#include "Surface.h"

class SurfaceManager
{
private:

	static SurfaceManager * m_pInstance;
	vector<Surface *> m_pSurfaces;

	Surface * m_pCameraSurface;
	ICamera * m_pSceneCamera;

public:

	SurfaceManager();
	~SurfaceManager();

	vector<Surface *>& getSurfaces();
	static SurfaceManager * get();

	void PushCameraObject(Surface *);
	void PushCamera(ICamera *);
	void PushSurface(Surface *);
	void CheckForCollision();
	void RenderSurfaces();
};