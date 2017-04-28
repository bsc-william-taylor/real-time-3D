
#include "SurfaceManager.h"
#include "Win32Codes.h"
#include "DemoScene.h"
#include "Demo.h"

DemoScene::DemoScene()
    : m_Loaded(false)
{
    m_pCamera = new ThirdPersonCamera();
    m_pPlayer = new DynamicModel();
    m_pCity = new StaticModel();

    m_pEffects = new GL_PostProcessor();
    m_Overlaymap = new GL_MapOverlay();
    m_Heightmap = new GL_Heightmap();
    m_pRenderer = new GL_Renderer();
    m_pMiniMap = new GL_Minimap();
    m_pSkybox = new GL_Skybox();
}

DemoScene::~DemoScene()
{
    SAFE_RELEASE(m_pRenderer);
    SAFE_RELEASE(m_pEffects);
    SAFE_RELEASE(m_pCamera);
    SAFE_RELEASE(m_pSkybox);
    SAFE_RELEASE(m_pMiniMap);
}

void DemoScene::update()
{
    if (Demo::demoSettings.enableFx)
    {
        m_pEffects->Enable();
    }

    m_pRenderer->LoadIdentity();
    m_pRenderer->update();

    m_pPlayer->getMatrix()->LoadIdenditity();
    m_pPlayer->getMatrix()->Rotate(RAIDAN(90), vec3(0.0, 0.0, 1.0));
    m_pPlayer->getMatrix()->Rotate(RAIDAN(90), vec3(0.0, 1.0, 0.0));
    m_pPlayer->getMatrix()->Scale(vec3(0.03, 0.03, 0.03));


    SurfaceManager::get()->CheckForCollision();
    m_pCamera->update(true);
}

void DemoScene::render()
{
    m_pRenderer->render();
    m_pAudioPlayer->Stream();

    if (Demo::demoSettings.enableFx)
    {
        m_pEffects->execute();
    }

    if (Demo::demoSettings.showBoundingBoxes)
    {
        SurfaceManager::get()->RenderSurfaces();
    }

    m_pRenderer->Render2D(GL_FALSE);
    m_pOptions->render(m_pRenderer);
    m_pQuit->render(m_pRenderer);

    m_pRenderer->Render3D(Demo::demoSettings.wireframeEnabled);
    m_pMiniMap->RenderToBuffer();
    m_pRenderer->LoadIdentity();
    m_pRenderer->update();
    m_pCamera->update(GL_FALSE);
    m_pRenderer->render();
    m_pMiniMap->RenderToScreen();
    m_pCamera->Reset();
}

void DemoScene::keyPress(int Key, int State)
{
    m_pCamera->keyPress(Key, State);

    if (Key == ENTER && State == PRESSED) 
    {
        SceneManager::get()->SwitchTo(2);
    }

    if (Key == ESCAPE && State == RELEASED) 
    {
        PostQuitMessage(0);
    }
}

void DemoScene::motion(float pos_x, float pos_y)
{
    m_pCamera->motion(pos_x, pos_y);
}

void DemoScene::mousePress(int Key, int State, int x, int y)
{
    if (m_pOptions->MouseState(Key, State, x, y)) 
    {
        SceneManager::get()->SwitchTo(2);
    }

    if (m_pQuit->MouseState(Key, State, x, y)) 
    {
        PostQuitMessage(0);
    }
}

void DemoScene::enter()
{
    if (!m_Loaded)
    {
        m_pOptions = new Button();
        m_pQuit = new Button();

        m_pOptions->SetPosition("Options", vec2(1050, 610), vec2(200, 50));
        m_pOptions->getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
        m_pQuit->SetPosition("Quit", vec2(1050, 10), vec2(200, 50));
        m_pQuit->getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));

        m_pEffects->Initialise(1280, 720);
        m_pSkybox->Folder("data/skybox/");
        m_pSkybox->SetDistance(10000);
        m_pSkybox->Setup();

        m_Overlaymap->SetOverlayImage("data/img/road.jpg");
        m_Overlaymap->SetOverlayMap("data/img/pathway.png");
        m_Heightmap->setHeightMap("data/img/heightmap.png");
        m_Heightmap->setMapTexture("data/img/grass.png");
        m_Heightmap->PushOverlay(m_Overlaymap);

        m_Loaded = !m_Loaded;

        setupGraphics();
        setupAudio();
    }
}

void DemoScene::setupGraphics()
{
    m_pCity->Load("data/models/Metro 1.3ds", "data/models/", true);
    m_pCity->SetScale(0.75f);
    m_pCity->Rotate(RAIDAN(90), vec3(-1, 0, 0));
    m_pCity->Translate(vec3(-5.0, -2.5, -15));

    m_pPlayer->ReadTexture("data/models/pac3D.bmp");
    m_pPlayer->ReadMD2Model("data/models/pac3D.md2", true);

    m_pRenderer->PushHeightmap(m_Heightmap);
    m_pRenderer->PushSkybox(m_pSkybox);
    m_pRenderer->PushModel(m_pCity);
    m_pRenderer->Prepare();
    m_pRenderer->Perspective(70, vec2(16, 9), vec2(0.1, 10000));
    m_pRenderer->setSurfaceSize(vec4(0, 0, 1280, 720));

    m_pCamera->setPlayerModel(m_pPlayer);
    m_pCamera->Initialise(m_pRenderer);
    m_pMiniMap->Initialise(m_pCamera);

    SurfaceManager::get()->PushCamera(m_pCamera);
    SurfaceManager::get()->PushCameraObject(m_pPlayer->getSurface());
}

void DemoScene::setupAudio()
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