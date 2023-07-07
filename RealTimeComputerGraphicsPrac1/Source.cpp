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
	
	float positions[]{
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	unsigned int Vertices[]{
		0, 1, 2,
		2, 3, 0
		
	};

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


	unsigned int bufferOne;
	glGenBuffers(1, &bufferOne);
	glBindBuffer(GL_ARRAY_BUFFER, bufferOne);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), positions, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), Vertices, GL_STATIC_DRAW);




	
	while (!glfwWindowShouldClose(window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT);

		
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

