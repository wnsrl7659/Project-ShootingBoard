#include "Sprite.h"
#include <iostream>
#include "../physics/Transform.h"
#include "Shader.h"

Sprite::Sprite()
{
	rrate = 0;
	alpha = 1.0f;
}

void Sprite::Init(int shader)
{
	if (shader != 99)
	{
		render = new Render(shader);
		sID = shader;
	}
}

Sprite::~Sprite()
{
	delete render;
}

void Sprite::SetTexture(const int id)
{
	tID = id;
}

int Sprite::GetTexture()
{
	return tID;
}

void Sprite::SetPosition(float x, float y)
{
	rcenter.x = x;
	rcenter.y = y;
}

glm::vec2 Sprite::GetPosition()
{
	return rcenter;
}

int Sprite::GetShader()
{
	return sID;
}

void Sprite::SetSize(float x, float y)
{
	rsize.x = x;
	rsize.y = y;
}

glm::vec2 Sprite::GetSize()
{
	return rsize;
}

void Sprite::SetCamera(Camera camera)
{
	rcamera = camera;
}

void Sprite::SetRotation(float rate)
{
	rrate = rate;
}

float Sprite::GetRotation()
{
	return rrate;
}

void Sprite::setShader(int id)
{
	sID = id;
}

void Sprite::Update(float dt)
{
	//Animation* anim = owner->GetComponent<Animation>();

	//AddSprite(prior, sID, 0, tID,
	//	rcenter, rsize, rrate, alpha, anim, LR, color, owner);

	render->setShader(sID);
	render->loadMesh(Mesh_Square);
	render->loadTexture(tID);
	render->setTransform(rcenter.x, rcenter.y);
	render->setScale(rsize.x, rsize.y);
	render->setRotate(rrate);
	render->setModelToWorld(mainCam);
	render->setAlpha(alpha);
	render->setAlphaUniform();

	glUseProgram(render->getShader());
	render->displayTexture();
}

void Sprite::Draw()const
{
}

float Sprite::getAlpha()
{ 
	return alpha;
}

void Sprite::setAlpha(float zeroToOne)
{
	if (zeroToOne < 0)
		zeroToOne = 0;
	if (zeroToOne > 1)
		zeroToOne = 1;
	alpha = zeroToOne;
}
