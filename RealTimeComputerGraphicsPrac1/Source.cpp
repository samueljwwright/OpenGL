#include "Source.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "Shader.h"
#include "ObjLoader.h"


#include <windows.h>
constexpr int W_KEY = 0x57;
constexpr int S_KEY = 0x53;
constexpr int A_KEY = 0x41;
constexpr int D_KEY = 0x44;
constexpr int SHIFT_KEY = 0x10;
constexpr int SPACE_KEY = 0x20;
constexpr int PRESSED_BIT_FLAG = 0x8000; //determines if key is currently pressed

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

    Object* a = new Object("Cube", "test.png");



    //OBJECT 2

    Object* c = new Object("Monkey2", "Test2.png");




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
        glm::vec4 lightColour = { 1.0f, 1.0f, 1.0f, 1.0f };
        glm::vec4 lightPosition = { 2.0f, -2.0f, 2.0f, 1.0f };
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

        a->transform = glm::mat4(1.0f); // mumst be set for all objects in loop for proper transform simulations
        a->transform = glm::translate(a->transform, glm::vec3(-3.0f, 0.0f, 0.0f));



        if (GetKeyState(W_KEY) & PRESSED_BIT_FLAG) // w define alias for keys
        {
            viewMatrix[3][2] += 0.001;
        }
        if (GetKeyState(S_KEY) & PRESSED_BIT_FLAG) //s
        {
            viewMatrix[3][2] -= 0.001;
        }
        if (GetKeyState(A_KEY) & PRESSED_BIT_FLAG) //a
        {
            viewMatrix[3][0] += 0.001;
        }
        if (GetKeyState(D_KEY) & PRESSED_BIT_FLAG) //d
        {
            viewMatrix[3][0] -= 0.001;
        }
        if (GetKeyState(SHIFT_KEY) & PRESSED_BIT_FLAG) //d
        {
            viewMatrix[3][1] += 0.001;
        }
        if (GetKeyState(SPACE_KEY) & PRESSED_BIT_FLAG) //d
        {
            viewMatrix[3][1] -= 0.001;
        }
        //Needed to update camera matrix each frame
        unsigned int viewMatrixLocation = glGetUniformLocation(shaderProgram, "view_matrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniform3f(glGetUniformLocation(shaderProgram, "camPosition"), viewMatrix[3][0], viewMatrix[3][1], viewMatrix[3][2]);

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
