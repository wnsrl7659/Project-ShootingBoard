#ifndef SPRITE_H
#define SPRITE_H

#include "../system/Window.h"
#include "../physics/Transform.h"
#include "Render.h"
#include "Camera.h"
#include "Mesh.h"
 


class Sprite
{
public:
	Sprite();
	~Sprite();
	void Init(int shader = 99);
	void SetTexture(const int id);
	void SetPosition(float x, float y);
	glm::vec2 GetPosition();
	int GetShader();
	int GetTexture();
	glm::vec2 GetSize();
	float GetRotation();
	void SetSize(float x, float y);
	void SetCamera(Camera camera);
	void SetRotation(float rate);
	void Update(float dt);
	void Draw()const;
	float getAlpha();
	void setAlpha(float zeroToOne);
	void setShader(int id);

	int getShaderIndex()
	{
		return sID;
		//return render->getShaderIndex();
	}

private:
	Render* render;
	glm::vec2 rcenter;
	glm::vec2 rsize;
	float rrate;
	Camera rcamera;

  int tID = 0; // texture ID
  GLuint sID = 0;

  float alpha;
};

#endif