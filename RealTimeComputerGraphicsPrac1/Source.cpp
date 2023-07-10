#include "Source.h"
#include <iostream>
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
	
	glfwMakeContextCurrent(window); //must come before glew init

	//glewExperimental = GL_TRUE; 
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::cout << "glew error" << std::endl;
	}


	Object* a = new Object();

	glGenVertexArrays(1, &a->vao);
	glBindVertexArray(a->vao);

	glGenBuffers(1, &a->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, a->vbo);
	glBufferData(GL_ARRAY_BUFFER, a->vertexData.size() * sizeof(float), a->vertexData.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	
	glGenBuffers(1, &a->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, a->indexData.size() * sizeof(unsigned int), a->indexData.data(), GL_STATIC_DRAW);
	
	while (!glfwWindowShouldClose(window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		glBindVertexArray(a->vao);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

