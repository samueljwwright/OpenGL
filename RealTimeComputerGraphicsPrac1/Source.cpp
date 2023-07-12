#include "Source.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

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

	//Generate VAO
	glGenVertexArrays(1, &a->vao);
	glBindVertexArray(a->vao);

	//Generate VBO
	glGenBuffers(1, &a->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, a->vbo);
	glBufferData(GL_ARRAY_BUFFER, a->vertexData.size() * sizeof(float), a->vertexData.data(), GL_STATIC_DRAW);
	
	//Generate IBO
	glGenBuffers(1, &a->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, a->indexData.size() * sizeof(unsigned int), a->indexData.data(), GL_STATIC_DRAW);

	//Setup VAO, VBO association
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	
	//ARGS FOR ABOVE {VBO,VAO,IBO, VERTEX DATA & SIZE, INDEX DATA & SIZE, {GLPARAMS} = KEEP CONSTANT}


	//SHADERS TO BE MOVED TO RESOURCE FOLDERS

	//shaders written as strings to allow for ease of formatting (using R e.t.c)
	std::string vertexShaderStandard = 
		R"(
			#version 330 core

			layout(location = 0) in vec4 position;			

			void main()
			{
				gl_Position = position;
			}
		)";

	std::string fragmentShaderStandard =
		R"(
			#version 330 core

			layout(location = 0) out vec4 color;			

			void main()
			{
				color = vec4(1.0, 0.0, 0.0, 1.0);
			}
		)";


	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fsPointer = fragmentShaderStandard.c_str();
	glShaderSource(fs, 1, &fsPointer, nullptr);
	glCompileShader(fs);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);


	glBindBuffer(GL_ARRAY_BUFFER, 0); //FOR TESTING VAO (WORKING AS OF NOW)
	glBindVertexArray(0);			  //
									  //

	while (!glfwWindowShouldClose(window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		

		glBindVertexArray(a->vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

