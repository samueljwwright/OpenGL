#include "Texture.h"
#include "third-party/stb_image.h"

//Handles the use if image textures

void Texture::CreateTexture(const std::string& imageName) 
{
	stbi_set_flip_vertically_on_load(1); // LOADS IN IMAGES UPSIDE DOWN
	textureData = stbi_load(imageName.c_str(), &w, &h, &bitsPerPixel, 4); // 4 colour channels (rgba)
	

}
