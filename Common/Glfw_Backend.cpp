#include <Windows.h>
#include <stdio.h>
#include "Glfw_Backend.h"
#include<iostream>


static ICallbacks* s_pCallbacks = NULL;
static GLFWwindow* s_pWindow = NULL;
float lastX = (float)1920 / 2.0;
float lastY = (float)1080 / 2.0;
bool firstMouse = true;

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	s_pCallbacks->mouse_callback(xpos, ypos);	
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	s_pCallbacks->scroll_callback(xoffset, yoffset);
}

static void KeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{  
	if (key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(pWindow, true);
		return;
	}
	bool state = (action == GLFW_PRESS) ? true : false;	 
	s_pCallbacks->KeyboardCB(key, state);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
static void InitCallbacks()
{
	//glfwMakeContextCurrent(s_pWindow);
	glfwSetFramebufferSizeCallback(s_pWindow, framebuffer_size_callback);
	glfwSetCursorPosCallback(s_pWindow, mouse_callback);
	glfwSetScrollCallback(s_pWindow, scroll_callback);
	glfwSetKeyCallback(s_pWindow, KeyCallback);
}

void GLFWErrorCallback(int error, const char* description)
{
#ifdef WIN32
	char msg[1000];
	_snprintf_s(msg, sizeof(msg), "GLFW error %d - %s", error, description);
	MessageBoxA(NULL, msg, NULL, 0);
#else
	fprintf(stderr, "GLFW error %d - %s", error, description);
#endif    
	exit(0);
}

void GLFWBackendInit(int argc, char** argv)
{   
	glfwSetErrorCallback(GLFWErrorCallback);
 
	if (glfwInit() != 1) {
		std::cout << "Error in Init" << std::endl;
		exit(1);
	}

	int Major, Minor, Rev;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif	
}


bool GLFWBackendCreateWindow(int Width, int Height, bool isFullScreen, const char* pTitle)
{   
	GLFWmonitor* pMonitor = isFullScreen ? glfwGetPrimaryMonitor() : NULL;
	s_pWindow  = glfwCreateWindow(Width, Height, pTitle, pMonitor, NULL);
	if (s_pWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(s_pWindow);	

	// Must be done after glfw is initialized!
	glewExperimental = GL_TRUE;
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::cout << glewGetErrorString(res) << std::endl;
		exit(1);
	}
	glfwSetInputMode(s_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	return (s_pWindow != NULL);
}

void GLFWBackendRun(ICallbacks* pCallbacks)
{
	if (!pCallbacks) {
		std::cout << "Call backs not specified" << std::endl;
		exit(1);
	}

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glFrontFace(GL_CW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);


	s_pCallbacks = pCallbacks;
	InitCallbacks();


	while (!glfwWindowShouldClose(s_pWindow)) {
		s_pCallbacks->RenderScene();
		glfwSwapBuffers(s_pWindow);
		glfwPollEvents();
	}
}

void GLFWBackendTerminate()
{
	glfwDestroyWindow(s_pWindow);
	glfwTerminate();
}


void GLFWBackendSwapBuffers()
{
	// Nothing to do here
}


void GLFWBackendLeaveMainLoop()
{
	glfwSetWindowShouldClose(s_pWindow, 1);
}


void GLFWBackendSetMousePos(int x, int y)
{
	glfwSetCursorPos(s_pWindow, (double)x, (double)y);
}