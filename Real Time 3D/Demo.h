
#pragma once

#include "Win32System.h"
#include "GL_Texture.h"
#include "Win32Timer.h"
#include "SceneManager.h"

class Demo
{
private:

	Win32System * m_pWin32;
	Win32Timer * m_pTimer;

	SceneManager * m_pScenes;
	GLfloat m_TimeLeft;
	GLuint m_FPS;

public:

	Demo();
	~Demo();

	void SetWindowSize(int, int, int, int);
	void SetRedrawRate(int);
	void HideConsole();

	void KeyPress(int, int);
	void Execute();

private:

	void Init_Scenes();
	void Init_OpenGL();
};