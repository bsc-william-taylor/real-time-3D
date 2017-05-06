
#include "SurfaceManager.h"
#include "Win32Codes.h"
#include "DemoScene.h"
#include "Demo.h"

DemoScene::DemoScene()
    : loaded(false)
{
    camera = new ThirdPersonCamera();
    player = new DynamicModel();
    city = new StaticModel();

    effects = new GL_PostProcessor();
    overlaymap = new GL_MapOverlay();
    heightmap = new GL_Heightmap();
    renderer = new GL_Renderer();
    miniMap = new GL_Minimap();
    skybox = new GL_Skybox();
}

DemoScene::~DemoScene()
{
    SAFE_RELEASE(renderer);
    SAFE_RELEASE(effects);
    SAFE_RELEASE(camera);
    SAFE_RELEASE(skybox);
    SAFE_RELEASE(miniMap);
}

void DemoScene::update()
{
    if (Demo::demoSettings.enableFx)
    {
        effects->Enable();
    }

    renderer->LoadIdentity();
    renderer->update();

    player->getMatrix()->LoadIdenditity();
    player->getMatrix()->Rotate(RAIDAN(90), vec3(0.0, 0.0, 1.0));
    player->getMatrix()->Rotate(RAIDAN(90), vec3(0.0, 1.0, 0.0));
    player->getMatrix()->Scale(vec3(0.03, 0.03, 0.03));


    SurfaceManager::get()->CheckForCollision();
    camera->update(true);
}

void DemoScene::render()
{
    renderer->render();
    audioPlayer->Stream();

    if (Demo::demoSettings.enableFx)
    {
        effects->execute();
    }

    if (Demo::demoSettings.showBoundingBoxes)
    {
        SurfaceManager::get()->RenderSurfaces();
    }

    renderer->Render2D(GL_FALSE);
    options->render(renderer);
    quit->render(renderer);

    renderer->Render3D(Demo::demoSettings.wireframeEnabled);
    miniMap->RenderToBuffer();
    renderer->LoadIdentity();
    renderer->update();
    camera->update(GL_FALSE);
    renderer->render();
    miniMap->RenderToScreen();
    camera->Reset();
}

void DemoScene::keyPress(int Key, int State)
{
    camera->keyPress(Key, State);

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
    camera->motion(pos_x, pos_y);
}

void DemoScene::mousePress(int Key, int State, int x, int y)
{
    if (options->MouseState(Key, State, x, y)) 
    {
        SceneManager::get()->SwitchTo(2);
    }

    if (quit->MouseState(Key, State, x, y)) 
    {
        PostQuitMessage(0);
    }
}

void DemoScene::enter()
{
    if (!loaded)
    {
        options = new Button();
        quit = new Button();

        options->SetPosition("Options", vec2(1050, 610), vec2(200, 50));
        options->getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
        quit->SetPosition("Quit", vec2(1050, 10), vec2(200, 50));
        quit->getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));

        effects->Initialise(1280, 720);
        skybox->Folder("data/skybox/");
        skybox->SetDistance(10000);
        skybox->Setup();

        overlaymap->SetOverlayImage("data/img/road.jpg");
        overlaymap->SetOverlayMap("data/img/pathway.png");
        heightmap->setHeightMap("data/img/heightmap.png");
        heightmap->setMapTexture("data/img/grass.png");
        heightmap->PushOverlay(overlaymap);

        loaded = !loaded;

        setupGraphics();
        setupAudio();
    }
}

void DemoScene::setupGraphics()
{
    city->Load("data/models/Metro 1.3ds", "data/models/", true);
    city->SetScale(0.75f);
    city->Rotate(RAIDAN(90), vec3(-1, 0, 0));
    city->Translate(vec3(-5.0, -2.5, -15));

    player->ReadTexture("data/models/pac3D.bmp");
    player->ReadMD2Model("data/models/pac3D.md2", true);

    renderer->PushHeightmap(heightmap);
    renderer->PushSkybox(skybox);
    renderer->PushModel(city);
    renderer->Prepare();
    renderer->Perspective(70, vec2(16, 9), vec2(0.1, 10000));
    renderer->setSurfaceSize(vec4(0, 0, 1280, 720));

    camera->setPlayerModel(player);
    camera->Initialise(renderer);
    miniMap->Initialise(camera);

    SurfaceManager::get()->PushCamera(camera);
    SurfaceManager::get()->PushCameraObject(player->getSurface());
}

void DemoScene::setupAudio()
{
    music = new AudioObject();
    music->SetAudioSource("data/audio/PianoMono.mp3");
    music->SetPosition(vec3(-1, -1, -1));
    music->Play();

    audioPlayer = new AudioPlayer();
    audioPlayer->PushClip(music);
    audioPlayer->Set3DCamera(camera);
    audioPlayer->Set3DRenderer(renderer);
    audioPlayer->Initialise();
}