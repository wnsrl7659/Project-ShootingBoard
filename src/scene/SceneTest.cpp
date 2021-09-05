#include "SceneTest.h"
#include "../system/Window.h"
#include "../graphic/Sprite.h"
#include "../graphic/Shader.h"
#include "../graphic/Camera.h"
#include "../gameobject/TextureManager.h"
#include "../imgui/SBGui.h"
#include "../imgui/SBGuiWindow.h"
#include "../gameobject/TileMap.h"
#include "../system/SBEngine.h"
#include "../system/SoundEventHandler.h"
#include "../imgui/SBGuiWidgets.h"
#include "../gameobject/ObjectManager.h"

static Sprite* player, * enemyA, *enemyB, *enemyC, *enemyD, * blue, * red, * uil, * uir, * itemA, *itemB, *scope;
static float pHP = 5.0f;

static Sprite* fade;

static float falpha = 1.0f;
static int fadeb = 0;
static float fadespeed = 0.5f;

static int camside = 0;

static bool getA = false;
static bool getB = false;

static int sscale = 30000;

float getHP()
{
	return pHP;
}
void SceneTest::SceneInit()
{
	StartGameMusic();
	uiGUI = !uiGUI;
	resetGameTime();
	pHP = 5.0f;
	falpha = 1.0f;
	fadeb = 0;
	camside = 0;
	sscale = 30000;
	getA = false;
	getB = false;

	mainCam.SetPosition(250, 250);

	player = new Sprite;
	player->Init(Shader_BasicTexture);
	player->SetTexture(Tex_Player);
	player->SetPosition(125, 125);
	player->SetSize(50.0f, 50.0f);
	player->SetCamera(mainCam);
	player->setAlpha(1.0f);

	scope = new Sprite;
	scope->Init(Shader_BasicTexture);
	scope->SetTexture(Tex_Scope);
	scope->SetPosition(125, 125);
	scope->SetSize(30000.0f, 30000.0f);
	scope->SetCamera(mainCam);
	scope->setAlpha(1.0f);

	enemyA = new Sprite;
	enemyA->Init(Shader_BasicTexture);
	enemyA->SetTexture(Tex_Enemy);
	enemyA->SetPosition(13 * 50 + 25, 11 * 50 + 25);
	enemyA->SetSize(50.0f, 50.0f);
	enemyA->SetCamera(mainCam);
	enemyA->setAlpha(1.0f);
	enemyB = new Sprite;
	enemyB->Init(Shader_BasicTexture);
	enemyB->SetTexture(Tex_Enemy);
	enemyB->SetPosition(13 * 50 + 25, 18 * 50 + 25);
	enemyB->SetRotation(3.14159);
	enemyB->SetSize(50.0f, 50.0f);
	enemyB->SetCamera(mainCam);
	enemyB->setAlpha(1.0f);
	enemyC = new Sprite;
	enemyC->Init(Shader_BasicTexture);
	enemyC->SetTexture(Tex_Enemy);
	enemyC->SetPosition(16 * 50 + 25, 11 * 50 + 25);
	enemyC->SetSize(50.0f, 50.0f);
	enemyC->SetCamera(mainCam);
	enemyC->setAlpha(1.0f);
	enemyD = new Sprite;
	enemyD->Init(Shader_BasicTexture);
	enemyD->SetTexture(Tex_Enemy);
	enemyD->SetPosition(16 * 50 + 25, 18 * 50 + 25);
	enemyD->SetRotation(3.14159);
	enemyD->SetSize(50.0f, 50.0f);
	enemyD->SetCamera(mainCam);
	enemyD->setAlpha(1.0f);

	blue = new Sprite;
	blue->Init(Shader_BasicTexture);
	blue->SetTexture(Tex_Blue);
	blue->SetPosition(125, 125);
	blue->SetSize(50.0f, 50.0f);
	blue->SetCamera(mainCam);
	blue->setAlpha(1.0f);

	red = new Sprite;
	red->Init(Shader_BasicTexture);
	red->SetTexture(Tex_Red);
	red->SetPosition(25, 25);
	red->SetSize(50.0f, 50.0f);
	red->SetCamera(mainCam);
	red->setAlpha(1.0f);

	uil = new Sprite;
	uil->Init(Shader_BasicTexture);
	uil->SetTexture(Tex_UIL);
	uil->SetSize(100.0f, 500.0f);
	uil->SetCamera(mainCam);
	uil->setAlpha(1.0f);

	uir = new Sprite;
	uir->Init(Shader_BasicTexture);
	uir->SetTexture(Tex_UIR);
	uir->SetSize(100.0f, 500.0f);
	uir->SetCamera(mainCam);
	uir->setAlpha(1.0f);

	itemA = new Sprite;
	itemA->Init(Shader_BasicTexture);
	itemA->SetTexture(Tex_ItemA);
	itemA->SetPosition(17 * 50 + 25, 2 * 50 + 25);
	itemA->SetSize(50.0f, 50.0f);
	itemA->SetCamera(mainCam);
	itemA->setAlpha(1.0f);

	itemB = new Sprite;
	itemB->Init(Shader_BasicTexture);
	itemB->SetTexture(Tex_ItemB);
	itemB->SetPosition(18 * 50 + 25, 15 * 50 + 25);
	itemB->SetSize(50.0f, 50.0f);
	itemB->SetCamera(mainCam);
	itemB->setAlpha(1.0f);


	fade = new Sprite;
	fade->Init(Shader_BasicTexture);
	fade->SetTexture(Tex_Fade);
	fade->SetPosition(250, 250);
	fade->SetSize(700.0f, 500.0f);
	fade->SetCamera(mainCam);
	fade->setAlpha(falpha);

	tn_object->AddWidget(new SBGuiObject("player", player));
	tn_object->AddWidget(new SBGuiObject("blue", blue));
	tn_object->AddWidget(new SBGuiObject("red", red));
	tn_object->AddWidget(new SBGuiObject("UIright", uir));
	tn_object->AddWidget(new SBGuiObject("UIleft", uil));

	TileMapOneInit();
}

