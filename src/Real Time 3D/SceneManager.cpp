
#include "SceneManager.h"
#include "Demo.h"

SceneManager * SceneManager::manager = nullptr;

SceneManager::SceneManager()
    : currentIndex(0)
{
}

SceneManager::~SceneManager()
{
    for (int i = 0; i < scenes.size(); i++)
    {
        delete scenes[i];
    }

    scenes.clear();
}

void SceneManager::startFrom(unsigned int startingPoint)
{
    currentIndex = startingPoint;
}

Demo* SceneManager::getEngine()
{
    return demoScene;
}

void SceneManager::passEngine(Demo * Demo)
{
    demoScene = Demo;
}

void SceneManager::previousScene()
{
    currentIndex--;
}

void SceneManager::nextScene()
{
    currentIndex++;
}

void SceneManager::pushState(Scene * state)
{
    if (state != nullptr)
    {
        scenes.push_back(state);
    }
}

void SceneManager::updateManager()
{
    scenes[currentIndex]->onUpdate();
    scenes[currentIndex]->render();
}

void SceneManager::switchTo(unsigned int newPlace)
{
    scenes[currentIndex]->exit();
    currentIndex = newPlace;
    scenes[currentIndex]->enter();
}

Scene* SceneManager::getCurrent()
{
    if (scenes.empty())
    {
        return NULL;
    }

    return scenes[currentIndex];
}

SceneManager* SceneManager::get()
{
    if (manager == nullptr)
    {
        manager = new SceneManager();
    }

    return manager;
}