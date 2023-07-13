#include "Source.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "Shader.h"

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

		//POS
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
		//COL
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));


		//shaders written as strings to allow for ease of formatting (using R e.t.c)
		std::string vertexShaderStandard =
			R"(
				#version 330 core

				layout(location = 0) in vec4 position;
				layout(location = 1) in vec3 color; // Added color attribute

				uniform mat4 model_matrix;

				out vec3 vertexColor; // Output color to fragment shader

				void main()
				{
					gl_Position = position * model_matrix;
					vertexColor = color; // Pass color to fragment shader
				}
			)";

		std::string fragmentShaderStandard =
			R"(
				#version 330 core

				layout(location = 0) out vec4 fragColor;

				in vec3 vertexColor; // Input color from vertex shader

				void main()
				{
					fragColor = vec4(vertexColor, 1.0);
				}
			)";

		//VERTEX SHADER COMPILE
		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		const char* vsPointer = vertexShaderStandard.c_str();
		glShaderSource(vs, 1, &vsPointer, nullptr);
		glCompileShader(vs);

		//take uint type gl_vertex_shader , const std::string& pathname /(vertexshaderstandard) , return vs

		//FRAGMENT SHADER COMPILE
		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fsPointer = fragmentShaderStandard.c_str();
		glShaderSource(fs, 1, &fsPointer, nullptr);
		glCompileShader(fs);


		//Shader Program
		unsigned int shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vs); //Attach Vertex shader
		glAttachShader(shaderProgram, fs); //Attach Fragment shader

		glLinkProgram(shaderProgram);

		glUseProgram(shaderProgram);


		Shader s;
		std::string sd = "Standard_VertexShader";
		s.CompileShader(GL_VERTEX_SHADER, sd);





		glBindBuffer(GL_ARRAY_BUFFER, 0); //FOR TESTING VAO (WORKING AS OF NOW)
		glBindVertexArray(0);			  //
										  //

		while (!glfwWindowShouldClose(window)) 
		{
			glClear(GL_COLOR_BUFFER_BIT);
		

			glBindVertexArray(a->vao);
			glDrawElements(GL_TRIANGLES, a->indexData.size(), GL_UNSIGNED_INT, nullptr);
			
			//Rotation for debugging
			glm::mat4 model_mat = glm::mat4(1.0f);
			model_mat = glm::rotate(model_mat, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
			unsigned int model_mat_location = glGetUniformLocation(shaderProgram, "model_matrix");
			glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, &model_mat[0][0]); //Last arg provides pointer to first element of the mat (glm::value_ptr not available)

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
		glfwTerminate();
		return 0;
	}

