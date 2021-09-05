#pragma once

#include "Scene.h"

class SceneLogo : public Scene
{
public:
	SceneLogo() : Scene() {};
	void SceneInit();
	void SceneUpdate(const double deltaTime);
	void SceneShutdown();
private:
};