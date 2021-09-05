#pragma once

class Scene
{
public:
	Scene();
	~Scene();

	void Init();
	void Update(const double deltaTime);
	void Shutdown();

protected:
	virtual void SceneInit() = 0;
	virtual void SceneUpdate(const double deltaTime) = 0;
	virtual void SceneShutdown() = 0;

private:
};