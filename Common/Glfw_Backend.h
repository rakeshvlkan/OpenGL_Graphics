#ifndef GLFW_BACKEND_H
#define GLFW_BACKEND_H
#include"CallBacks.h"
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include <stb_image.h>

void GLFWBackendInit(int argc, char** argv);

void GLFWBackendTerminate();

bool GLFWBackendCreateWindow(int Width, int Height, bool isFullScreen, const char* pTitle);

void GLFWBackendRun(ICallbacks* pCallbacks);

void GLFWBackendSwapBuffers();

void GLFWBackendLeaveMainLoop();

#endif

