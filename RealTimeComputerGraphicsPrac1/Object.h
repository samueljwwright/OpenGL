#ifndef OBJECT_H
#define OBJECT_H
#include<iostream>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"
//Each object in the scene will hold a refernce to a unique vbo, vao and ibo/ebo

class Object 
{
public: 
	Object(std::string TexturePath);
	~Object();
	unsigned int vao, vbo, ibo;
	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;
	glm::mat4 transform;
	unsigned int TextureID;


	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateVertexArrayObject();

	void bindObject();

private:
	Texture texture;
};

#endif 

