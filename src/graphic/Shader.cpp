#include <iostream>
#include <string>
#include "Shader.h"

GLuint ShaderArray[Shader_Last]; 
Location location[Shader_Last]; 

char* StringReadFromFile(const char* filename)
{
	FILE* fp;
	long int FileSize;
	char* string;

	fopen_s(&fp, filename, "rb");
	if (!fp)
	{
		return (char*)"error";
	}

	fseek(fp, 0, SEEK_END);
	FileSize = ftell(fp);

	fseek(fp, 0, SEEK_SET);

	string = new char[FileSize + 1];

	if (fread(string, FileSize, 1, fp) != 1)
	{
		fclose(fp);
		delete[] string;
		return (char*)"error";
	}

	fclose(fp);
	string[FileSize] = 0;
	return string;
}

static char* ShaderReadFromFile(const char * filename)
{
		return StringReadFromFile(filename);
}

static unsigned int ShaderCompile(GLenum shaderType, const char* filename)
{
		//Get the shader code from a file
		const char* shaderCode = ShaderReadFromFile(filename);
		if (strcmp(shaderCode, "error") == 0)
		{
				std::cout << "Shader has error reading file: " << filename << std::endl;
		}

		//create the shader from the code
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &shaderCode, NULL);
		glCompileShader(shader);

		//delete the now pointless code
		delete[] shaderCode;

		//ERROR HANDLING
		GLint errorResult;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &errorResult);
		if (errorResult == GL_FALSE)
		{
				GLint size;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
				GLchar *message = new GLchar[size + 1];
				glGetShaderInfoLog(shader, size, &size, message);

				std::cout << filename << ": " << std::endl << message << std::endl;

				delete[] message;
				glDeleteShader(shader);
				return 0;
		}

		return shader;
}

GLuint ShaderCreate(const char* vertexFile, const char* fragmentFile)
{
		GLuint program = glCreateProgram();
		GLuint vertShader = ShaderCompile(GL_VERTEX_SHADER, vertexFile);
		GLuint fragShader = ShaderCompile(GL_FRAGMENT_SHADER, fragmentFile);

		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		return program;
}

void ShaderInit()
{
		ShaderArray[Shader_BasicColor] = ShaderCreate("./data/shaders/Vert_Default.txt", "./data/shaders/Frag_Col.txt");
		ShaderArray[Shader_BasicTexture] = ShaderCreate("./data/shaders/Vert_Default.txt", "./data/shaders/Frag_Tex.txt");
		SetAddress();
}

void ShaderShutdown()
{
		for (int i = Shader_StartOfList + 1; i < Shader_Last; i++)
				glDeleteProgram(ShaderArray[i]);
}

void SetAddress()
{
	for(int i = 0; i < Shader_Last; i ++)
	{
		location[i].uColor = glGetUniformLocation(ShaderArray[i], "uColor");
		location[i].utransform = glGetUniformLocation(ShaderArray[i], "transform");
		location[i].uview = glGetUniformLocation(ShaderArray[i], "view");
		location[i].uprojection = glGetUniformLocation(ShaderArray[i], "projection");
		location[i].image_alpha = glGetUniformLocation(ShaderArray[i], "image_alpha");
	}
}
