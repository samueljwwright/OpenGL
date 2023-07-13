#include "Shader.h"

#include <filesystem>


unsigned int Shader::CompileShader (unsigned int shaderType, const std::string& filePathName)
{
	 
	//Import Shader from file
	std::ifstream ShaderFile("Shaders/" + filePathName + ".txt"); //Might need to cast to std::string
	if (ShaderFile.is_open()) 
	{
		parseShader(ShaderFile);
	}
	else 
	{
		std::cout << "Shader file has not been opened " << std::endl;

	}
	



	//compileShader

	unsigned int shaderID = glCreateShader(shaderType);
	//const char* ShaderPointer = vertexShaderStandard.c_str();
	//glShaderSource(shaderID, 1, &shaderPointer, nullptr);
	glCompileShader(shaderID);
	return shaderID;
}

const char* Shader::parseShader(std::ifstream& file) 
{
	std::string shaderString;
	std::string l;
	while (std::getline(file, l)) 
	{
		shaderString.append(l + "\n");
	}

	const char *shaderCharptr = shaderString.c_str();
	std::cout << shaderCharptr;
	return shaderCharptr;
}




