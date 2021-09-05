#pragma once

#include <Windows.h>

#include <GL/glew.h> //first
#include <GL/gl.h> 
#include <GLFW/glfw3.h>
#include <string>


void WindowInit();

void WindowUpdate(float dt);

void WindowShutdown();

GLFWwindow* GetWindow();
GLFWmonitor* GetMonitor();
const GLFWvidmode* GetMode();

void GetCursorPosition(float* x, float* y);