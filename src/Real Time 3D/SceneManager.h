
#pragma once

#include <vector>

class Scene
{
public:
    virtual ~Scene() {}
    virtual void mousePress(int, int, int, int) {}
    virtual void motion(float, float) {}
    virtual void keyPress(int, int) {}
    virtual void update() {}
    virtual void render() {}
    virtual void enter() {}
    virtual void exit() {}
};

class Demo;

class SceneManager
{
    static SceneManager * m_pManager;
    std::vector<Scene *> m_vScenes;
    unsigned int m_CurrentPlace;
    Demo * m_pEngine;
public:
    SceneManager();
    ~SceneManager();

    static SceneManager * get();

    void StartFrom(unsigned int);
    void SwitchTo(unsigned int);
    void PassEngine(Demo*);
    void PushState(Scene*);
    void UpdateManager();
    void PreviousScene();
    void NextScene();

    Scene* getCurrent();
    Demo* getEngine();
};