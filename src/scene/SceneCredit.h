#pragma once

#include "Scene.h"

class SceneCredit : public Scene
{
public:
	SceneCredit() : Scene() {};
	void SceneInit();
	void SceneUpdate(const double deltaTime);
	void SceneShutdown();
private:
};