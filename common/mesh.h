#pragma once

#include <vector>
#include <iostream>
#include "glm\glm.hpp"
#include <cstdarg>
#include "transfrom.h"

using namespace glm;
class Transform;

class Mesh {
	//will always use index buffer
	//will create only one vbo

	Transform *transform;

	unsigned int voaId = 0;
	unsigned int vertexCount = 0;
	unsigned int vboId = 0;
	unsigned int iboId = 0;

public:
	long vertexDataEnable = 1;

	Mesh(std::vector<float> _vertexData, std::vector<unsigned short> _indices, int _maxAttributes, ...);
	virtual ~Mesh();

	void Render();

	Transform* getTransform() { return transform; }
};