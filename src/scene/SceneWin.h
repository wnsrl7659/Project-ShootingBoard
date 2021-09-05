#pragma once

#include "Scene.h"

class SceneWin : public Scene
{
public:
	SceneWin() : Scene() {};
	void SceneInit();
	void SceneUpdate(const double deltaTime);
	void SceneShutdown();
private:
};