#include "Source.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "Shader.h"
#include "ObjLoader.h"

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

    window = glfwCreateWindow(640, 480, "RTGC", NULL, NULL);
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

    //////////////////////////////////////////////////////////////

    Object* a = new Object();

    ObjLoader loader;
    objData b = loader.LoadObjectVertexData("Cube");

    a->indexData = b.Positionindex;
    a->vertexData = b.vertexData;

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0); // change size to 6 for default cube
    //COL
    //glEnableVertexAttribArray(1); //For default cube 
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

    //SHADERS
    Shader s;
    std::string VertexShaderPath = "Standard_VertexShader";
    std::string FragmentShaderPath = "Standard_FragmentShader";

    //Compile shaders
    unsigned int vs = s.CompileShader(GL_VERTEX_SHADER, VertexShaderPath);

    unsigned int fs = s.CompileShader(GL_FRAGMENT_SHADER, FragmentShaderPath);

    //Shader Program
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vs); //Attach Vertex shader
    glAttachShader(shaderProgram, fs); //Attach Fragment shader

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // VIEW MAT
    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, -5.0f), //Position
        glm::vec3(0.0f, 0.0f, 0.0f), //Target 
        glm::vec3(0.0f, 1.0f, 0.0f)  //up vector
    );

    unsigned int viewMatrixLocation = glGetUniformLocation(shaderProgram, "view_matrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);

    //PROJECTION MAT
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);


    unsigned int projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projection_matrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

    //Clear buffers

    glBindBuffer(GL_ARRAY_BUFFER, 0); //FOR TESTING VAO (WORKING AS OF NOW)
    glBindVertexArray(0);              //

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(a->vao);
        glDrawElements(GL_TRIANGLES, a->indexData.size(), GL_UNSIGNED_INT, nullptr);

        //Rotation for debugging
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));

        //modelMatrix = glm::translate(modelMatrix,  glm::vec3(0.0f, 0.0f, 1.0f + (float)glfwGetTime()));

        unsigned int modelMatrixLocation = glGetUniformLocation(shaderProgram, "model_matrix");
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
