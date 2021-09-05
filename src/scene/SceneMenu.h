#pragma once

#include "Scene.h"

class SceneMenu : public Scene
{
public:
	SceneMenu() : Scene() {};
	void SceneInit();
	void SceneUpdate(const double deltaTime);
	void SceneShutdown();
private:
};