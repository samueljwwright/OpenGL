#ifndef TEXTURE_H
#define TEXTURE _H

#include<string>
#include<iostream>
#include <fstream>


class Texture 
{
private:
	int a;

public:
	int w, h;
	int bitsPerPixel;
	unsigned char* textureData;
	void CreateTexture(const std::string& imageName);
};

#endif // !
