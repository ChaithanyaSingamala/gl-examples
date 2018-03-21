#pragma once

#include <vector>
#include <iostream>
#include <cstdarg>

#include "glm\glm.hpp"
#include "GLES3\gl3.h"
#include "helper.h"
#include "transfrom.hpp"

using namespace glm;

class Mesh {
	//will always use index buffer
	//will create only one vbo

public:

	struct VertexDataLayout {
		int location;
		int start;
		int size;
		int offset;
	};
	long vertexDataEnable = 1;
	Mesh() {}
	Mesh(std::vector<float> _vertexData, std::vector<unsigned short> _indices, std::vector<VertexDataLayout> _layoutList)
	{
		Load(_vertexData, _indices, _layoutList);
	}
	virtual ~Mesh() {}

	virtual void Render()
	{
		glBindVertexArray(voaId);
		glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_SHORT, 0);
		glBindVertexArray(0);
	}

	virtual Transform* getTransform() { return transform; }

protected:
	Transform *transform;

	unsigned int voaId = 0;
	unsigned int vertexCount = 0;
	unsigned int vboId = 0;
	unsigned int iboId = 0;

	void Load(std::vector<float> _vertexData, std::vector<unsigned short> _indices, std::vector<VertexDataLayout> _layoutList)
	{
		vertexCount = (unsigned int)_indices.size();
		//create VAO
		glGenVertexArrays(1, &voaId);
		glBindVertexArray(voaId);
		//single vbo with mutliple attributes
		glGenBuffers(1, &vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, _vertexData.size() * sizeof(float), _vertexData.data(), GL_STATIC_DRAW);

		for (int i = 0; i < _layoutList.size(); i++) {
			VertexDataLayout layout = _layoutList[i];
			glEnableVertexAttribArray(layout.location);
			glVertexAttribPointer(layout.location, layout.size, GL_FLOAT, GL_FALSE, layout.offset * sizeof(float), (void *)(layout.start * sizeof(float)));

		}

		glGenBuffers(1, &iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned short), _indices.data(), GL_STATIC_DRAW);


		transform = new Transform();
	}



};