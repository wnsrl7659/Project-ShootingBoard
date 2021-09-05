#include "SceneLogo.h"
#include "../system/Window.h"
#include "../graphic/Sprite.h"
#include "../graphic/Shader.h"
#include "../graphic/Camera.h"
#include "../gameobject/TextureManager.h"
#include "../system/SBEngine.h"

static Sprite *logo;

void SceneLogo::SceneInit()
{	
	mainCam.SetPosition(250, 250);

  logo = new Sprite;
  logo->Init(Shader_BasicTexture);
  logo->SetTexture(Tex_Logo);
	logo->SetPosition(250, 250);
	logo->SetSize(700.0f, 500.0f);
	logo->SetCamera(mainCam);
	logo->setAlpha(0.0f);
}

static float fade = 0.01f;
static bool fadeb = false;
static float fadespeed = 0.5f;
void SceneLogo::SceneUpdate(const double deltaTime)
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
		pEngine->ChangeScene("Team");
	}
	logo->setAlpha(fade);
	logo->Update(deltaTime);

}

void SceneLogo::SceneShutdown()
{
	delete logo;
}
