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
	//Prefixes
	char v = 'v'; //vec pos
	char f = 'f'; //face

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
				std::cout << "vPos: " << VertexPosition << " ";
				std::cout << "TexCoord: " << TexCoord << " ";
				std::cout << "Normal: " << Normal <<std::endl;
			}
		}
		else 
		{
			std::cout << "different data" << std::endl;
		}
	}



	std::vector<float> values;
	


	return values;
}

