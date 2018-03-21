#include "texture.h"

struct Texture::_staticTextureValues Texture::staticValues;

void Texture::StaticInit()
{
	//GL_MAX_CUBE_MAP_TEXTURE_SIZE
	//GL_MAX_TEXTURE_SIZE
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &staticValues.maxTextureUnits);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &staticValues.maxCombinedTextureUnits);
	staticValues.init = true;
}
