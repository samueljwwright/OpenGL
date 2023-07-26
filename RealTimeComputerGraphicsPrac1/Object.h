#ifndef OBJECT_H
#define OBJECT_H
#include<iostream>
#include <vector>

//Each object in the scene will hold a refernce to a unique vbo, vao and ibo/ebo

class Object 
{
public: 
	Object();
	~Object();
	unsigned int vao, vbo, ibo;
	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;

	void CreateVertexBuffer();
	void CreateIndexBuffer();

	void bindBuffer();
};

#endif 

