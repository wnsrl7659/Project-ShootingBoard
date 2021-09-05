#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <GL/glew.h> //Include first
#include <GL/gl.h> 
#include <GLFW/glfw3.h>

enum TextureList
{
	Tex_Player = 0,
	Tex_Enemy,
	Tex_Blue,
	Tex_Red,
	Tex_UIL,
	Tex_UIR,
	Tex_Wall,
	Tex_Grass,
	Tex_Lava,
	Tex_Mud,
	Tex_Logo,
	Tex_Menu,
	Tex_Win,
	Tex_Bullet,
	Tex_Fade,
	Tex_DoorA,
	Tex_ItemA,
	Tex_Scope,
	Tex_DoorB,
	Tex_ItemB,
	Tex_EBullet,
	Tex_Credit,
	Tex_Team,

	Tex_Count,
};


typedef struct Texture
{
	unsigned char * data = nullptr;
	int width = 0;
	int height = 0;
	int nrChannels = 0;
}Texture;


void TextureManagerInit();

void TextureManagerUpdate(float dt);

void TextureManagerShutdown();

void TextureBufferInit();


GLuint GetTexture(const int id);



#endif

