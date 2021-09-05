#include "SceneWin.h"
#include "../system/Window.h"
#include "../graphic/Sprite.h"
#include "../graphic/Shader.h"
#include "../graphic/Camera.h"
#include "../gameobject/TextureManager.h"
#include "../system/SBEngine.h"
#include "../system/SoundEventHandler.h"

static Sprite* win;

static float fade = 0.01f;
static bool fadeb = false;
static float fadespeed = 0.5f;

void SceneWin::SceneInit()
{
	PlayerWinSound();
	mainCam.SetPosition(250, 250);

	win = new Sprite;
	win->Init(Shader_BasicTexture);
	win->SetTexture(Tex_Win);
	win->SetPosition(250, 250);
	win->SetSize(700.0f, 500.0f);
	win->SetCamera(mainCam);
	win->setAlpha(0.0f);

	fade = 0.01f;
	fadeb = false;
}

void SceneWin::SceneUpdate(const double deltaTime)
{
	if (fade > 1.0f)
	{
		fadeb = true;
	}

	if (fadeb == true)
	{
		fade -= fadespeed * deltaTime;
	}
	else
	{
		fade += fadespeed * deltaTime;
	}

	if (fade < 0)
	{
		pEngine->ChangeScene("Menu");
	}
	win->setAlpha(fade);
	win->Update(deltaTime);

}

void SceneWin::SceneShutdown()
{
	delete win;
}
