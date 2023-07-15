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
	std::vector<unsigned int> indexData;
};


class ObjLoader	
{
public:
	std::vector<float> LoadObjectVertexData(const std::string& filePathName);
private:
	std::vector<float> parseObjectData(std::ifstream& file);
};

#endif // !1
