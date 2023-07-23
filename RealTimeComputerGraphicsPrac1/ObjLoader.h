#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <glm/glm.hpp>

struct objData 
{
	std::vector<float> combinedData;
	std::vector<unsigned int > indices;

	std::vector<float> vertexData;
	std::vector<float> textureData;
	std::vector<float> normalData;

	std::vector<unsigned int> Positionindex;
	std::vector<unsigned int> textureIndex;
	std::vector<unsigned int> normalIndex;
};

struct vertex 
{
	glm::vec3 postion;
	glm::vec2 UV;
};


class ObjLoader	
{
public:
	objData LoadObjectVertexData(const std::string& filePathName);
private:
	objData parseObjectData(std::ifstream& file);
	void CombineObjectData();
};

#endif // !1
