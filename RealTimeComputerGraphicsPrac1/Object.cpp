#include "Object.h"


Object::Object(std::string ObjPath, std::string TexturePath)
{
    vao = 0;
    vbo = 0;
    ibo = 0;
    transform = glm::mat4(1.0f);

    
    objData temp =  loader.LoadObjectVertexData(ObjPath);
    vertexData = temp.combinedData;
    indexData = temp.indices;
    texture.CreateTexture(TexturePath, TextureID);

    CreateVertexArrayObject();
    CreateVertexBuffer();
    CreateIndexBuffer();
    bindObject();
}

//call after vertex data has been added
void Object::CreateVertexBuffer() 
{
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    //VAO MUST BE BOUND BEFORE. code below is vao dependent.

    //all objects have the same vao configuration

    //POS
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0); // change size to 6 for default cube
    //tex
    glEnableVertexAttribArray(1); //For default cube 
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    //normals
    glEnableVertexAttribArray(2);  
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 5));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Object::bindObject() 
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    texture.useTexture(TextureID); //ISSIE HERE
    //std::cout << "TEX ID::  :: " << TextureID << std::endl;
    
}

void Object::CreateIndexBuffer() 
{
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(unsigned int), indexData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::CreateVertexArrayObject() 
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}