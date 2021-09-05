#include "SceneCredit.h"
#include "../system/Window.h"
#include "../graphic/Sprite.h"
#include "../graphic/Shader.h"
#include "../graphic/Camera.h"
#include "../gameobject/TextureManager.h"
#include "../system/SBEngine.h"

static Sprite *logo;

static float fade = 0.01f;
static bool fadeb = false;
static float fadespeed = 0.5f;

void SceneCredit::SceneInit()
{	
	fade = 0.01f;
	fadeb = false;
	mainCam.SetPosition(250, 250);

  logo = new Sprite;
  logo->Init(Shader_BasicTexture);
  logo->SetTexture(Tex_Credit);
	logo->SetPosition(250, 250);
	logo->SetSize(700.0f, 500.0f);
	logo->SetCamera(mainCam);
	logo->setAlpha(0.0f);
}

void SceneCredit::SceneUpdate(const double deltaTime)
{
	if (fade > 1.0f )
	{
		fade = 1.0f;
	}

	if (fadeb == true)
	{
		fade -= fadespeed * deltaTime;
	}
	else
	{
		fade += fadespeed * deltaTime;
	}

	static int oldState = GLFW_RELEASE;
	int newState = glfwGetMouseButton(GetWindow(), GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		fadeb = true;
	}
	oldState = newState;

	if (fade < 0)
	{
		pEngine->ChangeScene("Menu");
	}
	logo->setAlpha(fade);
	logo->Update(deltaTime);

}

void SceneCredit::SceneShutdown()
{
	delete logo;
}
