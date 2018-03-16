#include "mesh.h"
#include "GLES3\gl3.h"
#include "helper.h"
#include "transfrom.h"

Mesh::Mesh(std::vector<float> _vertexData, std::vector<unsigned short> _indices, int _maxAttributes, ...)
{
	vertexCount = (unsigned int)_vertexData.size();
	//create VAO
	glGenVertexArrays(1, &voaId);
	glBindVertexArray(voaId);
	//single vbo with mutliple attributes
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, _vertexData.size() * sizeof(float), _vertexData.data(), GL_STATIC_DRAW);
	
	int offset = 0;
	va_list arguments;
	va_start(arguments, _maxAttributes);
	for (int x = 0; x < _maxAttributes; x++)
	{
		int loc = va_arg(arguments, int);
		int start = va_arg(arguments, int);
		int size = va_arg(arguments, int);
		int offset = va_arg(arguments, int);
		glEnableVertexAttribArray(loc);
		glVertexAttribPointer(loc, size, GL_FLOAT, GL_FALSE, offset * sizeof(float), (void *)(start * sizeof(float)));

	}
	va_end(arguments);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned short), _indices.data(), GL_STATIC_DRAW);


	transform = new Transform();

}

Mesh::~Mesh()
{
}

void Mesh::Render() {
	glBindVertexArray(voaId);
	glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}