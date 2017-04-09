
/* -------------------------------------------------
  
 @Filename  : SceneManager.h
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: A singletone which manages scenes
			  in the applications.

 ------------------------------------------------- */

#pragma once

class Scene 
{
public:

	virtual ~Scene(){}

	virtual void MousePress(int, int, int, int){}
	virtual void Motion(float, float) {}
	virtual void KeyPress(int, int) {}
	virtual void Update(){}
	virtual void Render(){}
	virtual void Enter(){}
	virtual void Exit(){}
};

#include <vector>

class Demo;

class SceneManager
{
private:

	unsigned int m_CurrentPlace;		// Current scene to render
	std::vector<Scene *> m_vScenes;		// All scenes available
	static SceneManager * m_pManager;	// Singleton instance
	Demo * m_pEngine;


public:

	// Constructor & Deconstructor
	SceneManager();
	~SceneManager();

	// Member functions
	void PassEngine(Demo *);
	void UpdateManager();
	void StartFrom(unsigned int);	
	void SwitchTo(unsigned int);
	void PushState(Scene *);
	void PreviousScene();
	void NextScene();

	// Get & Set Functions
	static SceneManager * get();		// Singleton get function
	Demo * getEngine();
	Scene * getCurrent();
};