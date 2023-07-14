#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include<string>
#include<iostream>
#include <fstream>

class Shader
{
public:
	unsigned int CompileShader(unsigned int shaderType, const std::string& filePathName);
    std::string parseShader(std::ifstream& file);
};

#endif 
