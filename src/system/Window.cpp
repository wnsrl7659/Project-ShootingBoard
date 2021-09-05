#include "Window.h"
#include "SBEngine.h"
#include "../graphic/Camera.h"


static GLFWwindow* window;
static void fbsize_cb(GLFWwindow* pwin, int width, int height);
void processInput(GLFWwindow* window);

static GLFWmonitor* monitor;
static const GLFWvidmode* mode;

const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 500;


void WindowInit()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	bool startFullscreen = true;

	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode(monitor);

	if (startFullscreen)
		window = glfwCreateWindow(mode->width, mode->height, "Shooting Board", monitor, NULL);
	else
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shooting Board", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, fbsize_cb);

	glewInit();

}


void WindowUpdate(float dt)
{
	processInput(window);

	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window); //swap buffer will change position !!!!!
	glfwPollEvents();

	if (glfwWindowShouldClose(window))
	{
		delete pEngine;
		pEngine = nullptr;
	}
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

static void fbsize_cb(GLFWwindow* pwin, int width, int height) {
	glViewport(0, 0, width, height);
}

void WindowShutdown()
{
	glfwTerminate();
}

GLFWwindow* GetWindow()
{
	return window;
}

const GLFWvidmode* GetMode()
{
	return mode;
}
GLFWmonitor* GetMonitor()
{
	return monitor;
}


void GetCursorPosition(float* x, float* y)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);


	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (xpos < 0 || ypos < 0 || xpos > width || ypos > height)
	{
		*x = 9999;
		*y = 9999;
		return;
	}
	int halfw = width / 2;
	int halfh = height / 2;

	float xratio = (float)SCR_WIDTH / (float)width;
	float yratio = (float)SCR_HEIGHT / (float)height;

	if (xpos == halfw && ypos == halfh)
	{
		*x = 0 + mainCam.GetPosition()[0];
		*y = 0 + mainCam.GetPosition()[1];
	}
	else if (xpos < halfw && ypos < halfh)
	{
		*x = -(halfw - (int)xpos) * xratio + mainCam.GetPosition()[0];
		*y = (halfh - (int)ypos) * yratio + mainCam.GetPosition()[1];
	}
	else if (xpos > halfw && ypos < halfh)
	{
		*x = ((int)xpos - halfw) * xratio + mainCam.GetPosition()[0];
		*y = (halfh - (int)ypos) * yratio + mainCam.GetPosition()[1];
	}
	else if (xpos > halfw && ypos > halfh)
	{
		*x = ((int)xpos - halfw) * xratio + mainCam.GetPosition()[0];
		*y = -((int)ypos - halfh) * yratio + mainCam.GetPosition()[1];
	}
	else if (xpos < halfw && ypos > halfh)
	{
		*x = -(halfw - (int)xpos) * xratio + mainCam.GetPosition()[0];
		*y = -((int)ypos - halfh) * yratio + mainCam.GetPosition()[1];
	}

}