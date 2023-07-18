#include "ObjLoader.h"


//remove only for testing
#include <glm/glm.hpp>

#include <ctime> // remove after testing random colors

objData ObjLoader::LoadObjectVertexData(const std::string& filePathName)
{
	objData ObjectData;

	std::ifstream ObjectFile(filePathName + ".obj");
	if (ObjectFile.is_open()) {
		srand(static_cast<unsigned int>(time(nullptr))); ///////remove after testing random colors
		std::cout << "object file opened" << std::endl;
		ObjectData = parseObjectData(ObjectFile);
	}
	else 
	{
		std::cout << "Object failed to load" << std::endl;
	}
	return ObjectData;
	
}

objData ObjLoader::parseObjectData(std::ifstream& file)
{
	objData objectData;
	//Prefixes
	char v = 'v'; //vec pos
	char f = 'f'; //face

	std::string l;
	while (std::getline(file,l)) 
	{
		if (l[0] == v && l[1] == ' ') 
		{			
			std::istringstream stream(l);
			float value;
			stream >> v; //skips the prefix
			while (stream >> value) 
			{
				objectData.vertexData.push_back(value);
				std::cout << value << std::endl;
			}

			objectData.vertexData.push_back((float)rand() / (RAND_MAX)); // For random vertex color values
			objectData.vertexData.push_back((float)rand() / (RAND_MAX));
			objectData.vertexData.push_back((float)rand() / (RAND_MAX));
		}
		else if(l[0] == f)
		{
			std::istringstream stream(l);
			//float value;
			stream >> f; //skips the prefix
			//stream.ignore(sl);

			unsigned int VertexPosition, TexCoord, Normal;
			char slashOne, slashTwo;

			while (stream >> VertexPosition >> slashOne >> TexCoord >> slashTwo >> Normal)
			{
				objectData.Positionindex.push_back(VertexPosition - 1); // -1 BECAUSE OBJ FILES START INDEX AT 1 INSTEAD OF 0!
				std::cout << "vPos: " << VertexPosition << " ";
				objectData.textureIndex.push_back(TexCoord);
				std::cout << "TexCoord: " << TexCoord << " ";
				objectData.normalIndex.push_back(Normal);
				std::cout << "Normal: " << Normal <<std::endl;
			}
		} //ELSE IF FOR OTHER DATA (NORMALS TEXTURES)
		else 
		{
			std::cout << "different data" << std::endl;
		}
	}



	return objectData;
}

