#ifndef SHADER_H
#define SHADER_H

#pragma once
#include <GL/glew.h>

enum ShaderList
{
	Shader_BasicColor = 0,
	Shader_BasicTexture,

	Shader_Last,
	Shader_StartOfList = -1,
};

typedef struct Location {

	GLint uColor;      
	GLint utransform;  
	GLint uview;       
	GLint uprojection; 
	GLint image_alpha; 
}Location;

extern GLuint ShaderArray[Shader_Last]; 
extern Location location[Shader_Last];  

static char* ShaderReadFromFile(const char * filename);

static unsigned int ShaderCompile(GLenum shaderType, const char* shaderCode);

GLuint ShaderCreate(const char* vertex, const char* fragment);

void ShaderInit();

void ShaderShutdown();

void SetAddress();

#endif 
