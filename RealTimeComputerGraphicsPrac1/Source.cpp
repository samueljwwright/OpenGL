#include "Source.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "Shader.h"
#include "ObjLoader.h"
#include "Texture.h"



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

    a->indexData = b.indices;
    a->vertexData = b.combinedData;

    Object* c = new Object();

    objData d = loader.LoadObjectVertexData("monk");

    c->indexData = d.indices;
    c->vertexData = d.combinedData;

    //Generate VAO
    glGenVertexArrays(1, &a->vao);
    glBindVertexArray(a->vao);

    //Generate VBO
    a->CreateVertexBuffer();
    a->CreateIndexBuffer();
    a->bindBuffer();

    //POS
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); // change size to 6 for default cube
    //tex
    glEnableVertexAttribArray(1); //For default cube 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    


    glGenVertexArrays(1, &c->vao);
    glBindVertexArray(c->vao);

    //second obj
    c->CreateVertexBuffer();
    c->CreateIndexBuffer();
    c->bindBuffer();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); // change size to 6 for default cube
    //tex
    glEnableVertexAttribArray(1); //For default cube 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));


    //Setup VAO, VBO association

    //POS
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0); // change size to 6 for default cube
    //tex
    glEnableVertexAttribArray(1); //For default cube 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));

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

    //Textures
    Texture texture;
    texture.CreateTexture("test.png");


    unsigned int texID;

    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.w, texture.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.textureData);

    glEnable(GL_TEXTURE_2D);




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


        unsigned int modelMatrixLocation = glGetUniformLocation(shaderProgram, "model_matrix");


        //TODO Move object model matrix to object class and access from there....
        glm::mat4 modelMatrixA = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f)); 
        modelMatrixA = glm::rotate(modelMatrixA, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));

        glm::mat4 modelMatrixC = glm::mat4(1.0f);

        glBindVertexArray(a->vao);
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrixA[0][0]);
        glDrawElements(GL_TRIANGLES, a->indexData.size(), GL_UNSIGNED_INT, nullptr);

        
        glBindVertexArray(c->vao);
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrixC[0][0]);
        glDrawElements(GL_TRIANGLES, c->indexData.size(), GL_UNSIGNED_INT, nullptr);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
