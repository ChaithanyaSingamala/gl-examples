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

	struct VertexDataLayout {
		int location;
		int start;
		int size;
		int offset;
	};

	long vertexDataEnable = 1;
#if 0 //old method
	Mesh(std::vector<float> _vertexData, std::vector<unsigned short> _indices, int _maxAttributes, ...);
#endif
	Mesh(std::vector<float> _vertexData, std::vector<unsigned short> _indices, std::vector<VertexDataLayout> _layoutList);
	virtual ~Mesh();

	void Render();

	Transform* getTransform() { return transform; }
};