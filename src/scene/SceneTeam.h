#pragma once

#include "Scene.h"

class SceneTeam : public Scene
{
public:
	SceneTeam() : Scene() {};
	void SceneInit();
	void SceneUpdate(const double deltaTime);
	void SceneShutdown();
private:
};