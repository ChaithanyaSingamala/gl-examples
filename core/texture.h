#pragma once
#include <iostream>
#include "GLES3\gl3.h"
#include "stb_image.h"
#include "helper.h"

class Texture
{
	int width;
	int height;
	unsigned int textureId;

	static struct _staticTextureValues
	{
		int maxTextureUnits = -1;
		int maxCombinedTextureUnits = -1;
		bool init = false;
	}staticValues;

public:
	Texture(std::string _filename)
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

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		UnBind();

	}
	virtual ~Texture()
	{
		UnBind();
		glDeleteTextures(1, &textureId);

	}
	void Bind(int _textureUnit = UINT_MAX)
	{
		if (_textureUnit < staticValues.maxCombinedTextureUnits)
			glActiveTexture(GL_TEXTURE0 + _textureUnit);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}
	void UnBind(int _textureUnit = UINT_MAX)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		if (_textureUnit < staticValues.maxCombinedTextureUnits)
			glActiveTexture(0);

	}

	unsigned int *getHandle() { return &textureId; }

	static void StaticInit();
};

