#pragma once

#include <include/GLEW/glew.h>
#include <include/GLFW/glfw3.h>
#include <include/VX/def.h>

GLFWwindow* VXNewWindow(u32 width, u32 height, char* title);
VXResult VXDelWindow(GLFWwindow* window);
