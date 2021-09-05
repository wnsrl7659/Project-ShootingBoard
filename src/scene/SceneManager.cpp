#include "SceneManager.h"
#include "SceneTest.h"
#include "SceneLogo.h"
#include "SceneMenu.h"
#include "SceneWin.h"
#include "SceneCredit.h"
#include "SceneTeam.h"

SceneManager::SceneManager()
{
	scenes.max_load_factor(0.1f);
}

SceneManager::~SceneManager()
{
	std::vector<std::string> names;

	for (auto sc : scenes)
	{
		names.push_back(const_cast<char*>(sc.first.c_str()));
	}
	for (auto nm : names)
	{
		RemoveScene(nm);
	}

	scenes.clear();
}

Scene* SceneManager::AddScene(std::string name, SceneType type)
{
	Scene* sc = 0;
	
	switch(type)
	{
	case ST_test:
		sc = new SceneTest();
		break;
	case ST_logo:
		sc = new SceneLogo();
		break;
	case ST_menu:
		sc = new SceneMenu();
		break;
	case ST_win:
		sc = new SceneWin();
		break;
	case ST_team:
		sc = new SceneTeam();
		break;
	case ST_credit:
		sc = new SceneCredit();
		break;
	}
	if (sc == 0)
	{
		//error
		return 0;
	}
	scenes[name] = sc;
	
	return sc;
}

void SceneManager::RemoveScene(std::string name)
{
	//check name is available
	delete scenes[name];
	scenes.erase(name);
}

void SceneManager::SetFirstScene(std::string name)
{
	c_scene = name;
	n_scene = name;
}

void SceneManager::ChangeScene(std::string name)
{
  if (scenes[name] == nullptr)
  {
    return;
  }
	n_scene = name;
}

void SceneManager::CheckScene()
{
	if (n_scene[0] != c_scene[0])
	{
    if (n_scene[0] == "restart"[0])
    {
      scenes[c_scene]->Shutdown();
      n_scene = c_scene;
      scenes[c_scene]->Init();
    }
    else
    {
      scenes[c_scene]->Shutdown();
      c_scene = n_scene;
      scenes[c_scene]->Init();
    }
	}
}
void SceneManager::RestartScene()
{
  n_scene = "restart";
}

void SceneManager::Init()
{
	scenes[c_scene]->Init();
}
void SceneManager::Update(const double deltaTime)
{
	scenes[c_scene]->Update(deltaTime);
}
void SceneManager::Shutdown()
{
	scenes[c_scene]->Shutdown();
}