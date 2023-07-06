#include "Source.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() 
{
	Source source;
	source.WindowInit();
	
	return 0;
}

int Source::WindowInit() 
{
	GLFWwindow* window;

	if (!glfwInit()) {
		return -1;
	}

	window = glfwCreateWindow(640,480, "RTGC", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	while (!glfwWindowShouldClose(window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