static float obspeed = 50.0f;
static float cooltime = 0.1f;
static float ecool = 4.0f;
void SceneTest::SceneUpdate(const double deltaTime)
{
	TileMapOneUpdate(deltaTime);

	// 250 250, 750 250, 750 750, 
	float px = player->GetPosition().x;
	float py = player->GetPosition().y;

	if (py >= 1475)
	{
		fadeb = 2;
	}

	int i = (int)px / 50;
	int j = (int)py / 50;

	if (colmap[(int)px / 50][(int)py / 50] == 2)
	{
		PaintSound();
		pHP -= 1.0f * deltaTime;
	}

	if (pHP < 0)
	{
		fadeb = 1;
		//uiGUI = !uiGUI;
		//pEngine->RestartScene();
	}

	float camspeed = 10;
	switch (camside)
	{
		//right
	case 1:
		mainCam.SetPosition(mainCam.GetPosition()[0] + camspeed, mainCam.GetPosition()[1]);
		if ((int)(mainCam.GetPosition()[0] - 250) % 500 == 0)
		{
			camside = 0;
		}
		break;
		//left
	case 2:
		mainCam.SetPosition(mainCam.GetPosition()[0] - camspeed, mainCam.GetPosition()[1]);
		if ((int)(mainCam.GetPosition()[0] - 250) % 500 == 0)
		{
			camside = 0;
		}
		break;
		//up
	case 3:
		mainCam.SetPosition(mainCam.GetPosition()[0], mainCam.GetPosition()[1] + camspeed);
		if ((int)(mainCam.GetPosition()[1] - 250) % 500 == 0)
		{
			camside = 0;
		}
		break;
		//down
	case 4:
		mainCam.SetPosition(mainCam.GetPosition()[0], mainCam.GetPosition()[1] - camspeed);
		if ((int)(mainCam.GetPosition()[1] - 250) % 500 == 0)
		{
			camside = 0;
		}
		break;
	}
	if (abs(px - mainCam.GetPosition()[0]) > 250)
	{
		//player right side
		if ((px - mainCam.GetPosition()[0]) > 0)
		{
			camside = 1;
			if ((int)(mainCam.GetPosition()[0] - 250) % 500 == 0)
				mainCam.SetPosition(mainCam.GetPosition()[0] + camspeed, mainCam.GetPosition()[1]);
		}
		else
		{
			camside = 2;
			if ((int)(mainCam.GetPosition()[0] - 250) % 500 == 0)
			mainCam.SetPosition(mainCam.GetPosition()[0] - camspeed, mainCam.GetPosition()[1]);
		}
	}
	if (abs(py - mainCam.GetPosition()[1]) > 250)
	{
		//player up side
		if ((py - mainCam.GetPosition()[1]) > 0)
		{
			camside = 3;
			if ((int)(mainCam.GetPosition()[1] - 250) % 500 == 0)
			mainCam.SetPosition(mainCam.GetPosition()[0], mainCam.GetPosition()[1] + camspeed);
		}
		else
		{
			camside = 4;
			if ((int)(mainCam.GetPosition()[1] - 250) % 500 == 0)
			mainCam.SetPosition(mainCam.GetPosition()[0], mainCam.GetPosition()[1] - camspeed);
		}
	}
	/*
	if (px < 500 && mainCam.GetPosition()[0] != 250)
	{
		mainCam.SetPosition(mainCam.GetPosition()[0] - camspeed, mainCam.GetPosition()[1]);
	}
	else if (px > 500 && mainCam.GetPosition()[0] != 750)
	{
		mainCam.SetPosition(mainCam.GetPosition()[0] + camspeed, mainCam.GetPosition()[1]);
	}

	if (py < 500 && mainCam.GetPosition()[1] != 250)
	{
		mainCam.SetPosition(mainCam.GetPosition()[0], mainCam.GetPosition()[1] - camspeed);
	}
	else if (py > 500 && mainCam.GetPosition()[1] != 750)
	{
		mainCam.SetPosition(mainCam.GetPosition()[0], mainCam.GetPosition()[1] + camspeed);
	}
	*/

	if (ecool < 0)
	{

		if (enemyA->getAlpha() != 0.0f)
			CreateEBullet(13, 11, 13, 18);
		if (enemyB->getAlpha() != 0.0f)
		CreateEBullet(13, 18, 13, 11);
		if (enemyC->getAlpha() != 0.0f)
		CreateEBullet(16, 11, 16, 18);
		if (enemyD->getAlpha() != 0.0f)
		CreateEBullet(16, 18, 16, 11);
		ecool = 4.0f;
	}
	else
	{
		ecool -= 5.0f * deltaTime;
	}

	GLFWwindow* window = GetWindow();
	glm::vec2 ppos = player->GetPosition();
	glm::vec2 bpos = blue->GetPosition();

	float mx, my;
	GetCursorPosition(&mx, &my);
	
	static int oldState = GLFW_RELEASE;
	int newState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		if (((int)mx / 50) >= 0 && ((int)my / 50) >= 0)
		{
			//printf("bullet event in cell %d, %d \n", (int)mx / 50, (int)my / 50);
			PlayerShootSound();
			CreateBullet((int)px / 50, (int)py / 50, (int)mx / 50, (int)my / 50);
		}
	}
	oldState = newState;
	//
	for (int i = 0; i < bullets.size(); i++)
	{
		glm::vec2 temppos = bullets[i]->sp->GetPosition();
		glm::vec2 tempvec = bullets[i]->vector;
		tempvec.x = tempvec.x * deltaTime * obspeed;
		tempvec.y = tempvec.y * deltaTime * obspeed;
		temppos += tempvec;
		bullets[i]->sp->SetPosition(temppos.x, temppos.y);
		bullets[i]->sp->Update(deltaTime);
	}
	std::vector<int> dellist;
	for (int i = 0; i < bullets.size(); i++)
	{
		glm::vec2 temppos = bullets[i]->sp->GetPosition();
		int bx = (int)temppos.x / 50;
		int by = (int)temppos.y / 50;

		if (colmap[bx][by] == 1 || colmap[bx][by] >= 4)
		{
			dellist.push_back(i);
			continue;
		}

		if (bx == bullets[i]->dx && by == bullets[i]->dy)
		{
			dellist.push_back(i);
			CreateBoom(bx, by);
			if (bx == 13 && by == 11)
			{
				if(enemyA->getAlpha() != 0.0f)
					ExplosionSound();
				enemyA->setAlpha(0.0f);
			}
			else if (bx == 13 && by == 18)
			{
				if (enemyB->getAlpha() != 0.0f)
					ExplosionSound();
				enemyB->setAlpha(0.0f);
			}
			else if (bx == 16 && by == 11)
			{
				if (enemyC->getAlpha() != 0.0f)
					ExplosionSound();
				enemyC->setAlpha(0.0f);
			}
			else if (bx == 16 && by == 18)
			{
				if (enemyD->getAlpha() != 0.0f)
					ExplosionSound();
				enemyD->setAlpha(0.0f);
			}
		}
	}
	while (true)
	{
		if (dellist.size() == 0)
		{
			break;
		}
		int i = dellist[(dellist.size() - 1)];
		dellist.pop_back();
		
		delete bullets[i]->sp;
		delete bullets[i];
		bullets.erase(bullets.begin() + i);
	}
	//
		//
	for (int i = 0; i < ebullets.size(); i++)
	{
		glm::vec2 temppos = ebullets[i]->sp->GetPosition();
		glm::vec2 tempvec = ebullets[i]->vector;
		tempvec.x = tempvec.x * deltaTime * obspeed;
		tempvec.y = tempvec.y * deltaTime * obspeed;
		temppos += tempvec;
		ebullets[i]->sp->SetPosition(temppos.x, temppos.y);
		ebullets[i]->sp->Update(deltaTime);
	}
	for (int i = 0; i < ebullets.size(); i++)
	{
		glm::vec2 temppos = ebullets[i]->sp->GetPosition();
		int bx = (int)temppos.x / 50;
		int by = (int)temppos.y / 50;
		int ppx = (int)px / 50;
		int ppy = (int)py / 50;

		if (bx == ppx && by == ppy)
		{
			dellist.push_back(i); 
			ShotHitSound();
			pHP -= 0.4f;
			continue;
		}
		if (bx == ebullets[i]->dx && by == ebullets[i]->dy)
		{
			dellist.push_back(i);
		}
	}
	while (true)
	{
		if (dellist.size() == 0)
		{
			break;
		}
		int i = dellist[(dellist.size() - 1)];
		dellist.pop_back();

		delete ebullets[i]->sp;
		delete ebullets[i];
		ebullets.erase(ebullets.begin() + i);
	}
	//

	for (int i = 0; i < parts.size(); i++)
	{
		glm::vec2 temppos = parts[i]->sp->GetPosition();
		glm::vec2 tempvec = parts[i]->vector;
		tempvec.x = tempvec.x * deltaTime * obspeed;
		tempvec.y = tempvec.y * deltaTime * obspeed;
		temppos += tempvec;
		parts[i]->sp->SetPosition(temppos.x, temppos.y);
		parts[i]->sp->Update(deltaTime);
		parts[i]->timer -= 0.1f;
	}
	for (int i = 0; i < parts.size(); i++)
	{
		if (parts[i]->timer <= 0.0f)
		{
			dellist.push_back(i);
		}
	}
	while (true)
	{
		if (dellist.size() == 0)
		{
			break;
		}
		int i = dellist[(dellist.size() - 1)];
		dellist.pop_back();

		delete parts[i]->sp;
		delete parts[i];
		parts.erase(parts.begin() + i);
	}

	static int oldStateT = GLFW_RELEASE;
	int newStateT = glfwGetKey(window, GLFW_KEY_X);
	if (newStateT == GLFW_RELEASE && oldStateT == GLFW_PRESS) 
	{
		pressGUI = !pressGUI;
	}
	oldStateT = newStateT;

	if (cooltime <= 0.0f)
	{
		float dx = bpos.x - ppos.x;
		float dy = bpos.y - ppos.y;
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				if (dy < 100)
					bpos.y += 50;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				if(dx > -100)
					bpos.x -= 50;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				if (dy > -100)
					bpos.y -= 50;
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				if (dx < 100)
					bpos.x += 50;
			}
		}

		cooltime = 0.1f;
	}
	else
	{
		cooltime -= deltaTime;
	}

	int playerspeed = (float)5 * deltaTime * obspeed;
	if (playerspeed < 1)
	{
		playerspeed = 1;
	}

	if (ppos.x != bpos.x)
	{
		if (ppos.x < bpos.x)
		{
			int i = (int)px / 50;
			int j = (int)py / 50;

			if (colmap[i + 1][j] == 1 && ((int)px % 50) == 25)
			{
			}
			else if (colmap[i + 1][j] >= 4 && ((int)px % 50) == 25)
			{
			}
			else if (ppos.y != bpos.y && ppos.y < bpos.y && colmap[i + 1][j + 1] == 1 && (colmap[i][j + 1] == 0 || colmap[i][j + 1] == 2) && ((int)px % 50) == 25)
			{
			}
			else if (ppos.y != bpos.y && ppos.y > bpos.y && colmap[i + 1][j - 1] == 1 && (colmap[i][j - 1] == 0 || colmap[i][j - 1] == 2) && ((int)px % 50) == 25)
			{
			}
			else if (colmap[i][j] == 3)
			{
				ppos.x += (float)playerspeed / 2.0f;
			}
			else
			{
				ppos.x += playerspeed;
			}
		}
		else
		{
			int i = (int)px / 50;
			int j = (int)py / 50;

			if (colmap[i - 1][j] == 1 && ((int)px % 50) == 25)
			{
			}
			else if (colmap[i - 1][j] >= 4 && ((int)px % 50) == 25)
			{
			}
		
			else if (ppos.y != bpos.y && ppos.y < bpos.y && colmap[i - 1][j + 1] == 1 && (colmap[i][j + 1] == 0 || colmap[i][j + 1] == 2) && ((int)px % 50) == 25)
			{
			}
			else if (ppos.y != bpos.y && ppos.y > bpos.y && colmap[i - 1][j - 1] == 1 && (colmap[i][j - 1] == 0 || colmap[i][j - 1] == 2) && ((int)px % 50) == 25)
			{
			}
			else if (colmap[i][j] == 3)
			{
				ppos.x -= (float)playerspeed / 2.0f;
			}
			else
			{
				ppos.x -= playerspeed;
			}
		}
	}
	if (ppos.y != bpos.y)
	{
		if (ppos.y < bpos.y)
		{
			int i = (int)px / 50;
			int j = (int)py / 50;

			if (colmap[i][j + 1] == 1 && ((int)py % 50) == 25)
			{
			}
			else if (colmap[i][j + 1] >= 4 && ((int)py % 50) == 25)
			{
			}
			else if (colmap[i][j] == 3)
			{
				ppos.y += (float)playerspeed / 2.0f;
			}
			else
			{
				ppos.y += playerspeed;
			}
		}
		else
		{
			int i = (int)px / 50;
			int j = (int)py / 50;

			if (colmap[i][j - 1] == 1 && ((int)py % 50) == 25)
			{
			}
			else if (colmap[i][j - 1] >= 4 && ((int)py % 50) == 25)
			{
			}
			else if (colmap[i][j] == 3)
			{
				ppos.y -= (float)playerspeed / 2.0f;
			}
			else
			{
				ppos.y -= playerspeed;
			}
		}
	}

	int sandi = (int)ppos.x / 50;
	int sandj = (int)ppos.y / 50;

	if (colmap[sandi][sandj] == 3)
	{
		int i = (int)ppos.x / 50;
		int j = (int)ppos.y / 50;
		float fixedi = i * 50 + 25;
		float fixedj = j * 50 + 25;
		float tempx = abs(ppos.x - fixedi);
		float tempy = abs(ppos.y - fixedj);

		if (tempx < ((float)playerspeed / 2.0f))
		{
			ppos.x = fixedi;
		}
		if (tempy < ((float)playerspeed / 2.0f))
		{
			ppos.y = fixedj;
		}
	}
	else
	{
		int i = (int)ppos.x / 50;
		int j = (int)ppos.y / 50;
		float fixedi = i * 50 + 25;
		float fixedj = j * 50 + 25;
		float tempx = abs(ppos.x - fixedi);
		float tempy = abs(ppos.y - fixedj);

		if (tempx < playerspeed)
		{
			ppos.x = fixedi;
		}
		if (tempy < playerspeed)
		{
			ppos.y = fixedj;
		}
	}

	/*
	int fixedx = ((int)ppos.x / 50)*50;
	int fixedy = ((int)ppos.y / 50)*50;
	if (abs(ppos.x - fixedx) <= 2.5)
	{
		ppos.x = fixedx;
	}
	if (abs(ppos.y - fixedy) <= 2.5)
	{
		ppos.y = fixedy;
	}
	*/

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

	if (ppos.y < 500)
	{
		if (sscale < 30000)
		{
			sscale += 1000;
		}
	}
	else if (ppos.y >= 500 && ppos.y < 1000)
	{
		if (sscale > 6000)
		{
			sscale -= 1000;
		}
		else if (sscale < 6000)
		{
			sscale += 1000;
		}
	}
	else
	{
		if (sscale > 3000)
		{
			sscale -= 1000;
		}
	}

	double angle = -atan2(mx - ppos.x, my - ppos.y);
	
	player->SetRotation(angle);

	player->SetPosition(ppos.x, ppos.y);
	blue->SetPosition(bpos.x, bpos.y);
	red->SetPosition(fx, fy);

	if (!getA)
	{
		itemA->Update(deltaTime);
	}
	if (!getB)
	{
		itemB->Update(deltaTime);
	}

	player->Update(deltaTime);

	enemyA->Update(deltaTime);
	enemyB->Update(deltaTime);
	enemyC->Update(deltaTime);
	enemyD->Update(deltaTime);

	float camx = mainCam.GetPosition()[0];
	float camy = mainCam.GetPosition()[1];

	scope->SetSize(sscale, sscale);
	scope->SetPosition(ppos.x, ppos.y);
	scope->Update(deltaTime);

	blue->Update(deltaTime);
	red->Update(deltaTime);

	uil->SetPosition(camx - 250 - 50, camy);
	uir->SetPosition(camx + 250 + 50, camy);

	uil->Update(deltaTime);
	uir->Update(deltaTime);

	if (getA)
	{
		itemA->SetPosition(camx + 250 + 50, camy + 180);
  	itemA->Update(deltaTime);
	}
	if (getB)
	{
		itemB->SetPosition(camx + 250 + 50, camy + 100);
		itemB->Update(deltaTime);
	}


	if ((int)(ppos.x / 50) == 17 && (int)(ppos.y / 50) == 2)
	{
		getA = true;

		colmap[4][9] = 0;
		colmap[5][9] = 0;
		colmap[4][10] = 0;
		colmap[5][10] = 0;
		colmap[15][1] = 0;
	}

	if ((int)(ppos.x / 50) == 18 && (int)(ppos.y / 50) == 15)
	{
		getB = true;

		colmap[4][19] = 0;
		colmap[5][19] = 0;
		colmap[4][20] = 0;
		colmap[5][20] = 0;
	}


	if (fadeb == 1)
	{
		if (falpha < 1.0f)
			falpha += fadespeed * deltaTime;
		if (falpha >= 1.0f)
		{
			uiGUI = !uiGUI;
			pEngine->RestartScene();
		}
	}
	else if (fadeb == 2)
	{
		if (falpha < 1.0f)
			falpha += fadespeed * deltaTime;
		if (falpha >= 1.0f)
		{
			uiGUI = !uiGUI;
			pEngine->ChangeScene("Win");
		}
	}
	else if (fadeb == 0)
	{
		if (falpha > 0.0f)
			falpha -= fadespeed * deltaTime;
	}
	fade->SetPosition(camx, camy);
	fade->setAlpha(falpha);
	fade->Update(deltaTime);
}

void SceneTest::SceneShutdown()
{
	EndGameMusic();
	TileMapOneShutdown();
	
	delete player;
	delete enemyA;
	delete enemyB;
	delete enemyC;
	delete enemyD;
	delete blue;
	delete red;
	delete uil;
	delete uir;
	delete fade;
	delete itemA;
	delete itemB;
	delete scope;
}
