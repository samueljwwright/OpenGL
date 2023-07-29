#include "ObjLoader.h"


//remove only for testing


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
    // Prefixes
    char v = 'v'; // vec pos
    char f = 'f'; // face
    char vt = 'vt';

    std::string l;
    while (std::getline(file, l))
    {
        std::istringstream stream(l);
        if (l[0] == v && l[1] == ' ')
        {

            float value;
            stream >> v; // skips the prefix
            while (stream >> value)
            {
                objectData.vertexData.push_back(value);
                //std::cout << value << std::endl;
            }
        }
        else if (l[0] == f)
        {
            std::istringstream stream(l);
            stream >> f; // skips the prefix

            unsigned int VertexPositionIndex, TexCoordIndex, NormalIndex;
            char slashOne, slashTwo;

            while (stream >> VertexPositionIndex >> slashOne >> TexCoordIndex >> slashTwo >> NormalIndex)
            {
                objectData.Positionindex.push_back(VertexPositionIndex - 1); // -1 BECAUSE OBJ FILES START INDEX AT 1 INSTEAD OF 0!
                objectData.textureIndex.push_back(TexCoordIndex - 1);
                objectData.normalIndex.push_back(NormalIndex - 1);
            }
        }
        else if (l[0] == v && l[1] == 't')
        {

            //Messy change the streaming of vt twice!
            stream >> vt;
            stream >> vt;
            glm::vec2 TextureUV;
            stream >> TextureUV.x >> TextureUV.y;
            objectData.textureData.push_back(TextureUV.x);
            objectData.textureData.push_back(TextureUV.y);
            //std::cout << TextureUV.x << " this te" << std::endl;
        }
        else if(l[0] == v && l[1] == 'n')
        {
            stream >> l;
            glm::vec3 NoramlID;
            stream >> NoramlID.x >> NoramlID.y >> NoramlID.z;
            objectData.normalData.push_back(NoramlID.x);
            objectData.normalData.push_back(NoramlID.y);
            objectData.normalData.push_back(NoramlID.z);

        }
        else 
        {

        }
    }

    // Create combined vertex data
    for (size_t i = 0; i < objectData.Positionindex.size(); i++)
    {
            int posIndex = objectData.Positionindex[i];
            int texCoordIndex = objectData.textureIndex[i];
            int normalIndex = objectData.normalIndex[i];

            glm::vec3 position;
            glm::vec2 texCoord;
            glm::vec3 normals;
        
            //Positions
            position.x = objectData.vertexData[posIndex * 3];       // will always be 3 for postions
            position.y = objectData.vertexData[posIndex * 3 + 1];
            position.z = objectData.vertexData[posIndex * 3 + 2];
            //TexCoords
            texCoord.x = objectData.textureData[texCoordIndex * 2]; //will always be 2 for tex coords (normals will follow the same when added)
            texCoord.y = objectData.textureData[texCoordIndex * 2 + 1];
            //Noramls
            //std::cout << objectData.normalData[normalIndex * 3] << " normal index " << std::endl;
            normals.x = objectData.normalData[normalIndex * 3];
            normals.y = objectData.normalData[normalIndex * 3 + 1];
            normals.z = objectData.normalData[normalIndex * 3 + 2];

            //Push all data to combined vec
            objectData.combinedData.push_back(position.x);
            objectData.combinedData.push_back(position.y);
            objectData.combinedData.push_back(position.z);
            objectData.combinedData.push_back(texCoord.x);
            objectData.combinedData.push_back(texCoord.y);

            objectData.combinedData.push_back(normals.x);
            objectData.combinedData.push_back(normals.y);
            objectData.combinedData.push_back(normals.z);


    }

    //push all index to vector
    for (int i = 0; i < objectData.Positionindex.size(); i += 3)
    {
      objectData.indices.push_back(i);
      objectData.indices.push_back(i + 1);
      objectData.indices.push_back(i + 2);
    }

   // for (int i = 0; i < objectData.indices.size(); i++) {
   //     std::cout << objectData.indices[i] << std::endl;
   // }

    return objectData;
}


void ObjLoader::CombineObjectData() {
	//get pos index
	//get tex index
	//object data vector . pushback (vert pos of pos index and corresponding tex data) if this vertex does not exist
}

