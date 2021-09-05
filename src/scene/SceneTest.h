#pragma once

#include "Scene.h"

class SceneTest : public Scene
{
public:
	SceneTest() : Scene() {};
	void SceneInit();
	void SceneUpdate(const double deltaTime);
	void SceneShutdown();
private:
};

float getHP();