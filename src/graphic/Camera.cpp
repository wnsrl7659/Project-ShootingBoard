#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>

Camera mainCam(glm::vec2(0, 0), glm::vec2(0, 1), 700.0f, 500.0f);

Camera::Camera(void)
{
	rect_width = 2.0f;
	rect_height = 2.0f;

	right_vector.x = 1;
	up_vector.y = 1;
}

Camera::~Camera(void)
{
}

Camera::Camera(const glm::vec2& C, const glm::vec2& v, float W, float H)
{
	center_point = C;

	up_vector = v;

	// -90 degree = -1.5708f
	// u = r(-90degree)*v;
	if (v.x == 0)
	{
		right_vector.x = up_vector.y;
		right_vector.y = up_vector.x;
	}
	else
	{
		right_vector = glm::rotate(v, -1.5708f);
	}

	rect_width = W;
	rect_height = H;
}

void Camera::Update(float dt)
{
}

glm::vec2 Camera::center(void) const
{
	return center_point;
}

glm::vec2 Camera::right(void) const
{
	return right_vector;
}

glm::vec2 Camera::up(void) const
{
	return up_vector;
}

float Camera::width(void) const
{
	return rect_width;
}

float Camera::height(void) const
{
	return rect_height;
}

Camera& Camera::moveRight(float x)
{
	//c<-c+xu
	center_point = center_point + x * right_vector;
	return *this;
}

Camera& Camera::moveUp(float y)
{
	//c<-c+xv
	center_point = center_point + y * up_vector;
	return *this;
}

Camera& Camera::rotate(float t)
{
	//u<-r(t)*u
	//v<-r(t)*v
	right_vector = glm::rotate(right_vector, t);
	up_vector = glm::rotate(up_vector, t);
	return *this;
}

Camera& Camera::zoom(float f)
{
	//W<-fW
	//W<-fH
	rect_width = f * rect_width;
	rect_height = f * rect_height;
	return *this;
}

void Camera::SetPosition(float x, float y)
{
	center_point.x = x;
	center_point.y = y;
}
float* Camera::GetPosition()
{
	float pos[2];
	pos[0] = center_point.x;
	pos[1] = center_point.y;
	return pos;
}

void Camera::SetRotation(float r)
{
	right_vector = glm ::rotate(glm::vec2(1, 0), r);
	up_vector = glm::rotate(glm::vec2(0, 1), r);
}

void Camera::SetZoom(float f)
{
	rect_width = f * 1728.0f;
	rect_height = f * 1120.0f;
}

glm::mat3 cameraToWorld(const Camera& cam)
{
	//Mc = [u|v|c]
	glm::mat3 L = {};

	L[0][0] = cam.right().x;
	L[0][1] = cam.right().y;
	L[0][2] = 0;
	L[1][0] = cam.up().x;
	L[1][1] = cam.up().y;
	L[1][2] = 0;
	L[2][0] = cam.center().x;
	L[2][1] = cam.center().y;
	L[2][2] = 1;

	return L;
}

glm::mat3 worldToCamera(const Camera& cam)
{
	//V = Mc^-1
	glm::mat3 L = glm::inverse(cameraToWorld(cam));
	return L;
}

glm::mat3 cameraToNDC(const Camera& cam)
{
	glm::mat3 L = {};
	L[0][0] = 2.0f / cam.width();
	L[1][1] = 2.0f / cam.height();
	L[2][2] = 1;

	return L;
}

glm::mat3 NDCToCamera(const Camera& cam)
{
	glm::mat3 L = {};
	L[0][0] = cam.width() / 2.0f;
	L[1][1] = cam.height() / 2.0f;
	L[2][2] = 1;
	return L;
}
