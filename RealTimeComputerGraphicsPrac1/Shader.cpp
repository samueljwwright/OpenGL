#include "Shader.h"

#include <filesystem> //remove if not used later


unsigned int Shader::CompileShader (unsigned int shaderType, const std::string& filePathName)
{
	 
	//Import Shader from file
	std::ifstream ShaderFile("Shaders/" + filePathName + ".txt"); 
	if (ShaderFile.is_open()) 
	{
		std::string parsedShader = parseShader(ShaderFile); 
		const char* shaderCharptr = parsedShader.c_str();

		unsigned int shaderID = glCreateShader(shaderType); 

		glShaderSource(shaderID, 1, &shaderCharptr, nullptr);
		glCompileShader(shaderID);
		return shaderID;
	}
	else 
	{
		std::cout << "Shader file has not been opened " << std::endl;

	}
	ShaderFile.close();
	return 0;
}

std::string Shader::parseShader(std::ifstream& file) 
{
	std::string shaderString;
	std::string l;
	while (std::getline(file, l)) 
	{
		shaderString.append(l + "\n");
	}
	//std::cout << shaderCharptr;
	return shaderString;
}




