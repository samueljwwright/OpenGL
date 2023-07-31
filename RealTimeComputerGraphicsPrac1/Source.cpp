#include "Source.h"

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

    //OBJECT 1

    Object* a = new Object("Hall", "hall.png"); //Obj file, Texture file

    //OBJECT 2

    Object* c = new Object("Monkey2", "test2.png");

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

    //enables transparency via blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



    // VIEW MAT
    viewMatrix = glm::lookAt(
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

    //Lighting

    DirectionalLight light;
    
    glUniform4f(glGetUniformLocation(shaderProgram, "lightColour"), light.lightColour.x, light.lightColour.y, light.lightColour.z, light.lightColour.w);
    glUniform3f(glGetUniformLocation(shaderProgram, "lightPosition"), light.lightPosition.x, light.lightPosition.y, light.lightPosition.z);


    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);


    
    //Scene setup
    setObject(a, glm::vec3(.0f, .0f, 0.0f), glm::vec3(0.f, 3.14f/2, 0.f));
    setObject(c, glm::vec3(-.0f, .0f, 3.0f), glm::vec3(.0f,3.14f,.0f));

    float lastFrame = (float)glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        input();

        glUseProgram(shaderProgram);

        //Needed to update camera matrix each frame
        unsigned int viewMatrixLocation = glGetUniformLocation(shaderProgram, "view_matrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        glUniform3f(glGetUniformLocation(shaderProgram, "camPosition"), viewMatrix[3][0], viewMatrix[3][1], viewMatrix[3][2]);


        c->transform = glm::rotate(c->transform, deltaTime * 2, glm::vec3(2.0f, 2.0f, 0.0f));

     
        unsigned int modelMatrixLocation = glGetUniformLocation(shaderProgram, "model_matrix");

        a->bindObject();
        renderObject(modelMatrixLocation, a->transform, a->indexData.size());
        c->bindObject();
        renderObject(modelMatrixLocation, c->transform, c->indexData.size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void Source::input() {
    if (GetKeyState(W_KEY) & PRESSED_BIT_FLAG) 
    {
        viewMatrix[3][2] += 0.001;
    }
    if (GetKeyState(S_KEY) & PRESSED_BIT_FLAG) 
    {
        viewMatrix[3][2] -= 0.001;
    }
    if (GetKeyState(A_KEY) & PRESSED_BIT_FLAG) 
    {
        viewMatrix[3][0] += 0.001;
        //viewMatrix = glm::rotate(viewMatrix, deltaTime * -2, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    if (GetKeyState(D_KEY) & PRESSED_BIT_FLAG) 
    {
        viewMatrix[3][0] -= 0.001;
    }
    if (GetKeyState(SHIFT_KEY) & PRESSED_BIT_FLAG) 
    {
        viewMatrix[3][1] += 0.001;
    }
    if (GetKeyState(SPACE_KEY) & PRESSED_BIT_FLAG) 
    {
        viewMatrix[3][1] -= 0.001;
    }
}

void Source::renderObject(unsigned int modelMatrixLocation, glm::mat4 objectTransfromReference, int indexDataSize)
{
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &objectTransfromReference[0][0]);
    glDrawElements(GL_TRIANGLES, indexDataSize, GL_UNSIGNED_INT, nullptr);
}

void Source::setObject(Object* object, glm::vec3 position, glm::vec3 rotation) //add scale as well
{
    object->transform = glm::mat4(1.0f);
    object->transform[3][0] = position.x;
    object->transform[3][1] = position.y;
    object->transform[3][2] = position.z;

    object->transform = glm::rotate(object->transform, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    object->transform = glm::rotate(object->transform, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    object->transform = glm::rotate(object->transform, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
}