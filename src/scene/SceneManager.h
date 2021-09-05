#pragma once

#include <string>
#include <unordered_map>

#include "Scene.h"

typedef enum SceneType
{
  ST_default = -1,
	ST_test,
	ST_logo,
	ST_menu,
	ST_win,
	ST_team,
	ST_credit,
	ST_count,
}SceneType;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	Scene* AddScene(std::string name, SceneType type);
	void RemoveScene(std::string name);
	void SetFirstScene(std::string name);		
	void ChangeScene(std::string name);
  void CheckScene();
  void RestartScene();

	void Init();								
	void Update(const double deltaTime);		
	void Shutdown();	

	std::string CurrentScene() { return c_scene; }

private:
	std::unordered_map<std::string, Scene*> scenes;
	std::string c_scene;
	std::string n_scene;
};