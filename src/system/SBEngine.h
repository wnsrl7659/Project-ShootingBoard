#pragma once

#include "../scene/SceneManager.h"

typedef class SBGui;

class Engine
{
public:
	Engine();
	~Engine();
	void Init();
	void Update(float dt);
	void Shutdown();

	void ChangeScene(std::string name);
	void RestartScene();

	bool running = true;

private:
	SceneManager* m_pSceneManager;
	SBGui* mygui;
};

extern Engine* pEngine;

