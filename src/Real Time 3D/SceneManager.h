
#pragma once

#include <vector>

class Scene
{
public:
    virtual ~Scene() {}
    virtual void mousePress(int, int, int, int) {}
    virtual void onMotion(float, float) {}
    virtual void onKeyPress(int, int) {}
    virtual void onUpdate() {}
    virtual void render() {}
    virtual void enter() {}
    virtual void exit() {}
};

class Demo;

class SceneManager
{
    static SceneManager* manager;
    std::vector<Scene*> scenes;
    unsigned int currentIndex;
    Demo* demoScene;
public:
    SceneManager();
    ~SceneManager();

    static SceneManager* get();

    void startFrom(unsigned int);
    void switchTo(unsigned int);
    void passEngine(Demo*);
    void pushState(Scene*);
    void updateManager();
    void previousScene();
    void nextScene();

    Scene* getCurrent();
    Demo* getEngine();
};