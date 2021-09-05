#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <GL/glew.h> //Include first
#include <GL/gl.h> 
#include <GLFW/glfw3.h>

typedef struct Buffer {
	GLuint vertex_array;
	GLuint vertex_buffer;
	GLuint vertex_aarray;
	GLuint face_buffer;
	GLuint edge_buffer;
	int mesh_edge_count;
	int	mesh_face_count;
}Buffer;


void MeshManagerInit();

void MeshManagerUpdate(float dt);

void MeshManagerShutdown();

void CreateBuffer(int id);

Buffer* GetBuffer(const int id);

#endif

