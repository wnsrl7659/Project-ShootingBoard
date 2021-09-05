#include "../graphic/Sprite.h"
#include <vector>

struct Bullet 
{
  Sprite* sp;
  glm::vec2 vector;
  int dx;
  int dy;
};

struct Particle
{
  Sprite* sp;
  glm::vec2 vector;
  float timer;
};


void CreateBullet(int x, int y, int dx, int dy);
void CreateEBullet(int x, int y, int dx, int dy);
void CreateBoom(int x, int y);

extern std::vector<Bullet*> bullets;
extern std::vector<Bullet*> ebullets;
extern std::vector<Particle*> parts;