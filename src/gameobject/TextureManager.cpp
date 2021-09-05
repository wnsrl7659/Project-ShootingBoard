#include "TextureManager.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

static Texture* texture = nullptr;

static int count = Tex_Count;

static char** path;

static GLuint* texture_buffer;

void TextureManagerInit()
{
	texture = (Texture*)calloc(count, sizeof(Texture));
	path = (char**)calloc(count, sizeof(char*));
	texture_buffer = (GLuint*)calloc(count, sizeof(GLuint));

	for (int i = 0; i < count; i++)
	{
		path[i] = (char*)calloc(100, sizeof(char));
	}

	strcpy_s(path[0], sizeof(char) * 100, "./data/resources/player.png");
	strcpy_s(path[1], sizeof(char) * 100, "./data/resources/enemy.png");
	strcpy_s(path[2], sizeof(char) * 100, "./data/resources/blue.png");
	strcpy_s(path[3], sizeof(char) * 100, "./data/resources/red.png");
	strcpy_s(path[4], sizeof(char) * 100, "./data/resources/uil.png");
	strcpy_s(path[5], sizeof(char) * 100, "./data/resources/uir.png");
	strcpy_s(path[6], sizeof(char) * 100, "./data/resources/wall.png");
	strcpy_s(path[7], sizeof(char) * 100, "./data/resources/grass.png");
	strcpy_s(path[8], sizeof(char) * 100, "./data/resources/lava.png");
	strcpy_s(path[9], sizeof(char) * 100, "./data/resources/mud.png");
	strcpy_s(path[10], sizeof(char) * 100, "./data/resources/DigiPenLogo.png");
	strcpy_s(path[11], sizeof(char) * 100, "./data/resources/menu.png");
	strcpy_s(path[12], sizeof(char) * 100, "./data/resources/win.png");
	strcpy_s(path[13], sizeof(char) * 100, "./data/resources/bullet.png");
	strcpy_s(path[14], sizeof(char) * 100, "./data/resources/fade.png");
	strcpy_s(path[15], sizeof(char) * 100, "./data/resources/doorA.png");
	strcpy_s(path[16], sizeof(char) * 100, "./data/resources/itemA.png");
	strcpy_s(path[17], sizeof(char) * 100, "./data/resources/scope.png");
	strcpy_s(path[18], sizeof(char) * 100, "./data/resources/doorB.png");
	strcpy_s(path[19], sizeof(char) * 100, "./data/resources/itemB.png");
	strcpy_s(path[20], sizeof(char) * 100, "./data/resources/ebullet.png");
	strcpy_s(path[21], sizeof(char) * 100, "./data/resources/credit.png");
	strcpy_s(path[22], sizeof(char) * 100, "./data/resources/team.png");

	/******************************************************************/
	stbi_set_flip_vertically_on_load(true);
	for (int i = 0; i < count; i++)
	{
		texture[i].data = stbi_load(path[i], &texture[i].width, &texture[i].height, &texture[i].nrChannels, STBI_rgb_alpha);

		if (!texture[i].data)
		{
			//fail
		}
	}

	TextureBufferInit();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TextureManagerShutdown()
{
	for (int i = 0; i < count; i++)
	{
		free(path[i]);
	}
	free(path);
	
	for (int i = 0; i < count; i++)
	{
		stbi_image_free(texture[i].data);
	}
	free(texture);
	free(texture_buffer);
}

GLuint GetTexture(const int id)
{
	if (texture[id].data)
	{
		if (texture_buffer[id])
		{
			return texture_buffer[id];
		}
	}
	return 0;
}

void TextureBufferInit()
{
	for (int i = 0; i < count; i++)
	{
		Texture* temp = &texture[i];
		//GLuint texture;
		glGenTextures(1, &texture_buffer[i]);
		glBindTexture(GL_TEXTURE_2D, texture_buffer[i]); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	
		// set the texture wrapping parameters
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//// load image, create texture and generate mipmaps
		//int width, height, nrChannels;

		//stbi_set_flip_vertically_on_load(true);
		//unsigned char *data = stbi_load(temp->path, &width, &height, &nrChannels, STBI_rgb_alpha);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, temp->width, temp->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, temp->data);
		GLenum result = glGetError();
		if (result != GLEW_OK)
		{
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}