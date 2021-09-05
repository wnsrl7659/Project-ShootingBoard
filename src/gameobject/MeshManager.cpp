#include "MeshManager.h"
#include "../graphic/Mesh.h"

static const int meshcount = 1;

static Buffer buffer[meshcount];
static Mesh* mesh[meshcount];
static Mesh square(Mesh_Square);

void MeshManagerInit()
{
	mesh[0] = &square;
	CreateBuffer(0);
}

void MeshManagerShutdown()
{
	for (int i = 0; i < meshcount; i++)
	{
		glDeleteBuffers(1, &buffer[i].face_buffer);
		glDeleteBuffers(1, &buffer[i].edge_buffer);
		glDeleteBuffers(1, &buffer[i].vertex_buffer);
		glDeleteVertexArrays(1, &buffer[i].vertex_array);
		glDeleteVertexArrays(1, &buffer[i].vertex_aarray);
	}
}

void CreateBuffer(int id)
{
	int i;
	
	GLfloat *vertices = new GLfloat[mesh[id]->vertexCount() * 8];
	for (i = 0; i < mesh[id]->vertexCount(); i++)
	{
		vertices[(i * 8)] = mesh[id]->vertexArray()[i].x;
		vertices[(i * 8 + 1)] = mesh[id]->vertexArray()[i].y;
		vertices[(i * 8 + 2)] = 1; // z value
		vertices[(i * 8 + 3)] = mesh[id]->colorArray()[i].x;
		vertices[(i * 8 + 4)] = mesh[id]->colorArray()[i].y;
		vertices[(i * 8 + 5)] = mesh[id]->colorArray()[i].z;
		vertices[(i * 8 + 6)] = mesh[id]->textArray()[i].x;
		vertices[(i * 8 + 7)] = mesh[id]->textArray()[i].y;
	}

	buffer[id].mesh_edge_count = mesh[id]->edgeCount();
	GLuint *edges = new GLuint[mesh[id]->edgeCount() * 2];
	for (i = 0; i < mesh[id]->edgeCount(); i++)
	{
		edges[(i * 2)] = (GLuint)mesh[id]->edgeArray()[i].x;
		edges[(i * 2 + 1)] = (GLuint)mesh[id]->edgeArray()[i].y;
	}

	buffer[id].mesh_face_count = mesh[id]->faceCount();
	GLuint *faces = new GLuint[mesh[id]->faceCount() * 3];
	for (i = 0; i < mesh[id]->faceCount(); i++)
	{
		faces[(i * 3)] = (GLuint)mesh[id]->faceArray()[i].x;
		faces[(i * 3 + 1)] = (GLuint)mesh[id]->faceArray()[i].y;
		faces[(i * 3 + 2)] = (GLuint)mesh[id]->faceArray()[i].z;
	}

	glGenVertexArrays(1, &buffer[id].vertex_array);
	glBindVertexArray(buffer[id].vertex_array);

	glGenBuffers(1, &buffer[id].vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[id].vertex_buffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*mesh[id]->vertexCount() * 8, vertices, GL_STATIC_DRAW);

	//Tell the vertex shader whats in the Buffer
	//Vertex Attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//Color Attrib
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texcoordinate Attrib
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// face list buffer
	glGenBuffers(1, &buffer[id].face_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[id].face_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*mesh[id]->faceCount() * 3, faces, GL_STATIC_DRAW);

	glBindVertexArray(0);
	
	/******************************************************************************************/

	glGenVertexArrays(1, &buffer[id].vertex_aarray);
	glBindVertexArray(buffer[id].vertex_aarray);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[id].vertex_buffer);

	//Tell the vertex shader whats in the Buffer
	//Vertex Attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	//Color Attrib
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texcoordinate Attrib
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// edge list buffer
	glGenBuffers(1, &buffer[id].edge_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[id].edge_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*mesh[id]->edgeCount() * 2, edges, GL_STATIC_DRAW);

	glBindVertexArray(0);


	delete[](edges);

	delete[](vertices);
	delete[](faces);
}

Buffer* GetBuffer(const int id)
{
	return &buffer[id];
}