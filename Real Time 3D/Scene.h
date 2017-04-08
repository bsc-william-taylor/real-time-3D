
/* -------------------------------------------------
  
 @Filename  : SceneManager.cpp
 @author	: William Taylor
 @date		: 12/02/2014

 @purpose	: A interface that all scenes must
			  follow is they are to be controlled
			  by the SceneManager

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

// END