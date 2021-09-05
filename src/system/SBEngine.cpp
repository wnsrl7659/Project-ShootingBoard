#include "SBEngine.h"
#include "Window.h"
#include "../gameobject/MeshManager.h"
#include "../gameobject/TextureManager.h"
#include "../graphic/Shader.h"
#include "../imgui/SBGui.h"
#include "../system/SoundSystem.h"

Engine* pEngine = nullptr;


Engine::Engine()
{

	m_pSceneManager = new SceneManager();
	m_pSceneManager->AddScene("Test", ST_test);
	m_pSceneManager->AddScene("Logo", ST_logo);
	m_pSceneManager->AddScene("Menu", ST_menu);
	m_pSceneManager->AddScene("Win", ST_win);
	m_pSceneManager->AddScene("Team", ST_team);
	m_pSceneManager->AddScene("Credit", ST_credit);
	m_pSceneManager->SetFirstScene("Logo");

	Init();
}

Engine::~Engine()
{
	Shutdown();

	if (m_pSceneManager)
	{
		delete m_pSceneManager;
		m_pSceneManager = nullptr;
	}
}

void Engine::Init()
{
	SoundSystem* soundSystem = new SoundSystem();
	soundSystem->Init();

	WindowInit();

	mygui = new SBGui;
	mygui->Init();

	MeshManagerInit();
	TextureManagerInit();
	ShaderInit();
	m_pSceneManager->Init();
}

void Engine::Update(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT);
	m_pSceneManager->CheckScene();
	m_pSceneManager->Update(dt);
	SoundSystem::Get()->Update();
	mygui->Update();
	mygui->Render();
	WindowUpdate(dt);
}

void Engine::Shutdown()
{
	m_pSceneManager->Shutdown();
	SoundSystem::Get()->Shutdown();
	mygui->Shutdown();
	ShaderShutdown();
	TextureManagerShutdown();
	MeshManagerShutdown();
	WindowShutdown();

	delete mygui;
}

void Engine::ChangeScene(std::string name)
{
	m_pSceneManager->ChangeScene(name);
}

void Engine::RestartScene()
{
	m_pSceneManager->RestartScene();
}