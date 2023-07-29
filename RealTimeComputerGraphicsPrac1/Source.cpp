#include "Source.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "Shader.h"
#include "ObjLoader.h"



#include <ctime>

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

    window = glfwCreateWindow(1080  , 720, "RTGC", NULL, NULL);
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

    //OBJECT 1

    Object* a = new Object("test.png");

    ObjLoader loader;
    objData b = loader.LoadObjectVertexData("Cube");

    a->indexData = b.indices;
    a->vertexData = b.combinedData;

    a->CreateVertexArrayObject();
    a->CreateVertexBuffer();
    a->CreateIndexBuffer();
    a->bindObject();


    //OBJECT 2

    Object* c = new Object("Test2.png");

    objData d = loader.LoadObjectVertexData("monk");

    c->indexData = d.indices;
    c->vertexData = d.combinedData;

    //second obj
    c->CreateVertexArrayObject();
    c->CreateVertexBuffer();
    c->CreateIndexBuffer();
    c->bindObject();


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

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);


    //Lighting
    struct DirectionalLight {
        glm::vec4 lightColour = { 0.0f, 1.0f, 1.0f, 1.0f };
        glm::vec4 lightPosition = { 0.0f, -2.0f, 0.0f, 1.0f };
    };
    DirectionalLight light;
    //std::cout << light.lightPosition.x;   `
    //glm::vec4 l = glm::normalize(light.lightPosition);
    //std::cout << l.x;

    glUniform4f(glGetUniformLocation(shaderProgram, "lightColour"), light.lightColour.x, light.lightColour.y, light.lightColour.z, light.lightColour.w);
    glUniform3f(glGetUniformLocation(shaderProgram, "lightPosition"), light.lightPosition.x, light.lightPosition.y, light.lightPosition.z);

    glUniform3f(glGetUniformLocation(shaderProgram, "camPosition"), viewMatrix[3][0], viewMatrix[3][1], viewMatrix[3][2]);
    
    //std::cout<< viewMatrix[3][0] << viewMatrix[3][1] << viewMatrix[3][2] << std::endl;
    
    


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);


        unsigned int modelMatrixLocation = glGetUniformLocation(shaderProgram, "model_matrix");

        //light.lightPosition.x += (.2f * (float)glfwGetTime());

        a->transform = glm::mat4(1.0f); // mumst be set for all objects in loop for proper transform simulations
        a->transform = glm::translate(a->transform, glm::vec3(-3.0f, 0.0f, 0.0f)); 
        a->transform = glm::rotate(a->transform, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));


        c->transform = glm::mat4(1.0f);
        c->transform = glm::rotate(c->transform, (float)glfwGetTime(), glm::vec3(2.0f, 2.0f, 0.0f));
        

        a->bindObject();

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &a->transform[0][0]);
        glDrawElements(GL_TRIANGLES, a->indexData.size(), GL_UNSIGNED_INT, nullptr);

        
        c->bindObject();

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &c->transform[0][0]);
        glDrawElements(GL_TRIANGLES, c->indexData.size(), GL_UNSIGNED_INT, nullptr);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
