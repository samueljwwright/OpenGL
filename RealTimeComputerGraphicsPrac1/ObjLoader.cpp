#include "ObjLoader.h"


//object loader method

//vertex position loading :: 
//if(linestart "v") skip "v" and " " pull all untill " " repeat 2 more times to get all 3 values add all to vertexdata array
//
//face data (index data) loading :: 
//if(linestart "f") skip "v" and " " get next

std::vector<float> ObjLoader::LoadObjectVertexData(const std::string& filePathName)
{
	std::vector<float> a;

	std::ifstream ObjectFile(filePathName + ".obj");
	if (ObjectFile.is_open()) {
		std::cout << "object file opened" << std::endl;
		parseObjectData(ObjectFile);
	}
	else 
	{
		std::cout << "Object failed to load" << std::endl;
	}





	return a;
}

std::vector<float> ObjLoader::parseObjectData(std::ifstream& file)
{
	char v = 'v';

	std::string l;
	while (std::getline(file,l)) 
	{
		if (l[0] == v && l[1] == ' ') 
		{
			std::cout << l << std::endl;
			
			std::istringstream stream(l);
			float value;
			stream >> v; //skips the prefix
			while (stream >> value) 
			{
				std::cout << value << std::endl;
			}
		}
		else {
			std::cout << "not v" << std::endl;
		}
	}



	std::vector<float> values;
	


	return values;
}

