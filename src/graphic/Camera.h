#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Mesh.h"


class Camera {
public:
	Camera(void);
	Camera(const glm::vec2& C, const glm::vec2& v, float W, float H);

	~Camera(void);

	void Update(float dt);

	glm::vec2 center(void) const;
	glm::vec2 right(void) const;
	glm::vec2 up(void) const;
	float width(void) const;
	float height(void) const;
	Camera& moveRight(float x);
	Camera& moveUp(float y);
	Camera& rotate(float t);
	Camera& zoom(float f);
	void SetPosition(float x, float y);
	float* GetPosition();
	void SetRotation(float r);
	void SetZoom(float f);
private:
	float rect_width;
	float rect_height;

	glm::vec2 right_vector;
	glm::vec2 up_vector;

	glm::vec2 center_point;
};

glm::mat3 cameraToWorld(const Camera& cam);
glm::mat3 worldToCamera(const Camera& cam);
glm::mat3 cameraToNDC(const Camera& cam);
glm::mat3 NDCToCamera(const Camera& cam);

extern Camera mainCam;

#endif

