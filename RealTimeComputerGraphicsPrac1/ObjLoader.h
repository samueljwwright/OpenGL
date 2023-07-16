#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct objData 
{
	std::vector<float> vertexData;
	std::vector<float> textureData;
	std::vector<float> normalData;
	std::vector<unsigned int> Positionindex;
	std::vector<unsigned int> textureIndex;
	std::vector<unsigned int> normalIndex;
};


class ObjLoader	
{
public:
	objData LoadObjectVertexData(const std::string& filePathName);
private:
	objData parseObjectData(std::ifstream& file);
};

#endif // !1
