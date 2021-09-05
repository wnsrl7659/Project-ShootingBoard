#pragma once

#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h> //Include first
#include <GL/gl.h> 
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "Camera.h"
#include "../gameobject/TextureManager.h"
#include "../gameobject/MeshManager.h"

//#include "../animation/animation.h"

class Render {
public:
	Render(int);
	~Render(void);
	void clearFrame(const glm::vec3& c);
	void setModelToWorld(Camera camera);
	void loadMesh(int id);
	void unloadMesh(void);
	void loadTexture(const int id);
	int getTexture();
	void displayEdges(const glm::vec3& c);
	void displayFaces(const glm::vec3& c);
	void displayTexture(void);
	void setTransform(float X, float Y);
	void setScale(float ratex, float ratey);
	void setRotate(float rate);
	void setShader(int id);
	GLuint getShader();
	float getAlpha();
	void setAlphaUniform();
	void setAlpha(float zeroToOne);
	GLuint getShaderIndex()
	{
		return shaderIndex;
	}

private:
	GLint utransform,
		uview,
		uprojection,
		ualpha,
		ucolor;
	GLuint program,
		vertex_buffer,
		edge_buffer,
		face_buffer,
		texture_buffer,
		vertex_array,
		vertex_aarray;

	glm::mat3 transform, rscale, rotation;

	int mesh_edge_count,
		mesh_face_count;

	float image_alpha; 
	int shaderIndex; 
};


#endif

