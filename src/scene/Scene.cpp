#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{

  // This must be on the most bottom line
  this->SceneInit();
}

void Scene::Update(const double deltaTime)
{

  // This must be on the most bottom line
  this->SceneUpdate(deltaTime);
}


void Scene::Shutdown()
{

  // This must be on the TOP line, NOT BOTTOM!!
  this->SceneShutdown();
}
