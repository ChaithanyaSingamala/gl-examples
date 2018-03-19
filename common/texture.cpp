#include "texture.h"
#include "GLES3\gl3.h"
#include "stb_image.h"
#include "helper.h"


struct Texture::_staticTextureValues Texture::staticValues;

Texture::Texture(std::string _filename)
{
	if (!staticValues.init)
		StaticInit();
	unsigned char* image;
	int req_comp;

	std::vector<char> data = ReadBinaryFile(_filename);

	image = stbi_load_from_memory((unsigned char *)data.data(), data.size(), &width, &height, &req_comp, 0);
		
	glGenTextures(1, &textureId);

	Bind();
	if (req_comp == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	else 	if (req_comp == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	else 	if (req_comp == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, image);
	else
		LogE("Texture: Other format not implemented");

	stbi_image_free(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	UnBind();

}


Texture::~Texture()
{
	UnBind();
	glDeleteTextures(1, &textureId);

}

void Texture::Bind(int _textureUnit)
{
	if (_textureUnit < staticValues.maxCombinedTextureUnits)
		glActiveTexture(GL_TEXTURE0 + _textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::UnBind(int _textureUnit)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	if (_textureUnit < staticValues.maxCombinedTextureUnits)
		glActiveTexture(0);

}

void Texture::StaticInit()
{
	//GL_MAX_CUBE_MAP_TEXTURE_SIZE
	//GL_MAX_TEXTURE_SIZE
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &staticValues.maxTextureUnits);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &staticValues.maxCombinedTextureUnits);
	staticValues.init = true;
}
