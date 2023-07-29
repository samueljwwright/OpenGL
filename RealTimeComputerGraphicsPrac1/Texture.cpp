#include "Texture.h"
#include "third-party/stb_image.h"
#include <GL/glew.h>

//Handles the use if image textures

void Texture::CreateTexture(const std::string& imageName, unsigned int &texID) 
{
	stbi_set_flip_vertically_on_load(1); // LOADS IN IMAGES UPSIDE DOWN
	textureData = stbi_load(imageName.c_str(), &w, &h, &bitsPerPixel, 4); // 4 colour channels (rgba)	

    test = texID;
    //glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

    glEnable(GL_TEXTURE_2D);

    
}

void Texture::useTexture(unsigned int texID) 
{
    glActiveTexture(texID); //MAYBE USE GLTEXTURE0 + TEXID
    glBindTexture(GL_TEXTURE_2D, texID);
    
}