
#include "SurfaceManager.h"
#include "Win32Codes.h"
#include "DemoScene.h"
#include "Demo.h"

DemoScene::DemoScene()
    : loaded(false)
{
}

DemoScene::~DemoScene()
{
}

void DemoScene::onUpdate()
{
    if (Demo::demoSettings.enableFx)
    {
        effects.enable();
    }

    renderer.LoadIdentity();
    renderer.onUpdate();

    player.getMatrix()->loadIdenditity();
    player.getMatrix()->rotate(RAIDAN(90), vec3(0.0, 0.0, 1.0));
    player.getMatrix()->rotate(RAIDAN(90), vec3(0.0, 1.0, 0.0));
    player.getMatrix()->scale(vec3(0.03, 0.03, 0.03));

    SurfaceManager::get()->checkForCollision();
    camera.onUpdate(true);
}

void DemoScene::render()
{
    renderer.render();
    audioPlayer.stream();

    if (Demo::demoSettings.enableFx)
    {
        effects.execute();
    }

    if (Demo::demoSettings.showBoundingBoxes)
    {
        SurfaceManager::get()->renderSurfaces();
    }

    renderer.render2D(GL_FALSE);
    options.render(&renderer);
    quit.render(&renderer);

    renderer.render3D(Demo::demoSettings.wireframeEnabled);
    miniMap.renderToBuffer();
    renderer.LoadIdentity();
    renderer.onUpdate();
    camera.onUpdate(GL_FALSE);
    renderer.render();
    miniMap.renderToScreen();
    camera.Reset();
}

void DemoScene::onKeyPress(int Key, int State)
{
    camera.onKeyPress(Key, State);

    if (Key == ENTER && State == PRESSED)
    {
        SceneManager::get()->switchTo(2);
    }

    if (Key == ESCAPE && State == RELEASED)
    {
        PostQuitMessage(0);
    }
}

void DemoScene::onMotion(float pos_x, float pos_y)
{
    camera.onMotion(pos_x, pos_y);
}

void DemoScene::mousePress(int Key, int State, int x, int y)
{
    if (options.mouseState(Key, State, x, y))
    {
        SceneManager::get()->switchTo(2);
    }

    if (quit.mouseState(Key, State, x, y))
    {
        PostQuitMessage(0);
    }
}

void DemoScene::enter()
{
    if (!loaded)
    {
        options.setPosition("Options", vec2(1050, 610), vec2(200, 50));
        options.getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));
        quit.setPosition("Quit", vec2(1050, 10), vec2(200, 50));
        quit.getTexture()->setShade(vec4(1.0, 0.0, 0.0, 1.0));

        effects.initialise(1280, 720);
        skybox.folder("data/skybox/");
        skybox.setDistance(10000);
        skybox.setup();

        overlaymap.setOverlayImage("data/img/road.jpg");
        overlaymap.setOverlayMap("data/img/pathway.png");
        heightmap.setHeightMap("data/img/heightmap.png");
        heightmap.setMapTexture("data/img/grass.png");
        heightmap.PushOverlay(&overlaymap);

        loaded = !loaded;

        setupGraphics();
        setupAudio();
    }
}

void DemoScene::setupGraphics()
{
    city.load("data/models/Metro 1.3ds", "data/models/", true);
    city.setScale(0.75f);
    city.setRotate(RAIDAN(90), vec3(-1, 0, 0));
    city.setTranslate(vec3(-5.0, -2.5, -15));

    player.readTexture("data/models/pac3D.bmp");
    player.readMD2Model("data/models/pac3D.md2", true);

    renderer.pushHeightmap(&heightmap);
    renderer.pushSkybox(&skybox);
    renderer.pushModel(&city);
    renderer.prepare();
    renderer.perspective(70, vec2(16, 9), vec2(0.1, 10000));
    renderer.setSurfaceSize(vec4(0, 0, 1280, 720));

    camera.setPlayerModel(&player);
    camera.initialise(&renderer);
    miniMap.initialise(&camera);

    SurfaceManager::get()->pushCamera(&camera);
    SurfaceManager::get()->pushCameraObject(player.getSurface());
}

void DemoScene::setupAudio()
{
    music.setAudioSource("data/audio/PianoMono.mp3");
    music.setPosition(vec3(-1, -1, -1));
    music.play();

    audioPlayer.pushClip(&music);
    audioPlayer.set3DCamera(&camera);
    audioPlayer.set3DRenderer(&renderer);
    audioPlayer.initialise();
}