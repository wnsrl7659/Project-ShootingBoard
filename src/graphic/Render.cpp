#include "Render.h"
#include "Shader.h"
#include <iostream>
#include <glm/gtx/matrix_transform_2d.hpp>

static glm::mat3 origin = {};

Render::Render(int shader)
{
	origin[0][0] = 1;
	origin[1][1] = 1;
	origin[2][2] = 1;

	program = ShaderArray[shader];
	shaderIndex = shader;

	//Set the value of private data members 
	utransform = location[shader].utransform;
	uview = location[shader].uview;
	uprojection = location[shader].uprojection;
	ualpha = location[shader].image_alpha;
	ucolor = location[shader].uColor;

	image_alpha = 1.0f;
	//Set various guaranteed Uniforms here
	glUniform1f(location[shader].image_alpha, image_alpha);

	transform = origin;
	rscale = origin;
	rotation = origin;
}

Render::~Render(void)
{
}

void Render::clearFrame(const glm::vec3& c)
{
	//clear background
	//glClearColor(c.x, c.y, c.w, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render::setModelToWorld(Camera camera)
{
	glm::mat3 M = transform * rotation * rscale;
	glm::mat3 V = worldToCamera(camera);
	glm::mat3 P = cameraToNDC(camera);

	//Viewport Version
	//Affine P = scale(2.0f / Vwidth, 2.0f / Vheight);

	// select vertex buffer
	glUseProgram(program);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	// set vertex transformation
	float R[9] = { M[0][0], M[1][0], M[2][0],
					 M[0][1], M[1][1], M[2][1],
					 M[0][2], M[1][2], M[2][2] };
	float C[9] = { V[0][0], V[1][0], V[2][0],
					 V[0][1], V[1][1], V[2][1],
					 V[0][2], V[1][2], V[2][2] };
	float O[9] = { P[0][0], P[1][0], P[2][0],
					 P[0][1], P[1][1], P[2][1],
					 P[0][2], P[1][2], P[2][2] };

	GLint uniformLocation = location[shaderIndex].utransform;
	if (uniformLocation != -1)
		glUniformMatrix3fv(uniformLocation, 1, true, R);
	uniformLocation = location[shaderIndex].uview;
	if (uniformLocation != -1)
		glUniformMatrix3fv(uniformLocation, 1, true, C);
	uniformLocation = location[shaderIndex].uprojection;
	if (uniformLocation != -1)
		glUniformMatrix3fv(uniformLocation, 1, true, O);
}

void Render::loadMesh(int id)
{
	Buffer* temp = GetBuffer(id);
	vertex_buffer = temp->vertex_buffer;
	face_buffer = temp->face_buffer;
	vertex_array = temp->vertex_array;
	vertex_aarray = temp->vertex_aarray;
	edge_buffer = temp->edge_buffer;
	mesh_edge_count = temp->mesh_edge_count;
	mesh_face_count = temp->mesh_face_count;
}

void Render::unloadMesh(void)
{
	//mesh manager
}

void Render::loadTexture(const int id)
{
	texture_buffer = GetTexture(id);
}
int Render::getTexture()
{
	return texture_buffer;
}

void Render::displayEdges(const glm::vec3& c)
{
	// draw edges
	float color[3] = { c.x, c.y, c.z };
	glUniform3f(ucolor, color[0], color[1], color[2]);
	glBindVertexArray(vertex_aarray);
	glDrawElements(GL_LINES, mesh_edge_count * 2, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Render::displayFaces(const glm::vec3& c)
{
	// draw faces
	glBindVertexArray(vertex_array);
	glDrawElements(GL_TRIANGLES, mesh_face_count * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Render::displayTexture(void)
{
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture_buffer);

	glBindVertexArray(vertex_array);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Render::setTransform(float X, float Y)
{
	transform = origin;
	transform[2][0] = X;
	transform[2][1] = Y;
}

void Render::setShader(int id)
{
	program = ShaderArray[id];
	shaderIndex = id;
}

void Render::setScale(float ratex, float ratey)
{
	rscale = origin;
	rscale[0][0] = ratex;
	rscale[1][1] = ratey;
}

void Render::setRotate(float rate)
{
	glm::mat3 tempM = origin;
	rotation = glm::rotate(tempM, rate);
}

GLuint Render::getShader()
{
	return program;
}

float Render::getAlpha()
{
	return image_alpha;
}

void Render::setAlphaUniform()
{
	glUniform1f(location[shaderIndex].image_alpha, image_alpha);
}

void Render::setAlpha(float zeroToOne)
{
	image_alpha = zeroToOne;
}