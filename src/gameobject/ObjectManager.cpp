#include "ObjectManager.h"
#include "../graphic/Shader.h"
#include <glm/gtx/rotate_vector.hpp>


std::vector<Bullet*> bullets;
std::vector<Bullet*> ebullets;
std::vector<Particle*> parts;

void CreateBullet(int x, int y, int dx, int dy)
{
  float px, py, ddx, ddy;

  px = x * 50 + 25;
  py = y * 50 + 25;
  ddx = dx * 50 + 25;
  ddy = dy * 50 + 25;

  Bullet* temp = new Bullet;

  temp->sp = new Sprite;
  temp->sp->Init(Shader_BasicTexture);
  temp->sp->SetTexture(Tex_Bullet);
  temp->sp->SetPosition(px, py);
  temp->sp->SetSize(50.0f, 50.0f);
  temp->sp->SetCamera(mainCam);
  temp->sp->setAlpha(1.0f);

  temp->dx = dx;
  temp->dy = dy;

  temp->vector.x = (float)(ddx - px) / 20.0f;
  temp->vector.y = (float)(ddy - py) / 20.0f;
  //i * 50 + 25, j * 50 + 25

  bullets.push_back(temp);
}

void CreateEBullet(int x, int y, int dx, int dy)
{
  float px, py, ddx, ddy;

  px = x * 50 + 25;
  py = y * 50 + 25;
  ddx = dx * 50 + 25;
  ddy = dy * 50 + 25;

  Bullet* temp = new Bullet;

  temp->sp = new Sprite;
  temp->sp->Init(Shader_BasicTexture);
  temp->sp->SetTexture(Tex_EBullet);
  temp->sp->SetPosition(px, py);
  temp->sp->SetSize(25.0f, 25.0f);
  temp->sp->SetCamera(mainCam);
  temp->sp->setAlpha(1.0f);

  temp->dx = dx;
  temp->dy = dy;

  temp->vector.x = (float)(ddx - px) / 40.0f;
  temp->vector.y = (float)(ddy - py) / 40.0f;
  //i * 50 + 25, j * 50 + 25

  ebullets.push_back(temp);
}

void CreateBoom(int x, int y)
{
  for (int i = 0; i < 16; i++)
  {
    float px, py;

    px = x * 50 + 25;
    py = y * 50 + 25;

    Particle* temp = new Particle;

    temp->sp = new Sprite;
    temp->sp->Init(Shader_BasicTexture);
    temp->sp->SetTexture(Tex_Bullet);
    temp->sp->SetPosition(px, py);
    temp->sp->SetSize(25.0f, 25.0f);
    temp->sp->SetCamera(mainCam);
    temp->sp->setAlpha(1.0f);

    temp->timer = 4.0f;

    glm::vec2 tempvec = glm::vec2(2, 0);
    tempvec = glm::rotate(tempvec, (0.393f * (float)i));

    temp->vector = tempvec;

    parts.push_back(temp);
  }
}