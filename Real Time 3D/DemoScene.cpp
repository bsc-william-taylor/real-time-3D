
#include "Win32Codes.h"
#include "SurfaceManager.h"
#include "DemoScene.h"

DemoScene::DemoScene()
	: m_pCamera(new ThirdPersonCamera()),
	  m_pEffects(new GL_PostProcessor()),
	  m_Overlaymap(new GL_MapOverlay()),
      m_Heightmap(new GL_Heightmap()),
	  m_pRenderer(new GL_Renderer()),
	  m_pMiniMap(new GL_Minimap()),
	  m_pSkybox(new GL_Skybox()),
	  m_pPlayer(new DynamicModel()),
	  m_pCity(new StaticModel())
{
	m_Loaded = false;
}

DemoScene::~DemoScene()
{
	SAFE_RELEASE(m_pRenderer);
	SAFE_RELEASE(m_pEffects);
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pSkybox);
}

void DemoScene::Update()
{
	m_pEffects->Enable();
	m_pRenderer->LoadIdentity();
	m_pRenderer->Update();

	m_pPlayer->getMatrix()->LoadIdenditity();
	m_pPlayer->getMatrix()->Rotate(RAIDAN(90), vec3(0.0, 0.0, 1.0));
	m_pPlayer->getMatrix()->Rotate(RAIDAN(90), vec3(0.0, 1.0, 0.0));
	m_pPlayer->getMatrix()->Scale(vec3(0.03, 0.03, 0.03));

	SurfaceManager::get()->CheckForCollision();

	m_pCamera->Update();
}

void DemoScene::Render()
{
	m_pAudioPlayer->Stream();
	m_pRenderer->Render();
	m_pEffects->Execute();
	
	m_pMiniMap->RenderToBuffer();
	m_pRenderer->LoadIdentity();
	m_pRenderer->Update();

	m_pCamera->Update();
	m_pRenderer->Render();
	m_pMiniMap->RenderToScreen();
	m_pCamera->Reset();
}

void DemoScene::KeyPress(int Key, int State)
{
	m_pCamera->KeyPress(Key, State);

	if(Key == ENTER && State == PRESSED) {
		SceneManager::get()->SwitchTo(2);
	}

	if(Key == ESCAPE && State == RELEASED) {
		PostQuitMessage(0);
	}
}

void DemoScene::Motion(float pos_x, float pos_y)
{
	m_pCamera->Motion(pos_x, pos_y);
}

void DemoScene::Enter()
{
	if(!m_Loaded)
	{
		m_pSkybox->Folder("data/skybox/");
		m_pSkybox->SetDistance(10000);
		m_pSkybox->Setup();

		m_Overlaymap->SetOverlayImage("data/img/road.jpg");
		m_Overlaymap->SetOverlayMap("data/img/pathway.png");
		m_Heightmap->setHeightMap("data/img/heightmap.png");
		m_Heightmap->setMapTexture("data/img/grass.png");
		m_Heightmap->PushOverlay(m_Overlaymap);

		m_Loaded = !m_Loaded;
		SetupGraphics();
		SetupAudio();
	}
}

void DemoScene::SetupGraphics()
{
	m_pCity->Load("data/models/Metro 1.3ds", "data/models/", true);
	m_pCity->SetScale(0.75f);
	m_pCity->Rotate(RAIDAN(90), vec3(-1, 0, 0));
	m_pCity->Translate(vec3(-5.0, -2.5, -15));

	m_pPlayer->ReadMD2Model("data/models/yoshi.md2", true);
	m_pPlayer->ReadTexture("data/models/yoshi.bmp");
	
	m_pRenderer->PushHeightmap(m_Heightmap);
	m_pRenderer->PushSkybox(m_pSkybox);
	m_pRenderer->PushModel(m_pCity);
	m_pRenderer->Prepare();

	m_pRenderer->Perspective(70, vec2(16, 9), vec2(0.1, 10000));
	m_pRenderer->setSurfaceSize(vec4(0, 0, 1600, 900));

	m_pCamera->setPlayerModel(m_pPlayer);
	m_pCamera->Initialise(m_pRenderer);
	m_pMiniMap->Initialise(m_pCamera);
	m_pEffects->Initialise(1600, 900);

	SurfaceManager::get()->PushCameraObject(m_pPlayer->getSurface());
	SurfaceManager::get()->PushCamera(m_pCamera);
}

void DemoScene::SetupAudio()
{
	m_pMusic = new AudioObject();
	m_pMusic->SetAudioSource("data/audio/PianoMono.mp3");
	m_pMusic->SetPosition(vec3(-1, -1, -1));
	m_pMusic->Play();

	m_pAudioPlayer = new AudioPlayer();
	m_pAudioPlayer->PushClip(m_pMusic);
	m_pAudioPlayer->Set3DCamera(m_pCamera);
	m_pAudioPlayer->Set3DRenderer(m_pRenderer);
	m_pAudioPlayer->Initialise();
}