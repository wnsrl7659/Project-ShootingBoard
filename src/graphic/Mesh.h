#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>

enum MeshList
{
	Mesh_Square = 0,

	Mesh_Count,
};

class Mesh {
public:
	Mesh(MeshList id);
	~Mesh();
	int vertexCount(void);
	const glm::vec2* vertexArray(void);
	glm::vec2 dimensions(void);
	glm::vec2 center(void);
	int faceCount(void);
	const glm::vec3* faceArray(void);
	int edgeCount(void);
	const glm::vec2* edgeArray(void);
	const glm::vec3* colorArray(void);
	const glm::vec2* textArray(void);
private:
	glm::vec2* vertices;
	glm::vec3* faces;
	glm::vec2* edges;
	glm::vec3* colors;
	glm::vec2* texts;
	int vCount, fCount, eCount;
	glm::vec2 cen;
	glm::vec2 dim;

};
