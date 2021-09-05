#include "SceneMenu.h"
#include "../system/Window.h"
#include "../graphic/Sprite.h"
#include "../graphic/Shader.h"
#include "../graphic/Camera.h"
#include "../gameobject/TextureManager.h"
#include "../system/SBEngine.h"
#include "../system/SoundEventHandler.h"

static Sprite* red, * menu;

static Sprite* fade;

static float falpha = 1.0f;
static int fadeb = 0;
static float fadespeed = 0.5f;

void SceneMenu::SceneInit()
{
	StartMenuMusic();
	falpha = 1.0f;
	fadeb = 0;
	mainCam.SetPosition(250, 250);

	menu = new Sprite;
	menu->Init(Shader_BasicTexture);
	menu->SetTexture(Tex_Menu);
	menu->SetPosition(250, 250);
	menu->SetSize(700.0f, 500.0f);
	menu->SetCamera(mainCam);
	menu->setAlpha(1.0f);

	red = new Sprite;
	red->Init(Shader_BasicTexture);
	red->SetTexture(Tex_Red);
	red->SetPosition(25, 25);
	red->SetSize(50.0f, 50.0f);
	red->SetCamera(mainCam);
	red->setAlpha(1.0f);

	fade = new Sprite;
	fade->Init(Shader_BasicTexture);
	fade->SetTexture(Tex_Fade);
	fade->SetPosition(250, 250);
	fade->SetSize(700.0f, 500.0f);
	fade->SetCamera(mainCam);
	fade->setAlpha(falpha);
}


void SceneMenu::SceneUpdate(const double deltaTime)
{
	GLFWwindow* window = GetWindow();
	float mx, my;
	GetCursorPosition(&mx, &my);
	int fx, fy;

	if (mx >= 0)
	{
		fx = (int)mx / 50 * 50 + 25;
	}
	else
	{
		fx = (int)mx / 50 * 50 - 25;
	}
	if (my >= 0)
	{
		fy = (int)my / 50 * 50 + 25;
	}
	else
	{
		fy = (int)my / 50 * 50 - 25;
	}

	static int oldState = GLFW_RELEASE;
	int newState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		printf("bullet event in cell %d, %d \n", (int)mx / 50, (int)my / 50);

		if (((int)mx / 50) >= 3 && ((int)mx / 50) <= 6 && ((int)my / 50) == 1)
		{
			//QUIT
			exit(1);
		}
		else if (((int)mx / 50) >= 3 && ((int)mx / 50) <= 6 && ((int)my / 50) == 5)
		{
			fadeb = 1;
		}
		else if (((int)mx / 50) >= 3 && ((int)mx / 50) <= 6 && ((int)my / 50) == 3)
		{
			fadeb = 2;
		}
	}
	oldState = newState;

	menu->Update(deltaTime);
	
	red->SetPosition(fx, fy);
	red->Update(deltaTime);

	if (fadeb == 1)
	{
		if (falpha < 1.0f)
			falpha += fadespeed * deltaTime;
		if (falpha >= 1.0f)
		{
			pEngine->ChangeScene("Test");
		}
	}
	else if (fadeb == 2)
	{
		if (falpha < 1.0f)
			falpha += fadespeed * deltaTime;
		if (falpha >= 1.0f)
		{
			pEngine->ChangeScene("Credit");
		}
	}
	else if (fadeb == 0)
	{
		if (falpha > 0.0f)
			falpha -= fadespeed * deltaTime;
	}

	fade->setAlpha(falpha);
	fade->Update(deltaTime);
}

void SceneMenu::SceneShutdown()
{
	EndMenuMusic();
	delete red;
	delete menu;
	delete fade;
}
